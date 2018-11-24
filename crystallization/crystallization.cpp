#include "crystallization.h"

crystallization::crystallization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.button_load, SIGNAL(clicked(bool)), this, SLOT(load()));
	connect(ui.button_save, SIGNAL(clicked(bool)), this, SLOT(save()));
	connect(ui.button_apply, SIGNAL(clicked(bool)), this, SLOT(apply()));
	connect(ui.spinbox_density, SIGNAL(valueChanged(int)), ui.bar_density, SLOT(setValue(int)));
	connect(ui.bar_density, SIGNAL(valueChanged(int)), ui.spinbox_density, SLOT(setValue(int)));
}

void display(Mat img, QLabel *label)
{
	QImage qimg;
	Mat tmp; // !! wrong color
	switch (img.channels())
	{
	case 1:
		qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_ARGB32);
		break;
	case 3:
		cvtColor(img, tmp, CV_BGR2RGB);
		qimg = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, QImage::Format_RGB888);
		break;
	default:
		qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_RGB888);
		break;
	}

	QPixmap pixm = QPixmap::fromImage(qimg).scaled(label->width(), label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	label->setPixmap(pixm);
	label->show();
}

void crystallization::load()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open...", "", "*.jpg *.png *.bmp", 0);
	if (!filename.size()) return;

	src = imread(std::string(filename.toLocal8Bit()));
	dst = src;
	display(src, ui.label_src);
	display(dst, ui.label_dst);

	int nMax = src.rows * src.cols / 50;
	if (nMax > 2000) nMax = 2000;
	ui.bar_density->setMaximum(nMax);
	ui.spinbox_density->setMaximum(nMax);
	ui.bar_density->setValue(nMax / 2);

	ui.button_save->setEnabled(true);
	ui.bar_density->setEnabled(true);
	ui.spinbox_density->setEnabled(true);
	ui.button_apply->setEnabled(true);
}

void crystallization::save()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save as...", "", "*.jpg *.png *.bmp", 0);
	if (!filename.size()) return;
	ui.label_dst->pixmap()->save(filename);
}

void crystallization::apply()
{
	ui.bar_progress->show();

	SLIC slic(src, ui.spinbox_density->value());
	dst = slic.generate_superpixels();
	display(dst, ui.label_dst);

	ui.bar_progress->hide();
}
