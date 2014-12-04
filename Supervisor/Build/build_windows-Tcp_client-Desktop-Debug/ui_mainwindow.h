/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *displayAdrIP;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout;
    QPushButton *button_connect;
    QCheckBox *checkBox_connected;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_takeoff;
    QPushButton *button_landing;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *button_exit;
    QSpacerItem *verticalSpacer_7;
    QGridLayout *gridLayout;
    QPushButton *button_blue_triangle;
    QPushButton *button_red_triangle;
    QSpacerItem *verticalSpacer_2;
    QPushButton *button_green_rectangle;
    QPushButton *button_green_triangle;
    QPushButton *button_blue_rectangle;
    QSpacerItem *verticalSpacer_6;
    QPushButton *button_red_rectangle;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QPushButton *button_red_circle;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *button_green_circle;
    QPushButton *button_blue_circle;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(561, 413);
        MainWindow->setMaximumSize(QSize(1677, 1677));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        displayAdrIP = new QTextEdit(centralWidget);
        displayAdrIP->setObjectName(QString::fromUtf8("displayAdrIP"));
        displayAdrIP->setEnabled(false);
        displayAdrIP->setMaximumSize(QSize(200, 100));

        horizontalLayout->addWidget(displayAdrIP);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));
        button_connect->setEnabled(true);

        verticalLayout->addWidget(button_connect);

        checkBox_connected = new QCheckBox(centralWidget);
        checkBox_connected->setObjectName(QString::fromUtf8("checkBox_connected"));
        checkBox_connected->setEnabled(false);

        verticalLayout->addWidget(checkBox_connected);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        button_takeoff = new QPushButton(centralWidget);
        button_takeoff->setObjectName(QString::fromUtf8("button_takeoff"));
        button_takeoff->setEnabled(false);

        verticalLayout_2->addWidget(button_takeoff);

        button_landing = new QPushButton(centralWidget);
        button_landing->setObjectName(QString::fromUtf8("button_landing"));
        button_landing->setEnabled(false);

        verticalLayout_2->addWidget(button_landing);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        button_exit = new QPushButton(centralWidget);
        button_exit->setObjectName(QString::fromUtf8("button_exit"));
        button_exit->setEnabled(false);

        horizontalLayout->addWidget(button_exit);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        button_blue_triangle = new QPushButton(centralWidget);
        button_blue_triangle->setObjectName(QString::fromUtf8("button_blue_triangle"));
        button_blue_triangle->setEnabled(false);

        gridLayout->addWidget(button_blue_triangle, 2, 4, 1, 1);

        button_red_triangle = new QPushButton(centralWidget);
        button_red_triangle->setObjectName(QString::fromUtf8("button_red_triangle"));
        button_red_triangle->setEnabled(false);

        gridLayout->addWidget(button_red_triangle, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 2, 1, 1);

        button_green_rectangle = new QPushButton(centralWidget);
        button_green_rectangle->setObjectName(QString::fromUtf8("button_green_rectangle"));
        button_green_rectangle->setEnabled(false);

        gridLayout->addWidget(button_green_rectangle, 0, 4, 1, 1);

        button_green_triangle = new QPushButton(centralWidget);
        button_green_triangle->setObjectName(QString::fromUtf8("button_green_triangle"));
        button_green_triangle->setEnabled(false);

        gridLayout->addWidget(button_green_triangle, 4, 2, 1, 1);

        button_blue_rectangle = new QPushButton(centralWidget);
        button_blue_rectangle->setObjectName(QString::fromUtf8("button_blue_rectangle"));
        button_blue_rectangle->setEnabled(false);

        gridLayout->addWidget(button_blue_rectangle, 4, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 3, 4, 1, 1);

        button_red_rectangle = new QPushButton(centralWidget);
        button_red_rectangle->setObjectName(QString::fromUtf8("button_red_rectangle"));
        button_red_rectangle->setEnabled(false);

        gridLayout->addWidget(button_red_rectangle, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 3, 2, 1, 1);

        button_red_circle = new QPushButton(centralWidget);
        button_red_circle->setObjectName(QString::fromUtf8("button_red_circle"));
        button_red_circle->setEnabled(false);

        gridLayout->addWidget(button_red_circle, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 3, 1, 1);

        button_green_circle = new QPushButton(centralWidget);
        button_green_circle->setObjectName(QString::fromUtf8("button_green_circle"));
        button_green_circle->setEnabled(false);

        gridLayout->addWidget(button_green_circle, 2, 0, 1, 1);

        button_blue_circle = new QPushButton(centralWidget);
        button_blue_circle->setObjectName(QString::fromUtf8("button_blue_circle"));
        button_blue_circle->setEnabled(false);

        gridLayout->addWidget(button_blue_circle, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 1, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 3, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 561, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        displayAdrIP->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Adresse IP : 192.168.1.1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Socket : 4000</p></body></html>", 0, QApplication::UnicodeUTF8));
        button_connect->setText(QApplication::translate("MainWindow", "Connecter", 0, QApplication::UnicodeUTF8));
        checkBox_connected->setText(QApplication::translate("MainWindow", "Connected", 0, QApplication::UnicodeUTF8));
        button_takeoff->setText(QApplication::translate("MainWindow", "takeoff", 0, QApplication::UnicodeUTF8));
        button_landing->setText(QApplication::translate("MainWindow", "landing", 0, QApplication::UnicodeUTF8));
        button_exit->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        button_blue_triangle->setText(QString());
        button_red_triangle->setText(QString());
        button_green_rectangle->setText(QString());
        button_green_triangle->setText(QString());
        button_blue_rectangle->setText(QString());
        button_red_rectangle->setText(QString());
        button_red_circle->setText(QString());
        button_green_circle->setText(QString());
        button_blue_circle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
