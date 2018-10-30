#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include "ui_crystallization.h"

#include <opencv.hpp>
using namespace cv;

class crystallization : public QMainWindow
{
	Q_OBJECT

public:
	crystallization(QWidget *parent = Q_NULLPTR);

private:
	Ui::crystallizationClass ui;
	Mat src;
	Mat dst;

private slots:
	void load();
	void save();
};
