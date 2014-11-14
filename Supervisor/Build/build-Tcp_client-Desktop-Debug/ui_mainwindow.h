/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *button_connect;
    QPushButton *button_takeoff;
    QTextEdit *displayAdrIP;
    QCheckBox *checkBox_connected;
    QPushButton *button_landing;
    QPushButton *button_exit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(342, 287);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);
        button_connect->setGeometry(QRect(229, 29, 89, 27));
        button_takeoff = new QPushButton(centralWidget);
        button_takeoff->setObjectName(QStringLiteral("button_takeoff"));
        button_takeoff->setEnabled(false);
        button_takeoff->setGeometry(QRect(60, 110, 85, 27));
        displayAdrIP = new QTextEdit(centralWidget);
        displayAdrIP->setObjectName(QStringLiteral("displayAdrIP"));
        displayAdrIP->setEnabled(false);
        displayAdrIP->setGeometry(QRect(9, 22, 181, 51));
        checkBox_connected = new QCheckBox(centralWidget);
        checkBox_connected->setObjectName(QStringLiteral("checkBox_connected"));
        checkBox_connected->setEnabled(false);
        checkBox_connected->setGeometry(QRect(210, 60, 104, 22));
        button_landing = new QPushButton(centralWidget);
        button_landing->setObjectName(QStringLiteral("button_landing"));
        button_landing->setEnabled(false);
        button_landing->setGeometry(QRect(210, 110, 85, 27));
        button_exit = new QPushButton(centralWidget);
        button_exit->setObjectName(QStringLiteral("button_exit"));
        button_exit->setEnabled(false);
        button_exit->setGeometry(QRect(140, 170, 85, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 342, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        button_connect->setText(QApplication::translate("MainWindow", "Connecter", 0));
        button_takeoff->setText(QApplication::translate("MainWindow", "takeoff", 0));
        displayAdrIP->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Adresse IP : 192.168.1.1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Socket : 4000</p></body></html>", 0));
        checkBox_connected->setText(QApplication::translate("MainWindow", "Connected", 0));
        button_landing->setText(QApplication::translate("MainWindow", "landing", 0));
        button_exit->setText(QApplication::translate("MainWindow", "exit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
