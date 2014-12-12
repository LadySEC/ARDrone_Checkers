#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 ********************************
 * PUBLIC
 * *****************************/




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(DRONE_IMAGE_PATH));
    this->setIconSize(QSize(100,100));
    this->setWindowTitle("AR Drone Tic-Tac-Toe : The Game !");

    
    state_of_mission = mission_stopped ;
    ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
    ui->pushButton_image->setIcon(QIcon(DRONE_IMAGE_PATH));
    ui->pushButton_image->setIconSize(QSize(100,100));
    link_connect();

    /*
    ui->label_Vertical_Speed->setVisible(false);
    ui->label_Horizontal_Speed->setVisible(false);
    ui->label_Value_Horizontal_Speed->setVisible(false);
    ui->label_Value_Vertical_Speed->setVisible(false);
    */

    display_no_communication();

    set_icons_playground_without_communication();

    joueur = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::link_connect()
{
    QObject::connect( &C, SIGNAL(data_to_IHM(QChar/*,int*/,QByteArray)), this, SLOT(update_values_IHM(QChar/*,int*/,QByteArray)));

    QObject::connect( this, SIGNAL(change_battery_value(int)), ui->battery_progressBar, SLOT(setValue(int)));

    QObject::connect(this, SIGNAL(change_altitude_value(QString)), ui->label_Value_Altitude, SLOT(setText(QString)));

    QObject::connect(this, SIGNAL(change_horizon_speed_value(QString)), ui->label_Value_Horizontal_Speed, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(change_vertical_speed_value(QString)), ui->label_Value_Vertical_Speed, SLOT(setText(QString)));

    QObject::connect(this, SIGNAL(change_phi_value(QString)), ui->label_Value_Phi_Angle, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(change_psi_value(QString)), ui->label_Value_Psi_Angle, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(change_theta_value(QString)), ui->label_Value_Theta_Angle, SLOT(setText(QString)));


    QObject::connect(ui->button_connect,SIGNAL(clicked()),this,SLOT(open_connexion()));
    QObject::connect(ui->button_disconnect,SIGNAL(clicked()),this,SLOT(send_exit()));

    QObject::connect( &C, SIGNAL(socket_connected()), this, SLOT(mark_connexion()) ) ;
    QObject::connect( &C, SIGNAL(socket_disconnected()), this, SLOT(unmark_connexion()) ) ;

    QObject::connect(ui->button_start, SIGNAL(clicked()), this, SLOT(start_mission()));
    QObject::connect(ui->button_stop, SIGNAL(clicked()), this, SLOT(stop_mission()));
    QObject::connect(ui->button_pause, SIGNAL(clicked()), this, SLOT(pause_mission()));


    QObject::connect(ui->button_A_1, SIGNAL(clicked()), this, SLOT(send_G_A_1()));
    QObject::connect(ui->button_A_2, SIGNAL(clicked()), this, SLOT(send_G_A_2()));
    QObject::connect(ui->button_A_3, SIGNAL(clicked()), this, SLOT(send_G_A_3()));

    QObject::connect(ui->button_B_1, SIGNAL(clicked()), this, SLOT(send_G_B_1()));
    QObject::connect(ui->button_B_2, SIGNAL(clicked()), this, SLOT(send_G_B_2()));
    QObject::connect(ui->button_B_3,SIGNAL(clicked()), this, SLOT(send_G_B_3())) ;

    QObject::connect(ui->button_C_1, SIGNAL(clicked()), this, SLOT(send_G_C_1())) ;
    QObject::connect(ui->button_C_2, SIGNAL(clicked()), this, SLOT(send_G_C_2())) ;
    QObject::connect(ui->button_C_3, SIGNAL(clicked()), this, SLOT(send_G_C_3()));

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
    ui->label_Connected->setText("Connected !");
    ui->button_connect->setEnabled(false);
    ui->button_disconnect->setEnabled(true);
    ui->battery_progressBar->setVisible(true);
    ui->label_Value_Battery->setVisible(false);

    allow_start_mission();  
    state_of_mission = mission_ready;
    ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));

}

void MainWindow::unmark_connexion()
{
    ui->label_Connected->setText("Disconnected...");
    ui->button_connect->setEnabled(true);
    ui->button_disconnect->setEnabled(false);
    if (state_of_mission != mission_stopped)
        state_of_mission = mission_stopped ;

    forbid_start_mission();
    display_no_communication();
    set_icons_playground_without_communication();
}


/* Start takeoff, allow the user to give orders to the drone to look for a square */
void MainWindow::start_mission()
{
    if ((state_of_mission == mission_stopped) || (state_of_mission == mission_paused) ||(state_of_mission == mission_ready))
    {
        forbid_start_mission();
        send_takeoff();
        state_of_mission = mission_init;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));



        allow_pause_stop_mission();
        allow_orders_to_squares();
    }
}



void MainWindow::stop_mission()
{
    if ((state_of_mission == mission_started) || (state_of_mission == mission_init))
    {
        send_landing();
        allow_start_mission();
        state_of_mission = mission_stopped;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));

        hide_position() ;

        forbid_pause_stop_mission();
        forbid_orders_to_squares();
    }
}

void MainWindow::pause_mission()
{
    if ((state_of_mission == mission_started) || (state_of_mission == mission_init))
    {
        send_landing();
        allow_start_mission();
        state_of_mission = mission_paused;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));

        hide_position() ;

        forbid_pause_stop_mission();
        forbid_orders_to_squares();
    }
}


void MainWindow::update_values_IHM(QChar mnemo,/*int sizeOfData,*/QByteArray data)
{

    if (mnemo == 'N')
    {
        if (data.at(3) & 0x01)
            ui->label_value_flight_status->setText("Drone flying");
        else
            ui->label_value_flight_status->setText("Drone landed");

    }
    else if (mnemo == 'H')
    {
        uint altitude = 0 ;
        altitude += (data.at(0) + (data.at(1)<<8) + (data.at(2) <<16) + (data.at(3)<<24));
        emit change_altitude_value(QString::number(altitude/10)+ " cm");

    }
    else if (mnemo == 'S')
    {
        int32_t hor_speed = 0 ;
        int32_t ver_speed = 0 ;
        hor_speed += (data.at(0) + (data.at(1)<<8) + (data.at(2) <<16) + (data.at(3)<<24));
        if (hor_speed < 0){
            hor_speed = (  hor_speed +16842753) ;
        }

        ver_speed += (data.at(4) + (data.at(5)<<8) + (data.at(6) <<16) + (data.at(7)<<24));
        if (ver_speed < 0){
            ver_speed = (  ver_speed +16842753) ;
        }

        emit change_horizon_speed_value(QString::number(hor_speed/1000));
        emit change_vertical_speed_value(QString::number(ver_speed/1000));
    }
    else if (mnemo == 'G')
    {/*
        int square = data.at(2);
        mark_square_found(square);
*/
    }
    else if (mnemo == 'A')
    {
        int32_t theta = 0 ;
        int32_t psi = 0 ;
        int32_t phi = 0 ;

        theta += ( data.at(0) + (data.at(1)<<8) +  (data.at(2) <<16) + (data.at(3)<<24));
        phi +=( data.at(4) +  (data.at(5)<<8) + (data.at(6) <<16) + (data.at(7)<<24));
        psi += (data.at(8) + (data.at(9)<<8) + (data.at(10) <<16) + (data.at(11)<<24));

        if (psi < 0){
            psi = (  psi +16842753) ;
        }

        if (phi < 0){
            phi =  (  phi +16842753) ;
        }

        if (theta < 0){
            theta = ( theta +16842753) ;
        }

        emit change_theta_value(QString::number(theta/1000.0) + " °");
        emit change_phi_value(QString::number(phi/1000.0) + " °");
        emit change_psi_value(QString::number(psi/1000.0) + " °");


    }
    else if (mnemo == 'B')
    {
        emit change_battery_value( data.at(0));
    }

}

/** ORDERS SENT TO THE DRONE */

void MainWindow::send_takeoff()
{
    if ((state_of_mission == mission_stopped) || (state_of_mission == mission_paused) || (state_of_mission == mission_ready))
    {
        QByteArray message ;
        message.append('T') ;
        message.append(0x01) ;
        message.append(0x01);
        C.recoit_texte(message);
        state_of_mission = mission_init ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));

    }
}

void MainWindow::send_landing()
{
    if ((state_of_mission == mission_started) || (state_of_mission == mission_init))
    {
        QByteArray message ;
        message.append('T') ;
        message.append(0x01) ;
        quint8 value = 0x0 ;
        message.append(value) ;
        C.recoit_texte(message);
        state_of_mission = mission_init ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));

    }
}

void MainWindow::send_exit()
{
    if ((state_of_mission == mission_started) || (state_of_mission == mission_init))
    {
        send_landing();
    }
    QByteArray message ;
    message.append('D') ;
    message.append(0x01) ;
    message.append(0x01);
    C.recoit_texte(message);
}


void MainWindow::send_G_A_1()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x01);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("A1");
        display_position() ;

    }
}

void MainWindow::send_G_A_2()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x04);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("A2");
        display_position() ;

    }
}

void MainWindow::send_G_A_3()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x07);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("A3");
        display_position() ;

    }
}

void MainWindow::send_G_B_1()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x02);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("B1");

        display_position() ;

    }
}

void MainWindow::send_G_B_2()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x05);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("B2");
        display_position() ;

    }
}

void MainWindow::send_G_B_3()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x08);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("B3");
        display_position() ;

    }
}

void MainWindow::send_G_C_1()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x03);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("C1");
        display_position() ;
    }
}

void MainWindow::send_G_C_2()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x06);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("C2");
        display_position() ;

    }
}

void MainWindow::send_G_C_3()
{
    if (state_of_mission == mission_init)
    {
        QByteArray message ;
        message.append('G') ;
        message.append(0x01) ;
        message.append(0x09);
        C.recoit_texte(message);
        state_of_mission = mission_started ;
        ui->label_Value_Mission_Status->setText(mission_state_to_QString(state_of_mission));
        ui->label_Value_Searched_Square->setText("C3");
        display_position() ;

    }
}



/**
 * ********************************
 * PRIVATE
 * *******************************/


/** ******************
 * START MISSION
 * ******************/
void MainWindow::allow_start_mission()
{
    ui->button_start->setEnabled(true);
}

void MainWindow::forbid_start_mission()
{
    ui->button_start->setEnabled(false);
}


/** ******************
 * STOP / PAUSE MISSION
 * ******************/
void MainWindow::allow_pause_stop_mission()
{
    ui->button_pause->setEnabled(true);
    ui->button_stop->setEnabled(true);
}

void MainWindow::forbid_pause_stop_mission()
{
    ui->button_pause->setEnabled(false);
    ui->button_stop->setEnabled(false);
}


/** ******************
 * SENDING ORDERS TO LOOK FOR A SQUARE
 * ******************/
void MainWindow::allow_orders_to_squares()
{
    ui->button_A_1->setEnabled(true);
    ui->button_A_2->setEnabled(true);
    ui->button_A_3->setEnabled(true);

    ui->button_B_1->setEnabled(true);
    ui->button_B_2->setEnabled(true);
    ui->button_B_3->setEnabled(true);

    ui->button_C_1->setEnabled(true);
    ui->button_C_2->setEnabled(true);
    ui->button_C_3->setEnabled(true);
    set_icons_playground_with_communication();
}

void MainWindow::forbid_orders_to_squares()
{
    ui->button_A_1->setEnabled(false);
    ui->button_A_2->setEnabled(false);
    ui->button_A_3->setEnabled(false);

    ui->button_B_1->setEnabled(false);
    ui->button_B_2->setEnabled(false);
    ui->button_B_3->setEnabled(false);

    ui->button_C_1->setEnabled(false);
    ui->button_C_2->setEnabled(false);
    ui->button_C_3->setEnabled(false);
    set_icons_playground_without_communication() ;
}



void MainWindow::display_position()
{
    ui->label_Searched_Square->setVisible(true);
    ui->label_Value_Searched_Square->setVisible(true);
    ui->label_Current_Abscisse->setVisible(true);
    ui->label_Current_Ordonnee->setVisible(true);
    ui->label_Ordonnee->setVisible(true);
    ui->label_Abscisse->setVisible(true);

}

void MainWindow::hide_position()
{
    ui->label_Searched_Square->setVisible(false);
    ui->label_Value_Searched_Square->setVisible(false);

    ui->label_Current_Abscisse->setVisible(false);
    ui->label_Current_Ordonnee->setVisible(false);
    ui->label_Ordonnee->setVisible(false);
    ui->label_Abscisse->setVisible(false);

}


void MainWindow::display_no_communication()
{
    ui->label_value_flight_status->setText(NO_COMMUNICATION);

    ui->battery_progressBar->setVisible(false);
    if (!ui->label_Value_Battery->isVisible())
        ui->label_Value_Battery->setVisible(true);
    ui->label_Value_Battery->setText(NO_COMMUNICATION);

    if (!ui->label_Value_Altitude->isVisible())
        ui->label_Value_Altitude->setVisible(true);
    ui->label_Value_Altitude->setText(NO_COMMUNICATION);

    ui->label_Value_Horizontal_Speed->setText(NO_COMMUNICATION);
    ui->label_Value_Vertical_Speed->setText(NO_COMMUNICATION);

    ui->label_Value_Theta_Angle->setText(NO_COMMUNICATION);
    ui->label_Value_Phi_Angle->setText(NO_COMMUNICATION);
    ui->label_Value_Psi_Angle->setText(NO_COMMUNICATION);

    ui->label_Value_Mission_Status->setText(NO_COMMUNICATION);

    hide_position();

}





void MainWindow::mark_square_found(int square)
{
    QString path_to_marking_image ;
    if (joueur == 0)
    {
        path_to_marking_image = PATH_TO_CIRCLE ;
        joueur = 1 ;
    }
    else
    {
        path_to_marking_image = PATH_TO_CROSS ;
        joueur = 0 ;
    }

    switch (square)
    {
    case 1 :
        ui->button_A_1->setStyleSheet("background-color: white;");
        ui->button_A_1->setIcon(QIcon(path_to_marking_image));
        ui->button_A_1->setIconSize(QSize(100,100));
        ui->button_A_1->setEnabled(false);
        break ;
    case 2 :
        ui->button_B_1->setStyleSheet("background-color: white;");
        ui->button_B_1->setIcon(QIcon(path_to_marking_image));
        ui->button_B_1->setIconSize(QSize(100,100));
        ui->button_B_1->setEnabled(false);
        break ;
    case 3 :
        ui->button_C_1->setStyleSheet("background-color: white;");
        ui->button_C_1->setIcon(QIcon(path_to_marking_image));
        ui->button_C_1->setIconSize(QSize(100,100));
        ui->button_C_1->setEnabled(false);
        break ;
    case 4 :
        ui->button_A_2->setStyleSheet("background-color: white;");
        ui->button_A_2->setIcon(QIcon(path_to_marking_image));
        ui->button_A_2->setIconSize(QSize(100,100));
        ui->button_A_2->setEnabled(false);
        break ;
    case 5 :
        ui->button_B_2->setStyleSheet("background-color: white;");
        ui->button_B_2->setIcon(QIcon(path_to_marking_image));
        ui->button_B_2->setIconSize(QSize(100,100));
        ui->button_B_2->setEnabled(false);
        break ;
    case 6 :
        ui->button_C_2->setStyleSheet("background-color: white;");
        ui->button_C_2->setIcon(QIcon(path_to_marking_image));
        ui->button_C_2->setIconSize(QSize(100,100));
        ui->button_C_2->setEnabled(false);
        break ;
    case 7 :
        ui->button_A_3->setStyleSheet("background-color: white;");
        ui->button_A_3->setIcon(QIcon(path_to_marking_image));
        ui->button_A_3->setIconSize(QSize(100,100));
        ui->button_A_3->setEnabled(false);
        break ;
    case 8 :
        ui->button_B_3->setStyleSheet("background-color: white;");
        ui->button_B_3->setIcon(QIcon(path_to_marking_image));
        ui->button_B_3->setIconSize(QSize(100,100));
        ui->button_B_3->setEnabled(false);
        break ;
    case 9 :
        ui->button_C_3->setStyleSheet("background-color: white;");
        ui->button_C_3->setIcon(QIcon(path_to_marking_image));
        ui->button_C_3->setIconSize(QSize(100,100));
        ui->button_C_3->setEnabled(false);
        break ;
    }

}







void MainWindow::set_icons_playground_with_communication()
{
    ui->button_A_1->setStyleSheet("background-color: red;");
    ui->button_B_2->setStyleSheet("background-color: blue;");
    ui->button_C_3->setStyleSheet("background-color: red;");
    ui->button_A_2->setStyleSheet("background-color: green;");
    ui->button_B_3->setStyleSheet("background-color: green;");
    ui->button_C_1->setStyleSheet("background-color: red;");
    ui->button_A_3->setStyleSheet("background-color: red;");
    ui->button_B_1->setStyleSheet("background-color: green;");
    ui->button_C_2->setStyleSheet("background-color: green;");

}


void MainWindow::set_icons_playground_without_communication()
{
    ui->button_A_1->setStyleSheet("background-color: grey;");
    ui->button_B_2->setStyleSheet("background-color: grey;");
    ui->button_C_3->setStyleSheet("background-color: grey;");
    ui->button_A_2->setStyleSheet("background-color: grey;");
    ui->button_B_3->setStyleSheet("background-color: grey;");
    ui->button_C_1->setStyleSheet("background-color: grey;");
    ui->button_A_3->setStyleSheet("background-color: grey;");
    ui->button_B_1->setStyleSheet("background-color: grey;");
    ui->button_C_2->setStyleSheet("background-color: grey;");

}
