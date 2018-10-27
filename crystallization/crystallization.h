#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_crystallization.h"

class crystallization : public QMainWindow
{
	Q_OBJECT

public:
	crystallization(QWidget *parent = Q_NULLPTR);

private:
	Ui::crystallizationClass ui;
};
