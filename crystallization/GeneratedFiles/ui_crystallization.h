/********************************************************************************
** Form generated from reading UI file 'crystallization.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRYSTALLIZATION_H
#define UI_CRYSTALLIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_crystallizationClass
{
public:
    QWidget *centralWidget;
    QPushButton *button_load;
    QLabel *label_src;
    QLabel *label_dst;
    QPushButton *pushButton;
    QLabel *label;
    QSlider *density_bar;
    QPushButton *button_apply;
    QFrame *line;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *crystallizationClass)
    {
        if (crystallizationClass->objectName().isEmpty())
            crystallizationClass->setObjectName(QStringLiteral("crystallizationClass"));
        crystallizationClass->resize(891, 572);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(crystallizationClass->sizePolicy().hasHeightForWidth());
        crystallizationClass->setSizePolicy(sizePolicy);
        crystallizationClass->setMinimumSize(QSize(594, 424));
        centralWidget = new QWidget(crystallizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        button_load = new QPushButton(centralWidget);
        button_load->setObjectName(QStringLiteral("button_load"));
        button_load->setGeometry(QRect(180, 430, 75, 23));
        label_src = new QLabel(centralWidget);
        label_src->setObjectName(QStringLiteral("label_src"));
        label_src->setGeometry(QRect(20, 20, 401, 381));
        label_dst = new QLabel(centralWidget);
        label_dst->setObjectName(QStringLiteral("label_dst"));
        label_dst->setGeometry(QRect(460, 20, 411, 381));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(620, 430, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 490, 61, 21));
        density_bar = new QSlider(centralWidget);
        density_bar->setObjectName(QStringLiteral("density_bar"));
        density_bar->setGeometry(QRect(130, 490, 601, 22));
        density_bar->setOrientation(Qt::Horizontal);
        button_apply = new QPushButton(centralWidget);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setGeometry(QRect(750, 490, 81, 23));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(430, 20, 20, 391));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        crystallizationClass->setCentralWidget(centralWidget);
        label_dst->raise();
        label_src->raise();
        button_load->raise();
        pushButton->raise();
        label->raise();
        density_bar->raise();
        button_apply->raise();
        line->raise();
        menuBar = new QMenuBar(crystallizationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 26));
        crystallizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(crystallizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        crystallizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(crystallizationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        crystallizationClass->setStatusBar(statusBar);

        retranslateUi(crystallizationClass);

        QMetaObject::connectSlotsByName(crystallizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *crystallizationClass)
    {
        crystallizationClass->setWindowTitle(QApplication::translate("crystallizationClass", "crystallization", nullptr));
        button_load->setText(QApplication::translate("crystallizationClass", "Load", nullptr));
        label_src->setText(QString());
        label_dst->setText(QString());
        pushButton->setText(QApplication::translate("crystallizationClass", "Save", nullptr));
        label->setText(QApplication::translate("crystallizationClass", "Density:", nullptr));
        button_apply->setText(QApplication::translate("crystallizationClass", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class crystallizationClass: public Ui_crystallizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYSTALLIZATION_H
