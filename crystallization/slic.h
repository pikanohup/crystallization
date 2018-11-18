#pragma once

#include <vector>
#include <climits>
#include <opencv.hpp>

using namespace std;
using namespace cv;

struct RGB
{
	int r, g, b;

	RGB(int r, int g, int b) : r(r), g(g), b(b) {}
};

struct LAB
{
	int l, a, b;

	LAB(int l, int a, int b) : l(l), a(a), b(b) {}
};

struct LABXY
{
	LAB lab;
	int x, y;

	LABXY(LAB lab, int x, int y) : lab(lab), x(x), y(y) {}
};

struct Pixel
{
	int id;
	LABXY labxy;
	int label;
	double distance;
	
	Pixel(int id, LABXY labxy) : id(id), labxy(labxy), label(-1), distance(DBL_MAX) {}
};

struct Cluster
{
	int label;
	LABXY center;
	vector<int> pixels;

	Cluster(int label, LABXY center) : label(label), center(center) {}
};

class SLIC
{
private:
	Mat image;			// input
	int k;				// number of cluster centers

	int n;				// number of pixels
	int step;			// grid step

	double m;			// color similarity & spatial proximity
	int iters;			// umber of iterations run by the clustering

	vector<Pixel> pixels;
	vector<Cluster> clusters;

public:
	SLIC(Mat image, int k);
	~SLIC();

	/* utils */
	// transform color space
	double gamma(double x);
	double flab(double x);
	LAB rgb2lab(RGB rgb);
	// compute gradient
	double graylevel(int i, int j);
	double gradient(int i, int j);
	// distance between labxys
	double distance(LABXY p, LABXY q);
	// equalize color of superpixel
	RGB equalize(Cluster c);

	/* main loop */
	// initialize pixels and cluster centers
	void initialize();
	// compute distance and assign labels
	void assign();
	// compute new cluster centers
	void update();
	// Generate an over-segmentation for an image
	Mat generate_superpixels();
};