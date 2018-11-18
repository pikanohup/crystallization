#include "slic.h"

SLIC::SLIC(Mat image, int k) : image(image), k(k), m(32.0), iters(10)
{
	n = image.rows * image.cols;
	step = sqrt(n / k);
}

SLIC::~SLIC()
{
	
}

double SLIC::gamma(double x) {
	return x > 0.04045 ? pow((x + 0.055) / 1.055, 2.4) : (x / 12.92);
}

double SLIC::flab(double x) {
	return x > 0.008856 ? pow(x, 1.0 / 3.0) : (7.787 * x + 0.137931);
}

LAB SLIC::rgb2lab(RGB rgb) {
	double r = gamma(rgb.r / 255.0);
	double g = gamma(rgb.g / 255.0);
	double b = gamma(rgb.b / 255.0);

	double x = 0.412453 * r + 0.357580 * g + 0.180423 * b;
	double y = 0.212671 * r + 0.715160 * g + 0.072169 * b;
	double z = 0.019334 * r + 0.119193 * g + 0.950227 * b;

	x /= 0.950456;
	y /= 1.0;
	z /= 1.088754;

	double fx = flab(x);
	double fy = flab(y);
	double fz = flab(z);

	return LAB(y > 0.008856 ? (116.0 * fy - 16.0) : (903.3f * y), 500.0 * (fx - fy), 200.0 * (fy - fz));
}

double SLIC::graylevel(int i, int j)
{
	return (image.at<cv::Vec3b>(i, j)[2] + image.at<cv::Vec3b>(i, j)[1] + image.at<cv::Vec3b>(i, j)[0]) / 3;
}

double SLIC::gradient(int i, int j)
{
	if (i < 0 || i >= image.rows || j < 0 || j >= image.cols)
		return DBL_MAX;

	double dx = (i < image.rows - 1 ? graylevel(i + 1, j) : 0) - graylevel(i, j);
	double dy = (j < image.cols - 1 ? graylevel(i, j + 1) : 0) - graylevel(i, j);
	return abs(dx) + abs(dy);
}

double SLIC::distance(LABXY p, LABXY q)
{
	double dc = sqrt(pow(p.lab.l - q.lab.l, 2) + pow(p.lab.a - q.lab.a, 2) + pow(p.lab.b - q.lab.b, 2));
	double ds = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
	return sqrt(pow(dc, 2) + pow(ds * m / (double)step, 2));
}

RGB SLIC::equalize(Cluster c)
{
	if (!c.pixels.size())
		return RGB(0, 0, 0);

	int r = 0, g = 0, b = 0;
	for (int i = 0; i < c.pixels.size(); i++) {
		int id = c.pixels[i];
		r += image.at<cv::Vec3b>(pixels[id].labxy.x, pixels[id].labxy.y)[2];
		g += image.at<cv::Vec3b>(pixels[id].labxy.x, pixels[id].labxy.y)[1];
		b += image.at<cv::Vec3b>(pixels[id].labxy.x, pixels[id].labxy.y)[0];
	}
	return RGB(r / c.pixels.size(), g / c.pixels.size(), b / c.pixels.size());
}





void SLIC::initialize()
{
	pixels.clear();
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			int id = j + image.cols * i;
			LAB lab = rgb2lab(RGB(image.at<cv::Vec3b>(i, j)[2], image.at<cv::Vec3b>(i, j)[1], image.at<cv::Vec3b>(i, j)[0]));
			pixels.push_back(Pixel(id, LABXY(lab, i, j)));
		}
	}

	clusters.clear();
	int count = 0;
	for (int i = step / 2; i < image.rows; i += step) {
		for (int j = step / 2; j < image.cols; j += step) {
			LAB lab = rgb2lab(RGB(image.at<cv::Vec3b>(i, j)[2], image.at<cv::Vec3b>(i, j)[1], image.at<cv::Vec3b>(i, j)[0]));
			
			// seek the lowest gradient position in 3*3 neighborhood
			double grads[3][3] = { { gradient(i - 1, j - 1),   gradient(i, j - 1), gradient(i + 1, j - 1) },
								{ gradient(i - 1, j),       gradient(i, j),     gradient(i + 1, j) },
								{ gradient(i - 1, j + 1),   gradient(i, j + 1), gradient(i + 1, j + 1) } };
			double minGrad = DBL_MAX;
			int minI = 1, minJ = 1;
			for (int gi = 0; gi < 3; gi++) {
				for (int gj = 0; gj < 3; gj++) {
					if (grads[gi][gj] < minGrad) {
						minGrad = grads[gi][gj];
						minI = gi;
						minJ = gj;
					}
				}
			}

			clusters.push_back(Cluster(count++, LABXY(lab, i+minI-1, j+minJ-1)));
		}
	}
}

void SLIC::assign()
{
	for (int i = 0; i < clusters.size(); i++) {
		if (clusters[i].label < 0)
			continue;

		int lx = clusters[i].center.x >= step ? (clusters[i].center.x - step) : 0;
		int rx = clusters[i].center.x >= image.rows - step ? (image.rows - 1) : (clusters[i].center.x + step);
		int ly = clusters[i].center.y >= step ? (clusters[i].center.y - step) : 0;
		int ry = clusters[i].center.y >= image.cols - step ? (image.cols - 1) : (clusters[i].center.y + step);

		for (int x = lx; x < rx; x++) {
			for (int y = ly; y < ry; y++) {
				int id = y + image.cols * x;
				double dist = distance(clusters[i].center, pixels[id].labxy);
				if (dist < pixels[id].distance) {
					pixels[id].distance = dist;
					pixels[id].label = clusters[i].label;
				}
			}
		}
	}
}

void SLIC::update()
{
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i].pixels.clear();
	}

	for (int i = 0; i < pixels.size(); i++) {
		if (pixels[i].label < 0)
			continue;

		clusters[pixels[i].label].pixels.push_back(i);
	}

	for (int i = 0; i < clusters.size(); i++) {
		if (!clusters[i].pixels.size()) {
			clusters[i].label = -1;
		}
		else {
			int ls = 0, as = 0, bs = 0, xs = 0, ys = 0;
			for (int p = 0; p < clusters[i].pixels.size(); p++) {
				ls += pixels[clusters[i].pixels[p]].labxy.lab.l;
				as += pixels[clusters[i].pixels[p]].labxy.lab.a;
				bs += pixels[clusters[i].pixels[p]].labxy.lab.b;
				xs += pixels[clusters[i].pixels[p]].labxy.x;
				ys += pixels[clusters[i].pixels[p]].labxy.y;
			}
			clusters[i].center.lab.l = ls / clusters[i].pixels.size();
			clusters[i].center.lab.a = as / clusters[i].pixels.size();
			clusters[i].center.lab.b = bs / clusters[i].pixels.size();
			clusters[i].center.x = xs / clusters[i].pixels.size();
			clusters[i].center.y = ys / clusters[i].pixels.size();
		}
	}
}

Mat SLIC::generate_superpixels()
{
	initialize();

	for (int it = 0; it < iters; it++) {
		assign();
		update();
	}

	Mat output(image.rows, image.cols, image.type());
	for (int i = 0; i < clusters.size(); i++) {
		RGB rgb = equalize(clusters[i]);
		for (int p = 0; p < clusters[i].pixels.size(); p++) {
			output.at<cv::Vec3b>(pixels[clusters[i].pixels[p]].labxy.x, pixels[clusters[i].pixels[p]].labxy.y)[2] = rgb.r;
			output.at<cv::Vec3b>(pixels[clusters[i].pixels[p]].labxy.x, pixels[clusters[i].pixels[p]].labxy.y)[1] = rgb.g;
			output.at<cv::Vec3b>(pixels[clusters[i].pixels[p]].labxy.x, pixels[clusters[i].pixels[p]].labxy.y)[0] = rgb.b;
		}
	}
	return output;
}