#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::open_connexion()
{
    C.connect_server();
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

void MainWindow::mark_connexion()
{
    ui->checkBox_connected->setChecked(true);
    allow_sending();
}

void MainWindow::allow_sending()
{
    ui->button_takeoff->setEnabled(true);
    ui->button_landing->setEnabled(true);
    ui->button_exit->setEnabled(true);
}

void MainWindow::unmark_connexion()
{
    ui->checkBox_connected->setChecked(false);
    forbid_sending() ;
}

void MainWindow::forbid_sending()
{
    ui->button_takeoff->setEnabled(false);
    ui->button_landing->setEnabled(false);
    ui->button_exit->setEnabled(false);
}

void MainWindow::link_connect()
{
    QObject::connect(ui->button_connect,SIGNAL(clicked()),this,SLOT(open_connexion()));

    QObject::connect( &C, SIGNAL(socket_connected()), this, SLOT(mark_connexion()) ) ;
    QObject::connect( &C, SIGNAL(socket_disconnected()), this, SLOT(unmark_connexion()) ) ;


    QObject::connect(ui->button_takeoff,SIGNAL(clicked()),this,SLOT(send_takeoff()));
    QObject::connect(ui->button_landing,SIGNAL(clicked()),this,SLOT(send_landing()));
    QObject::connect(ui->button_exit,SIGNAL(clicked()),this,SLOT(send_exit()));
}
