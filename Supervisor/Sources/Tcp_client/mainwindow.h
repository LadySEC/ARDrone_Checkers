#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "global.h"
#include <QDebug>
#include <QTime>
#include <QDate>
#include "unixTime.h"
#include <QMessageBox>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void link_connect() ;


public slots:

    void begin_scenario() ;
    void open_connexion();

    void mark_connexion() ;
    void unmark_connexion() ;

    void start_mission ();
    void stop_mission();
    //void pause_mission();
    void emergency_landing();
    void reset_after_emergency() ;

    void send_takeoff() ;
    void send_landing() ;
    void send_exit() ;
    void send_emergency(quint8 value) ;

    void update_values_IHM(QChar mnemo,/*int sizeOfData,*/QByteArray data) ;

    void send_G_A_1() ;
    void send_G_A_2() ;
    void send_G_A_3() ;

    void send_G_B_1() ;
    void send_G_B_2() ;
    void send_G_B_3() ;

    void send_G_C_1() ;
    void send_G_C_2() ;
    void send_G_C_3() ;

    void send_date();

    //void slot_change_flight_status(int flying_state) ;

signals :
    void change_battery_value(int new_value);
    void change_altitude_value(QString new_value);
    void change_vertical_speed_value(QString new_value);
    void change_horizon_speed_value(QString new_value);
    void change_theta_value(QString new_value);
    void change_phi_value(QString new_value);
    void change_psi_value(QString new_value);

private:

    void end_scenario(int scenario) ;



    /** Allow the user to ask for the drone to look for a tag.
     * Only available if the mission is started (if the drone has taken off)
     */
    void allow_orders_to_squares() ;

    /** Forbid the user to ask for the drone to look for a tag.
     * The user is forbidden if the mission is stopped or paused.
     */
    void forbid_orders_to_squares() ;

    /** Allow the user to start the mission.
     * The user is allowed to start the mission if the connection with the drone is enable.
     * The user is allowed to start the mission if the mission if stopped or paused.
     */
    void allow_start_mission() ;

    /** Forbid the user to start a mission
     * The user is forbidden to start a mission if the connection with the drone is not enable.
     */
    void forbid_start_mission() ;

    /** Allow the user to stop or pause the mission.
     * The user is allowed to stop or pause the mission if the mission is started.
     */
    void allow_pause_stop_mission() ;

    /** Forbid the user to stop or pause the mission.
     * The user is not allowed to stop or pause the mission if the mission is not started.
     */
    void forbid_pause_stop_mission();


    /** Allow the user to give to the drone the order to land in emergency or to reset from an emergency state.
     */
    void allow_emergency() ;

    /** Forbid the user to stop or pause the mission.
     * The user is not allowed to stop or pause the mission if the mission is not started.
     */
    void forbid_emergency();


    void display_position() ;
    void hide_position() ;

    void display_no_communication();

    void set_icons_playground_without_communication();
    void set_icons_playground_with_communication();

    void set_icons_scenario_not_enable();
    void set_icons_scenario_enable();

    void mark_square_found(int square) ;

    void change_flight_status(int flying_state) ;


    mission_state state_of_mission ;

    int joueur ;

    Ui::MainWindow *ui;
    client C ;

    int battery_level ;
    state_of_flight flight_state ;
    int emergency_status;

    int num_scenario ;
    bool scenario_mode ;
};

#endif // MAINWINDOW_H
