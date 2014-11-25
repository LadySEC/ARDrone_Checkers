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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
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
    QVBoxLayout *verticalLayout_3;
    QPushButton *button_mission;
    QPushButton *button_exit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(561, 181);
        MainWindow->setMaximumSize(QSize(1677, 1677));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        displayAdrIP = new QTextEdit(centralWidget);
        displayAdrIP->setObjectName(QStringLiteral("displayAdrIP"));
        displayAdrIP->setEnabled(false);
        displayAdrIP->setMaximumSize(QSize(200, 100));

        gridLayout->addWidget(displayAdrIP, 0, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);

        verticalLayout->addWidget(button_connect);

        checkBox_connected = new QCheckBox(centralWidget);
        checkBox_connected->setObjectName(QStringLiteral("checkBox_connected"));
        checkBox_connected->setEnabled(false);

        verticalLayout->addWidget(checkBox_connected);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        button_takeoff = new QPushButton(centralWidget);
        button_takeoff->setObjectName(QStringLiteral("button_takeoff"));
        button_takeoff->setEnabled(false);

        verticalLayout_2->addWidget(button_takeoff);

        button_landing = new QPushButton(centralWidget);
        button_landing->setObjectName(QStringLiteral("button_landing"));
        button_landing->setEnabled(false);

        verticalLayout_2->addWidget(button_landing);


        gridLayout->addLayout(verticalLayout_2, 0, 4, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 5, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        button_mission = new QPushButton(centralWidget);
        button_mission->setObjectName(QStringLiteral("button_mission"));
        button_mission->setEnabled(false);

        verticalLayout_3->addWidget(button_mission);

        button_exit = new QPushButton(centralWidget);
        button_exit->setObjectName(QStringLiteral("button_exit"));
        button_exit->setEnabled(false);

        verticalLayout_3->addWidget(button_exit);


        gridLayout->addLayout(verticalLayout_3, 0, 6, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        button_mission->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 561, 25));
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
        displayAdrIP->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Adresse IP : 192.168.1.1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Socket : 4000</p></body></html>", 0));
        button_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        checkBox_connected->setText(QApplication::translate("MainWindow", "Connected", 0));
        button_takeoff->setText(QApplication::translate("MainWindow", "Takeoff", 0));
        button_landing->setText(QApplication::translate("MainWindow", "Landing", 0));
        button_mission->setText(QApplication::translate("MainWindow", "Mission", 0));
        button_exit->setText(QApplication::translate("MainWindow", "exit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
