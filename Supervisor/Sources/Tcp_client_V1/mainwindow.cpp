#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 ********************************
 * PUBLIC
 * *****************************/

static const QString ICON_RED_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_rectangle.jpg";
static const QString ICON_BLUE_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_rectangle.jpg";
static const QString ICON_GREEN_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_rectangle.jpg";
static const QString ICON_RED_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_triangle.jpg";
static const QString ICON_BLUE_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_triangle.jpg";
static const QString ICON_GREEN_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_triangle.jpg";
static const QString ICON_RED_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_circle.jpg";
static const QString ICON_BLUE_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_circle.jpg";
static const QString ICON_GREEN_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_circle.jpg";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    link_connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::link_connect()
{
    QObject::connect(ui->button_connect,SIGNAL(clicked()),this,SLOT(open_connexion()));

    QObject::connect( &C, SIGNAL(socket_connected()), this, SLOT(mark_connexion()) ) ;
    QObject::connect( &C, SIGNAL(socket_disconnected()), this, SLOT(unmark_connexion()) ) ;

    QObject::connect(ui->button_takeoff,SIGNAL(clicked()),this,SLOT(send_takeoff()));
    QObject::connect(ui->button_landing,SIGNAL(clicked()),this,SLOT(send_landing()));
    QObject::connect(ui->button_exit, SIGNAL(clicked()), this, SLOT(send_exit()));
    QObject::connect(ui->button_mission, SIGNAL(clicked()), this, SLOT(send_mission_begin()));
}


/** **************************
 * PUBLIC SLOTS
 * **************************/


void MainWindow::open_connexion()
{
    C.connect_server();
}




void MainWindow::mark_connexion()
{
    ui->checkBox_connected->setChecked(true);
    allow_sending();
}

void MainWindow::unmark_connexion()
{
    ui->checkBox_connected->setChecked(false);
    forbid_sending() ;
}



void MainWindow::send_takeoff()
{
    C.recoit_texte("takeoff");
}

void MainWindow::send_landing()
{
    C.recoit_texte("land");
}

void MainWindow::send_exit()
{
    C.recoit_texte("exit");
}


void MainWindow::send_mission_begin()
{
    C.recoit_texte("begin_m");
}


/**
 * ********************************
 * PRIVATE
 * *******************************/

void MainWindow::allow_sending()
{
    ui->button_takeoff->setEnabled(true);
    ui->button_landing->setEnabled(true);
    ui->button_exit->setEnabled(true);
    ui->button_mission->setEnabled(true);
}

void MainWindow::forbid_sending()
{
    ui->button_takeoff->setEnabled(false);
    ui->button_landing->setEnabled(false);
    ui->button_exit->setEnabled(false);
    ui->button_mission->setEnabled(false);
}



