#include "crystallization.h"

crystallization::crystallization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.button_load, SIGNAL(clicked(bool)), this, SLOT(load()));
	connect(ui.button_save, SIGNAL(clicked(bool)), this, SLOT(save()));
}

void display(Mat img, QLabel *label)
{
	QImage qimg;
	switch (img.channels())
	{
	case 1:
		qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_ARGB32);
		break;
	case 3:
		cvtColor(img, img, CV_BGR2RGB);
		qimg = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB888);
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
	dst = imread("lena.jpg");
	display(src, ui.label_src);
	display(dst, ui.label_dst);
	ui.button_save->setEnabled(true);
}

void crystallization::save()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save as...", "", "*.jpg *.png *.bmp", 0);
	if (!filename.size()) return;
	ui.label_dst->pixmap()->save(filename);
}
