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
#include <QtWidgets/QLineEdit>
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
    QLineEdit *editIP;
    QLineEdit *editMessage;
    QPushButton *button_connect;
    QPushButton *button_send;
    QTextEdit *displayAdrIP;
    QTextEdit *displayMessage;
    QCheckBox *checkBox_connected;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(576, 394);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        editIP = new QLineEdit(centralWidget);
        editIP->setObjectName(QStringLiteral("editIP"));
        editIP->setGeometry(QRect(200, 50, 201, 27));
        editMessage = new QLineEdit(centralWidget);
        editMessage->setObjectName(QStringLiteral("editMessage"));
        editMessage->setGeometry(QRect(200, 190, 201, 27));
        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(false);
        button_connect->setGeometry(QRect(450, 50, 99, 27));
        button_send = new QPushButton(centralWidget);
        button_send->setObjectName(QStringLiteral("button_send"));
        button_send->setEnabled(false);
        button_send->setGeometry(QRect(440, 190, 99, 27));
        displayAdrIP = new QTextEdit(centralWidget);
        displayAdrIP->setObjectName(QStringLiteral("displayAdrIP"));
        displayAdrIP->setEnabled(false);
        displayAdrIP->setGeometry(QRect(30, 50, 141, 31));
        displayMessage = new QTextEdit(centralWidget);
        displayMessage->setObjectName(QStringLiteral("displayMessage"));
        displayMessage->setEnabled(false);
        displayMessage->setGeometry(QRect(20, 190, 141, 31));
        checkBox_connected = new QCheckBox(centralWidget);
        checkBox_connected->setObjectName(QStringLiteral("checkBox_connected"));
        checkBox_connected->setEnabled(false);
        checkBox_connected->setGeometry(QRect(440, 100, 97, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 576, 25));
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
        button_send->setText(QApplication::translate("MainWindow", "Envoyer", 0));
        displayAdrIP->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Adresse IP :</p></body></html>", 0));
        displayMessage->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Message :</p></body></html>", 0));
        checkBox_connected->setText(QApplication::translate("MainWindow", "Connected", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
