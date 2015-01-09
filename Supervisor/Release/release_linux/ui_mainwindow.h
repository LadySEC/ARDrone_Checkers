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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *button_connect;
    QPushButton *button_disconnect;
    QFrame *line;
    QLabel *label_title;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Abscisse;
    QLabel *label_Current_Abscisse;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Ordonnee;
    QLabel *label_Current_Ordonnee;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Mission_Status;
    QLabel *label_Value_Mission_Status;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_Searched_Square;
    QLabel *label_Value_Searched_Square;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QLabel *label_Column_A;
    QLabel *label_Column_B;
    QLabel *label_Square_C;
    QLabel *label_Line_1;
    QLabel *label_Line_2;
    QLabel *label_Line_3;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout;
    QPushButton *button_A_2;
    QPushButton *button_B_2;
    QPushButton *button_C_1;
    QPushButton *button_B_1;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_C_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_A_1;
    QPushButton *button_A_3;
    QPushButton *button_B_3;
    QPushButton *button_C_3;
    QLabel *label_Connected;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_Flight_Status;
    QLabel *label_value_flight_status;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_Battery_Level;
    QLabel *label_Value_Battery;
    QProgressBar *battery_progressBar;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_Altitude;
    QLabel *label_Value_Altitude;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_Horizontal_Speed;
    QLabel *label_Value_Vertical_Speed;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_Vertical_Speed;
    QLabel *label_Value_Horizontal_Speed;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_Theta_Angle;
    QLabel *label_Value_Theta_Angle;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_Phi_Angle;
    QLabel *label_Value_Phi_Angle;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_Psi_Angle;
    QLabel *label_Value_Psi_Angle;
    QPushButton *pushButton_image;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_start;
    QPushButton *scenario_pushButton;
    QPushButton *button_stop;
    QPushButton *button_emergency;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1009, 709);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(1677, 1677));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 10, 181, 90));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        button_connect = new QPushButton(layoutWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);

        verticalLayout->addWidget(button_connect);

        button_disconnect = new QPushButton(layoutWidget);
        button_disconnect->setObjectName(QStringLiteral("button_disconnect"));
        button_disconnect->setEnabled(false);

        verticalLayout->addWidget(button_disconnect);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(410, 10, 20, 561));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(690, 630, 301, 17));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 490, 136, 66));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_Abscisse = new QLabel(layoutWidget1);
        label_Abscisse->setObjectName(QStringLiteral("label_Abscisse"));
        label_Abscisse->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_Abscisse);

        label_Current_Abscisse = new QLabel(layoutWidget1);
        label_Current_Abscisse->setObjectName(QStringLiteral("label_Current_Abscisse"));
        label_Current_Abscisse->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label_Current_Abscisse);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_Ordonnee = new QLabel(layoutWidget1);
        label_Ordonnee->setObjectName(QStringLiteral("label_Ordonnee"));
        label_Ordonnee->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(label_Ordonnee);

        label_Current_Ordonnee = new QLabel(layoutWidget1);
        label_Current_Ordonnee->setObjectName(QStringLiteral("label_Current_Ordonnee"));
        label_Current_Ordonnee->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label_Current_Ordonnee);


        verticalLayout_3->addLayout(horizontalLayout_2);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 430, 300, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_Mission_Status = new QLabel(layoutWidget2);
        label_Mission_Status->setObjectName(QStringLiteral("label_Mission_Status"));
        label_Mission_Status->setMinimumSize(QSize(140, 0));

        horizontalLayout_3->addWidget(label_Mission_Status);

        label_Value_Mission_Status = new QLabel(layoutWidget2);
        label_Value_Mission_Status->setObjectName(QStringLiteral("label_Value_Mission_Status"));

        horizontalLayout_3->addWidget(label_Value_Mission_Status);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 460, 301, 29));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_Searched_Square = new QLabel(layoutWidget3);
        label_Searched_Square->setObjectName(QStringLiteral("label_Searched_Square"));
        label_Searched_Square->setMinimumSize(QSize(140, 0));
        label_Searched_Square->setMaximumSize(QSize(140, 16777215));

        horizontalLayout_4->addWidget(label_Searched_Square);

        label_Value_Searched_Square = new QLabel(layoutWidget3);
        label_Value_Searched_Square->setObjectName(QStringLiteral("label_Value_Searched_Square"));

        horizontalLayout_4->addWidget(label_Value_Searched_Square);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(630, 140, 20, 461));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(790, 140, 20, 461));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(470, 430, 501, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(470, 290, 501, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_Column_A = new QLabel(centralWidget);
        label_Column_A->setObjectName(QStringLiteral("label_Column_A"));
        label_Column_A->setGeometry(QRect(560, 150, 21, 17));
        label_Column_B = new QLabel(centralWidget);
        label_Column_B->setObjectName(QStringLiteral("label_Column_B"));
        label_Column_B->setGeometry(QRect(720, 150, 21, 17));
        label_Square_C = new QLabel(centralWidget);
        label_Square_C->setObjectName(QStringLiteral("label_Square_C"));
        label_Square_C->setGeometry(QRect(850, 150, 21, 17));
        label_Line_1 = new QLabel(centralWidget);
        label_Line_1->setObjectName(QStringLiteral("label_Line_1"));
        label_Line_1->setGeometry(QRect(470, 250, 21, 17));
        label_Line_2 = new QLabel(centralWidget);
        label_Line_2->setObjectName(QStringLiteral("label_Line_2"));
        label_Line_2->setGeometry(QRect(470, 360, 16, 17));
        label_Line_3 = new QLabel(centralWidget);
        label_Line_3->setObjectName(QStringLiteral("label_Line_3"));
        label_Line_3->setGeometry(QRect(470, 480, 16, 17));
        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(510, 180, 421, 381));
        gridLayout = new QGridLayout(layoutWidget4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        button_A_2 = new QPushButton(layoutWidget4);
        button_A_2->setObjectName(QStringLiteral("button_A_2"));
        button_A_2->setEnabled(false);
        button_A_2->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_A_2, 4, 0, 1, 1);

        button_B_2 = new QPushButton(layoutWidget4);
        button_B_2->setObjectName(QStringLiteral("button_B_2"));
        button_B_2->setEnabled(false);
        button_B_2->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_B_2, 4, 2, 1, 1);

        button_C_1 = new QPushButton(layoutWidget4);
        button_C_1->setObjectName(QStringLiteral("button_C_1"));
        button_C_1->setEnabled(false);
        button_C_1->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_C_1, 0, 4, 1, 1);

        button_B_1 = new QPushButton(layoutWidget4);
        button_B_1->setObjectName(QStringLiteral("button_B_1"));
        button_B_1->setEnabled(false);
        button_B_1->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_B_1, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        button_C_2 = new QPushButton(layoutWidget4);
        button_C_2->setObjectName(QStringLiteral("button_C_2"));
        button_C_2->setEnabled(false);
        button_C_2->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_C_2, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        button_A_1 = new QPushButton(layoutWidget4);
        button_A_1->setObjectName(QStringLiteral("button_A_1"));
        button_A_1->setEnabled(false);
        button_A_1->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_A_1, 0, 0, 1, 1);

        button_A_3 = new QPushButton(layoutWidget4);
        button_A_3->setObjectName(QStringLiteral("button_A_3"));
        button_A_3->setEnabled(false);
        button_A_3->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_A_3, 6, 0, 1, 1);

        button_B_3 = new QPushButton(layoutWidget4);
        button_B_3->setObjectName(QStringLiteral("button_B_3"));
        button_B_3->setEnabled(false);
        button_B_3->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_B_3, 6, 2, 1, 1);

        button_C_3 = new QPushButton(layoutWidget4);
        button_C_3->setObjectName(QStringLiteral("button_C_3"));
        button_C_3->setEnabled(false);
        button_C_3->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(button_C_3, 6, 4, 1, 1);

        label_Connected = new QLabel(centralWidget);
        label_Connected->setObjectName(QStringLiteral("label_Connected"));
        label_Connected->setGeometry(QRect(320, 20, 131, 22));
        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(20, 140, 348, 257));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_Flight_Status = new QLabel(layoutWidget5);
        label_Flight_Status->setObjectName(QStringLiteral("label_Flight_Status"));

        horizontalLayout_13->addWidget(label_Flight_Status);

        label_value_flight_status = new QLabel(layoutWidget5);
        label_value_flight_status->setObjectName(QStringLiteral("label_value_flight_status"));

        horizontalLayout_13->addWidget(label_value_flight_status);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_Battery_Level = new QLabel(layoutWidget5);
        label_Battery_Level->setObjectName(QStringLiteral("label_Battery_Level"));

        horizontalLayout_6->addWidget(label_Battery_Level);

        label_Value_Battery = new QLabel(layoutWidget5);
        label_Value_Battery->setObjectName(QStringLiteral("label_Value_Battery"));

        horizontalLayout_6->addWidget(label_Value_Battery);

        battery_progressBar = new QProgressBar(layoutWidget5);
        battery_progressBar->setObjectName(QStringLiteral("battery_progressBar"));
        battery_progressBar->setEnabled(true);
        battery_progressBar->setMinimumSize(QSize(150, 10));
        battery_progressBar->setValue(24);

        horizontalLayout_6->addWidget(battery_progressBar);


        verticalLayout_5->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_Altitude = new QLabel(layoutWidget5);
        label_Altitude->setObjectName(QStringLiteral("label_Altitude"));

        horizontalLayout_12->addWidget(label_Altitude);

        label_Value_Altitude = new QLabel(layoutWidget5);
        label_Value_Altitude->setObjectName(QStringLiteral("label_Value_Altitude"));

        horizontalLayout_12->addWidget(label_Value_Altitude);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_Horizontal_Speed = new QLabel(layoutWidget5);
        label_Horizontal_Speed->setObjectName(QStringLiteral("label_Horizontal_Speed"));

        horizontalLayout_11->addWidget(label_Horizontal_Speed);

        label_Value_Vertical_Speed = new QLabel(layoutWidget5);
        label_Value_Vertical_Speed->setObjectName(QStringLiteral("label_Value_Vertical_Speed"));

        horizontalLayout_11->addWidget(label_Value_Vertical_Speed);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_Vertical_Speed = new QLabel(layoutWidget5);
        label_Vertical_Speed->setObjectName(QStringLiteral("label_Vertical_Speed"));

        horizontalLayout_10->addWidget(label_Vertical_Speed);

        label_Value_Horizontal_Speed = new QLabel(layoutWidget5);
        label_Value_Horizontal_Speed->setObjectName(QStringLiteral("label_Value_Horizontal_Speed"));

        horizontalLayout_10->addWidget(label_Value_Horizontal_Speed);


        verticalLayout_4->addLayout(horizontalLayout_10);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer_4 = new QSpacerItem(346, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_Theta_Angle = new QLabel(layoutWidget5);
        label_Theta_Angle->setObjectName(QStringLiteral("label_Theta_Angle"));

        horizontalLayout_9->addWidget(label_Theta_Angle);

        label_Value_Theta_Angle = new QLabel(layoutWidget5);
        label_Value_Theta_Angle->setObjectName(QStringLiteral("label_Value_Theta_Angle"));

        horizontalLayout_9->addWidget(label_Value_Theta_Angle);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_Phi_Angle = new QLabel(layoutWidget5);
        label_Phi_Angle->setObjectName(QStringLiteral("label_Phi_Angle"));

        horizontalLayout_8->addWidget(label_Phi_Angle);

        label_Value_Phi_Angle = new QLabel(layoutWidget5);
        label_Value_Phi_Angle->setObjectName(QStringLiteral("label_Value_Phi_Angle"));

        horizontalLayout_8->addWidget(label_Value_Phi_Angle);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_Psi_Angle = new QLabel(layoutWidget5);
        label_Psi_Angle->setObjectName(QStringLiteral("label_Psi_Angle"));

        horizontalLayout_7->addWidget(label_Psi_Angle);

        label_Value_Psi_Angle = new QLabel(layoutWidget5);
        label_Value_Psi_Angle->setObjectName(QStringLiteral("label_Value_Psi_Angle"));

        horizontalLayout_7->addWidget(label_Value_Psi_Angle);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_5->addLayout(verticalLayout_2);

        pushButton_image = new QPushButton(centralWidget);
        pushButton_image->setObjectName(QStringLiteral("pushButton_image"));
        pushButton_image->setGeometry(QRect(10, 0, 100, 100));
        pushButton_image->setMinimumSize(QSize(100, 100));
        layoutWidget6 = new QWidget(centralWidget);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(510, 20, 411, 81));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        button_start = new QPushButton(layoutWidget6);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setEnabled(false);
        button_start->setMinimumSize(QSize(70, 70));
        button_start->setMaximumSize(QSize(70, 70));

        horizontalLayout_5->addWidget(button_start);

        scenario_pushButton = new QPushButton(layoutWidget6);
        scenario_pushButton->setObjectName(QStringLiteral("scenario_pushButton"));
        scenario_pushButton->setEnabled(false);
        scenario_pushButton->setMinimumSize(QSize(70, 70));
        scenario_pushButton->setMaximumSize(QSize(70, 70));

        horizontalLayout_5->addWidget(scenario_pushButton);

        button_stop = new QPushButton(layoutWidget6);
        button_stop->setObjectName(QStringLiteral("button_stop"));
        button_stop->setEnabled(false);
        button_stop->setMinimumSize(QSize(70, 70));
        button_stop->setMaximumSize(QSize(70, 70));

        horizontalLayout_5->addWidget(button_stop);

        button_emergency = new QPushButton(layoutWidget6);
        button_emergency->setObjectName(QStringLiteral("button_emergency"));
        button_emergency->setEnabled(false);
        button_emergency->setMinimumSize(QSize(70, 70));
        button_emergency->setMaximumSize(QSize(70, 70));

        horizontalLayout_5->addWidget(button_emergency);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        line->raise();
        label_title->raise();
        line_2->raise();
        line_3->raise();
        line_4->raise();
        line_5->raise();
        label_Column_A->raise();
        label_Column_B->raise();
        label_Square_C->raise();
        label_Line_1->raise();
        label_Line_2->raise();
        label_Line_3->raise();
        label_Connected->raise();
        pushButton_image->raise();
        layoutWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1009, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        button_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        button_disconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        label_title->setText(QApplication::translate("MainWindow", "AR Drone Tic-Tac-Toe V_2.0.1 by Lady Team", 0));
        label_Abscisse->setText(QApplication::translate("MainWindow", "x =", 0));
        label_Current_Abscisse->setText(QString());
        label_Ordonnee->setText(QApplication::translate("MainWindow", "y =", 0));
        label_Current_Ordonnee->setText(QString());
        label_Mission_Status->setText(QApplication::translate("MainWindow", "Mission Status :", 0));
        label_Value_Mission_Status->setText(QString());
        label_Searched_Square->setText(QApplication::translate("MainWindow", "Searched Square :", 0));
        label_Value_Searched_Square->setText(QString());
        label_Column_A->setText(QApplication::translate("MainWindow", "A", 0));
        label_Column_B->setText(QApplication::translate("MainWindow", "B", 0));
        label_Square_C->setText(QApplication::translate("MainWindow", "C", 0));
        label_Line_1->setText(QApplication::translate("MainWindow", "1", 0));
        label_Line_2->setText(QApplication::translate("MainWindow", "2", 0));
        label_Line_3->setText(QApplication::translate("MainWindow", "3", 0));
        button_A_2->setText(QString());
        button_B_2->setText(QString());
        button_C_1->setText(QString());
        button_B_1->setText(QString());
        button_C_2->setText(QString());
        button_A_1->setText(QString());
        button_A_3->setText(QString());
        button_B_3->setText(QString());
        button_C_3->setText(QString());
        label_Connected->setText(QApplication::translate("MainWindow", "Disconnected", 0));
        label_Flight_Status->setText(QApplication::translate("MainWindow", "Flight status :", 0));
        label_value_flight_status->setText(QString());
        label_Battery_Level->setText(QApplication::translate("MainWindow", "Battery level :", 0));
        label_Value_Battery->setText(QString());
        label_Altitude->setText(QApplication::translate("MainWindow", "Altitude : ", 0));
        label_Value_Altitude->setText(QString());
        label_Horizontal_Speed->setText(QApplication::translate("MainWindow", "Horizontal Speed :", 0));
        label_Value_Vertical_Speed->setText(QString());
        label_Vertical_Speed->setText(QApplication::translate("MainWindow", "Vertical Speed :", 0));
        label_Value_Horizontal_Speed->setText(QString());
        label_Theta_Angle->setText(QApplication::translate("MainWindow", "Theta angle :", 0));
        label_Value_Theta_Angle->setText(QString());
        label_Phi_Angle->setText(QApplication::translate("MainWindow", "Phi angle :", 0));
        label_Value_Phi_Angle->setText(QString());
        label_Psi_Angle->setText(QApplication::translate("MainWindow", "Psi angle :", 0));
        label_Value_Psi_Angle->setText(QString());
        pushButton_image->setText(QString());
        button_start->setText(QString());
        scenario_pushButton->setText(QString());
        button_stop->setText(QString());
        button_emergency->setText(QString());
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
