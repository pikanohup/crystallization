#include "crystallization.h"

crystallization::crystallization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.button_load, SIGNAL(clicked(bool)), this, SLOT(load()));
	connect(ui.button_save, SIGNAL(clicked(bool)), this, SLOT(save()));
	connect(ui.button_apply, SIGNAL(clicked(bool)), this, SLOT(apply()));
	connect(ui.density_spinbox, SIGNAL(valueChanged(int)), ui.density_bar, SLOT(setValue(int)));
	connect(ui.density_bar, SIGNAL(valueChanged(int)), ui.density_spinbox, SLOT(setValue(int)));
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
	// TODO
	// QString filename = QFileDialog::getOpenFileName(this, "Open...", "", "*.jpg *.png *.bmp", 0);
	// src = imread(std::string(filename.toLocal8Bit()));
	src = imread("lena.jpg");
	dst = src;
	display(src, ui.label_src);
	display(dst, ui.label_dst);

	int nMax = src.rows * src.cols / 100;
	if (nMax > 10000) nMax = 10000;
	ui.density_bar->setMaximum(nMax);
	ui.density_spinbox->setMaximum(nMax);

	ui.button_save->setEnabled(true);
	ui.density_bar->setEnabled(true);
	ui.density_spinbox->setEnabled(true);
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
	SLIC slic(src, ui.density_spinbox->value());
	dst = slic.generate_superpixels();
	display(dst, ui.label_dst);
}
