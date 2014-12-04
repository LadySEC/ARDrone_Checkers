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
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_takeoff;
    QPushButton *button_landing;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *button_connect;
    QPushButton *button_exit;
    QCheckBox *checkBox_connected;
    QFrame *line;
    QLabel *label;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Abscisse;
    QLabel *label_Current_Abscisse;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Ordonnee;
    QLabel *label_Current_Ordonnee;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Mission_Status;
    QLabel *label_Current_Status;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_Searched_Square;
    QLabel *label_Current_Square;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_start;
    QPushButton *button_pause;
    QPushButton *button_stop;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *button_green_circle;
    QPushButton *button_red_rectangle;
    QPushButton *button_green_rectangle;
    QPushButton *button_blue_circle;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_blue_triangle;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_red_triangle;
    QPushButton *button_blue_rectangle;
    QPushButton *button_green_triangle;
    QPushButton *button_red_circle;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1009, 709);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(1677, 1677));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 230, 87, 62));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        button_takeoff = new QPushButton(layoutWidget);
        button_takeoff->setObjectName(QString::fromUtf8("button_takeoff"));
        button_takeoff->setEnabled(false);

        verticalLayout_2->addWidget(button_takeoff);

        button_landing = new QPushButton(layoutWidget);
        button_landing->setObjectName(QString::fromUtf8("button_landing"));
        button_landing->setEnabled(false);

        verticalLayout_2->addWidget(button_landing);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 10, 181, 90));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        button_connect = new QPushButton(layoutWidget1);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));
        button_connect->setEnabled(true);

        verticalLayout->addWidget(button_connect);

        button_exit = new QPushButton(layoutWidget1);
        button_exit->setObjectName(QString::fromUtf8("button_exit"));
        button_exit->setEnabled(false);

        verticalLayout->addWidget(button_exit);

        checkBox_connected = new QCheckBox(layoutWidget1);
        checkBox_connected->setObjectName(QString::fromUtf8("checkBox_connected"));
        checkBox_connected->setEnabled(true);

        verticalLayout->addWidget(checkBox_connected);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(410, 10, 20, 561));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(700, 630, 301, 17));
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(770, 70, 136, 66));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Abscisse = new QLabel(layoutWidget2);
        label_Abscisse->setObjectName(QString::fromUtf8("label_Abscisse"));
        label_Abscisse->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_Abscisse);

        label_Current_Abscisse = new QLabel(layoutWidget2);
        label_Current_Abscisse->setObjectName(QString::fromUtf8("label_Current_Abscisse"));
        label_Current_Abscisse->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label_Current_Abscisse);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_Ordonnee = new QLabel(layoutWidget2);
        label_Ordonnee->setObjectName(QString::fromUtf8("label_Ordonnee"));
        label_Ordonnee->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(label_Ordonnee);

        label_Current_Ordonnee = new QLabel(layoutWidget2);
        label_Current_Ordonnee->setObjectName(QString::fromUtf8("label_Current_Ordonnee"));
        label_Current_Ordonnee->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label_Current_Ordonnee);


        verticalLayout_3->addLayout(horizontalLayout_2);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(460, 50, 300, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_Mission_Status = new QLabel(layoutWidget3);
        label_Mission_Status->setObjectName(QString::fromUtf8("label_Mission_Status"));
        label_Mission_Status->setMinimumSize(QSize(140, 0));

        horizontalLayout_3->addWidget(label_Mission_Status);

        label_Current_Status = new QLabel(layoutWidget3);
        label_Current_Status->setObjectName(QString::fromUtf8("label_Current_Status"));

        horizontalLayout_3->addWidget(label_Current_Status);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(460, 80, 301, 29));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_Searched_Square = new QLabel(layoutWidget4);
        label_Searched_Square->setObjectName(QString::fromUtf8("label_Searched_Square"));
        label_Searched_Square->setMinimumSize(QSize(140, 0));
        label_Searched_Square->setMaximumSize(QSize(140, 16777215));

        horizontalLayout_4->addWidget(label_Searched_Square);

        label_Current_Square = new QLabel(layoutWidget4);
        label_Current_Square->setObjectName(QString::fromUtf8("label_Current_Square"));

        horizontalLayout_4->addWidget(label_Current_Square);

        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(460, 0, 471, 31));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        button_start = new QPushButton(layoutWidget5);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setEnabled(false);
        button_start->setMinimumSize(QSize(0, 0));
        button_start->setMaximumSize(QSize(150, 150));

        horizontalLayout_5->addWidget(button_start);

        button_pause = new QPushButton(layoutWidget5);
        button_pause->setObjectName(QString::fromUtf8("button_pause"));
        button_pause->setEnabled(false);
        button_pause->setMinimumSize(QSize(0, 0));
        button_pause->setMaximumSize(QSize(150, 150));

        horizontalLayout_5->addWidget(button_pause);

        button_stop = new QPushButton(layoutWidget5);
        button_stop->setObjectName(QString::fromUtf8("button_stop"));
        button_stop->setEnabled(false);
        button_stop->setMinimumSize(QSize(0, 0));
        button_stop->setMaximumSize(QSize(150, 150));

        horizontalLayout_5->addWidget(button_stop);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(620, 150, 20, 461));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(780, 150, 20, 461));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(460, 440, 501, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(460, 310, 501, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 160, 21, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(710, 160, 21, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(840, 160, 21, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(460, 260, 21, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(460, 370, 16, 17));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(460, 490, 16, 17));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(500, 190, 421, 381));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        button_green_circle = new QPushButton(widget);
        button_green_circle->setObjectName(QString::fromUtf8("button_green_circle"));
        button_green_circle->setEnabled(false);

        gridLayout->addWidget(button_green_circle, 4, 0, 1, 1);

        button_red_rectangle = new QPushButton(widget);
        button_red_rectangle->setObjectName(QString::fromUtf8("button_red_rectangle"));
        button_red_rectangle->setEnabled(false);

        gridLayout->addWidget(button_red_rectangle, 4, 2, 1, 1);

        button_green_rectangle = new QPushButton(widget);
        button_green_rectangle->setObjectName(QString::fromUtf8("button_green_rectangle"));
        button_green_rectangle->setEnabled(false);

        gridLayout->addWidget(button_green_rectangle, 0, 4, 1, 1);

        button_blue_circle = new QPushButton(widget);
        button_blue_circle->setObjectName(QString::fromUtf8("button_blue_circle"));
        button_blue_circle->setEnabled(false);

        gridLayout->addWidget(button_blue_circle, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        button_blue_triangle = new QPushButton(widget);
        button_blue_triangle->setObjectName(QString::fromUtf8("button_blue_triangle"));
        button_blue_triangle->setEnabled(false);

        gridLayout->addWidget(button_blue_triangle, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        button_red_triangle = new QPushButton(widget);
        button_red_triangle->setObjectName(QString::fromUtf8("button_red_triangle"));
        button_red_triangle->setEnabled(false);

        gridLayout->addWidget(button_red_triangle, 0, 0, 1, 1);

        button_blue_rectangle = new QPushButton(widget);
        button_blue_rectangle->setObjectName(QString::fromUtf8("button_blue_rectangle"));
        button_blue_rectangle->setEnabled(false);

        gridLayout->addWidget(button_blue_rectangle, 6, 0, 1, 1);

        button_green_triangle = new QPushButton(widget);
        button_green_triangle->setObjectName(QString::fromUtf8("button_green_triangle"));
        button_green_triangle->setEnabled(false);

        gridLayout->addWidget(button_green_triangle, 6, 2, 1, 1);

        button_red_circle = new QPushButton(widget);
        button_red_circle->setObjectName(QString::fromUtf8("button_red_circle"));
        button_red_circle->setEnabled(false);

        gridLayout->addWidget(button_red_circle, 6, 4, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        line->raise();
        label->raise();
        line_2->raise();
        line_3->raise();
        line_4->raise();
        line_5->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1009, 25));
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
        button_takeoff->setText(QApplication::translate("MainWindow", "takeoff", 0, QApplication::UnicodeUTF8));
        button_landing->setText(QApplication::translate("MainWindow", "landing", 0, QApplication::UnicodeUTF8));
        button_connect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        button_exit->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        checkBox_connected->setText(QApplication::translate("MainWindow", "Connected", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "AR Drone Tic-Tac-Toe V_2.0.1 by Lady Team", 0, QApplication::UnicodeUTF8));
        label_Abscisse->setText(QApplication::translate("MainWindow", "x =", 0, QApplication::UnicodeUTF8));
        label_Current_Abscisse->setText(QString());
        label_Ordonnee->setText(QApplication::translate("MainWindow", "y =", 0, QApplication::UnicodeUTF8));
        label_Current_Ordonnee->setText(QString());
        label_Mission_Status->setText(QApplication::translate("MainWindow", "Mission Status :", 0, QApplication::UnicodeUTF8));
        label_Current_Status->setText(QString());
        label_Searched_Square->setText(QApplication::translate("MainWindow", "Searched Square :", 0, QApplication::UnicodeUTF8));
        label_Current_Square->setText(QString());
        button_start->setText(QApplication::translate("MainWindow", "Start / Resume", 0, QApplication::UnicodeUTF8));
        button_pause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        button_stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "A", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "B", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        button_green_circle->setText(QString());
        button_red_rectangle->setText(QString());
        button_green_rectangle->setText(QString());
        button_blue_circle->setText(QString());
        button_blue_triangle->setText(QString());
        button_red_triangle->setText(QString());
        button_blue_rectangle->setText(QString());
        button_green_triangle->setText(QString());
        button_red_circle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
