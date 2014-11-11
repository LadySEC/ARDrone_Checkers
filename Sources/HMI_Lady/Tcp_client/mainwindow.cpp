#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QObject::connect(ui->button_connect,SIGNAL(clicked()),this,SLOT(editing_IP()));
    QObject::connect(ui->editIP,SIGNAL(editingFinished()),this,SLOT(allow_connect()));

    QObject::connect(ui->button_send,SIGNAL(clicked()),this,SLOT(send_message()));
    QObject::connect(ui->editMessage,SIGNAL(editingFinished()),this,SLOT(allow_send()));

    QObject::connect( &C, SIGNAL(vers_IHM_connexion_OK()), this, SLOT(mark_connection()) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::editing_IP()
{
    C.recoit_IP(ui->editIP->text());
}

void MainWindow::allow_connect()
{
    ui->button_connect->setEnabled(true);
}

void MainWindow::allow_send()
{
    ui->button_send->setEnabled(true);
}


void MainWindow::send_message()
{
    C.recoit_texte(ui->editMessage->text());
}

void MainWindow::mark_connection()
{
    ui->checkBox_connected->setChecked(true);
}
