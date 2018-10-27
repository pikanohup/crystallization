#include "crystallization.h"

crystallization::crystallization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.button_load, SIGNAL(clicked(bool)), this, SLOT(loadAndShow()));
}

void displayImage(Mat img, QLabel *label)
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

void crystallization::loadAndShow()
{
	// QString filename = QFileDialog::getOpenFileName(this, "Open...", "", "*.jpg *.png *.bnp", 0);
	// src = imread(std::string(filename.toLocal8Bit()));
	src = imread("lena.jpg");
	displayImage(src, ui.label_src);
}