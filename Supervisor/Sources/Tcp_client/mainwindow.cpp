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

    ui->button_red_rectangle->setIcon(QIcon(ICON_RED_RECTANGLE_PATH));
    ui->button_red_rectangle->setIconSize(QSize(100, 100));

    ui->button_blue_rectangle->setIcon(QIcon(ICON_BLUE_RECTANGLE_PATH));
    ui->button_blue_rectangle->setIconSize(QSize(100, 100));

    ui->button_green_rectangle->setIcon(QIcon(ICON_GREEN_RECTANGLE_PATH));
    ui->button_green_rectangle->setIconSize(QSize(100, 100));

    ui->button_red_triangle->setIcon(QIcon(ICON_RED_TRIANGLE_PATH));
    ui->button_red_triangle->setIconSize(QSize(100, 100));

    ui->button_blue_triangle->setIcon(QIcon(ICON_BLUE_TRIANGLE_PATH));
    ui->button_blue_triangle->setIconSize(QSize(100, 100));

    ui->button_green_triangle->setIcon(QIcon(ICON_GREEN_TRIANGLE_PATH));
    ui->button_green_triangle->setIconSize(QSize(100, 100));

    ui->button_red_circle->setIcon(QIcon(ICON_RED_CIRCLE_PATH));
    ui->button_red_circle->setIconSize(QSize(100, 100));

    ui->button_blue_circle->setIcon(QIcon(ICON_BLUE_CIRCLE_PATH));
    ui->button_blue_circle->setIconSize(QSize(100, 100));

    ui->button_green_circle->setIcon(QIcon(ICON_GREEN_CIRCLE_PATH));
    ui->button_green_circle->setIconSize(QSize(100, 100));


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
    QObject::connect(ui->button_exit,SIGNAL(clicked()),this,SLOT(send_exit()));

    QObject::connect(ui->button_blue_rectangle, SIGNAL(clicked()), this, SLOT(send_M_Bl_Re()));
    QObject::connect(ui->button_blue_circle, SIGNAL(clicked()), this, SLOT(send_M_Bl_Ci()));
    QObject::connect(ui->button_blue_triangle, SIGNAL(clicked()), this, SLOT(send_M_Bl_Tr()));

    QObject::connect(ui->button_green_circle, SIGNAL(clicked()), this, SLOT(send_M_Gr_Ci()));
    QObject::connect(ui->button_green_rectangle, SIGNAL(clicked()), this, SLOT(send_M_Gr_Re()));
    QObject::connect(ui->button_green_triangle,SIGNAL(clicked()), this, SLOT(send_M_Gr_Tr())) ;

    QObject::connect(ui->button_red_circle, SIGNAL(clicked()), this, SLOT(send_M_Ro_Ci())) ;
    QObject::connect(ui->button_red_rectangle, SIGNAL(clicked()), this, SLOT(send_M_Ro_Re())) ;
    QObject::connect(ui->button_red_triangle, SIGNAL(clicked()), this, SLOT(send_M_Ro_Tr()));

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


void MainWindow::send_M_Bl_Re()
{
    C.recoit_texte("M_Bl_Re");
}

void MainWindow::send_M_Bl_Tr()
{
    C.recoit_texte("M_Bl_Tr");
}

void MainWindow::send_M_Bl_Ci()
{
    C.recoit_texte("M_Bl_Ci");
}

void MainWindow::send_M_Ro_Re()
{
    C.recoit_texte("M_Ro_Re");
}

void MainWindow::send_M_Ro_Tr()
{
    C.recoit_texte("M_Ro_Tr");
}

void MainWindow::send_M_Ro_Ci()
{
    C.recoit_texte("M_Ro_Ci");
}

void MainWindow::send_M_Gr_Re()
{
    C.recoit_texte("M_Gr_Re");
}

void MainWindow::send_M_Gr_Tr()
{
    C.recoit_texte("M_Gr_Tr");
}

void MainWindow::send_M_Gr_Ci()
{
    C.recoit_texte("M_Gr_Ci");
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

    ui->button_blue_rectangle->setEnabled(true);
    ui->button_blue_circle->setEnabled(true);
    ui->button_blue_triangle->setEnabled(true);

    ui->button_red_circle->setEnabled(true);
    ui->button_red_rectangle->setEnabled(true);
    ui->button_red_triangle->setEnabled(true);

    ui->button_green_circle->setEnabled(true);
    ui->button_green_rectangle->setEnabled(true);
    ui->button_green_triangle->setEnabled(true);
}

void MainWindow::forbid_sending()
{
    ui->button_takeoff->setEnabled(false);
    ui->button_landing->setEnabled(false);
    ui->button_exit->setEnabled(false);

    ui->button_blue_rectangle->setEnabled(false);
    ui->button_blue_circle->setEnabled(false);
    ui->button_blue_triangle->setEnabled(false);

    ui->button_red_circle->setEnabled(false);
    ui->button_red_rectangle->setEnabled(false);
    ui->button_red_triangle->setEnabled(false);

    ui->button_green_circle->setEnabled(false);
    ui->button_green_rectangle->setEnabled(false);
    ui->button_green_triangle->setEnabled(false);
}



