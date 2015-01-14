/**
 * \file 	mainWindow.h
 * \brief 	Definition of the evolution of the whole Interface : HMI code, Treatment of the orders coming from the Interface, to send orders to the drone
 * \author 	Lady team
 * \version 1.0
 * \date 	9 January 2015
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/

#include <QMainWindow>
#include "client.h"
#include "global.h"
#include <QDebug>
#include <QTime>
#include <QDate>
#include "unixTime.h"
#include <QMessageBox>
#include <QThread>
#include <QTimer>

/**********************************************************************************/
/* Class Definition                                                               */
/**********************************************************************************/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

/**********************************************************************************/
/* Public methodes                                                                */
/**********************************************************************************/

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void link_connect() ;

/**********************************************************************************/
/* Public slots                                                                   */
/**********************************************************************************/

public slots:

/**********************************************************************************/
/* Private slots                                                                   */
/**********************************************************************************/

private slots:

    /** Begin a scenario according the current scenario
     */
    void slot_begin_scenario() ;

    /** Connect the client to the server
     */
    void slot_open_connexion();

    /** Mark the connexion as established on the Interface
     */
    void slot_mark_connexion() ;

    /** Mark the connexion as not established on the Interface
     */
    void slot_unmark_connexion() ;

    /** Order the drone to take off and to ready for mission
     */
    void slot_takeoff();

    /** Order the drone to land and forbid any mission or order to take new moves
     */
    void slot_land();

    /** Order the drone to land in emergency, and to wait for the reset emergency order
     * No order to take new moves can be given to the drone
     */
    void slot_emergency_landing();

    /** Order the drone to reset after an emergency landing, and to ready for new move order
     */
    void slot_reset_after_emergency() ;

    /** During a scenario, when a square is found, send the order to look for the next square
     */
    void slot_next_move() ;

    /** On the reception of frames from the server (drone), update of the new values on the Interface
     * - update the flight status, the battery level and the emergency status from the NavData
     * - update the altitude from the altitude frame
     * - update the horizontal and vertical speed from the speed frame
     * - update the marked squares and order the drone to look for the next squares during a mission on reception of the movement frameGeometry()-
     * - update the theta, phi and psi angles from the angles frame
     */
    void slot_update_values_IHM(QChar mnemo,/*int sizeOfData,*/QByteArray data) ;

    /** Send to the drone the order to takeoff
     */
    void slot_send_takeoff() ;

    /** Send to the drone the order to takeoff
     */
    void slot_send_landing() ;

    /** Send to the drone the order to land in emergency or to quit the emergency mode
     */
    void slot_send_emergency(quint8 value) ;

    /** Send to the drone the order to disconnect
     */
    void slot_send_exit() ;

    /** Send to the drone the order to look for the square A1
     */
    void slot_send_G_A_1() ;

    /** Send to the drone the order to look for the square A2
     */
    void slot_send_G_A_2() ;

    /** Send to the drone the order to look for the square A3
     */
    void slot_send_G_A_3() ;

    /** Send to the drone the order to look for the square B1
     */
    void slot_send_G_B_1() ;

    /** Send to the drone the order to look for the square B2
     */
    void slot_send_G_B_2() ;

    /** Send to the drone the order to look for the square B3
     */
    void slot_send_G_B_3() ;

    /** Send to the drone the order to look for the square C1
     */
    void slot_send_G_C_1() ;

    /** Send to the drone the order to look for the square C2
     */
    void slot_send_G_C_2() ;

    /** Send to the drone the order to look for the square C3
     */
    void slot_send_G_C_3() ;

    /** Send to the drone a message with the date to be updated in the logs
     */
    void slot_send_date();


/**********************************************************************************/
/* Signals                                                                        */
/**********************************************************************************/

signals :
    void sig_change_battery_value(int new_value); /*!< Signal to update the battery value when frame with battery value is sent by the drone */
    void sig_change_altitude_value(QString new_value); /*!< Signal to update the altitude value when frame with altitute value is sent by the drone */
    void sig_change_vertical_speed_value(QString new_value); /*!< Signal to update the vertical speed value when frame with vertical speed value value is sent by the drone */
    void sig_change_horizon_speed_value(QString new_value); /*!< Signal to update the horizontal speed value when frame with horizontal speed value is sent by the drone */
    void sig_change_theta_value(QString new_value); /*!< Signal to update the theta angle value when frame with theta angle value is sent by the drone */
    void sig_change_phi_value(QString new_value); /*!< Signal to update the phi angle value when frame with phi angle value is sent by the drone */
    void sig_change_psi_value(QString new_value); /*!< Signal to update the psi angle value when frame with psi angle value is sent by the drone */

/**********************************************************************************/
/* Private methodes                                                               */
/**********************************************************************************/

private:

    /** End a scenario according to the evolution of the game :
     * Display a messageBox with information about the winner of the scenario
     * @param int scenario : 1,2 or 3, according to the played scenario
     */
    void end_scenario(int scenario) ;

    /** Allow the user to start the mission.
     * The user is allowed to start the mission if the connection with the drone is enable.
     * The user is allowed to start the mission if the mission if stopped or paused : the drone is landed.
     */
    void allow_start_mission() ;

    /** Forbid the user to start a mission
     * The user is forbidden to start a mission if the connection with the drone is not enable.
     * The user is forbidden to start a mission if the drone has already started a mission
     */
    void forbid_start_mission() ;

    /** Allow the user to stop the mission.
     * The user is allowed to stop the mission if the mission is started.
     */
    void allow_stop_mission() ;

    /** Forbid the user to stop the mission.
     * The user is not allowed to stop the mission if the mission is not started.
     */
    void forbid_stop_mission();

    /** Allow the user to give the drone the order to land in emergency or to reset from an emergency state.
     */
    void allow_emergency() ;

    /** Forbid the user to give the drone order to stop the drone in emergency.
     */
    void forbid_emergency();

    /** Allow the user to ask the drone to look for a tag.
     * Only available if the mission is init (if the drone has taken off)
     */
    void allow_orders_to_squares() ;

    /** Forbid the user to ask for the drone to look for a tag.
     * The user is forbidden if the mission is stopped or paused, or started.
     */
    void forbid_orders_to_squares() ;

    /** Display information about a searched square during a mission
     */
    void display_position() ;

    /** Hide any information on the Interface about searching for a square
     */
    void hide_position() ;

    /** Display "No Communication" for every information the user can access on the Interface
     * No communication displayed if the connexion is not established
     */
    void display_no_communication();

    /** Set colors on the playground's squares
     * Set the icons if the drone is flying
     */
    void set_icons_playground_with_communication();

    /** Set the playground in "no communication" mode : set the squares' icons in gray
     * If the communication is lost or if the mission has not yet been in state_ready
     */
    void set_icons_playground_without_communication();

    /** Mark a square as found if the drone has found it at the end of the mission
     * The square is marked with a circle or a cross, according to the player who marked the square
     * @param int square : square to be marked
     */
    void mark_square_found(int square) ;

    /** Set the icons of the scenario list (takeoff, start scenario, land, emergency) as enable
     * If the connexion is established
     */
    void set_icons_scenario_enable();

    /** Set the icons of the scenario list (takeoff, start scenario, land, emergency) as not enable
     * If the connexion is not established
     */
    void set_icons_scenario_not_enable();


/**********************************************************************************/
/* Private attributes                                                             */
/**********************************************************************************/

    mission_state state_of_mission ; /*!< Current state of the mission : stopped, ready, init, started, stopped_emergency */

    int joueur ; /*!< Current player : 0 or 1 */

    Ui::MainWindow *ui; /*!< Main window of the Interface, developed in mainwindow.ui */
    client C ; /*!< CLient for the TCP connexion */

    int battery_level ; /*!< Battery level of the drone to be updated periodically */
    state_of_flight flight_state ; /*!< Flight status of the drone to be updated periodically  : flying or landed */
    int emergency_status; /*!< emergency status representative of a bool to be updated periodically : in emergency mode or not */

    int num_scenario ; /*!< Number of the current scenario to be played : 1, 2 or 3 */
    bool scenario_mode ; /*!< Boolean to know if the drone is playing a scenario or not */

    QTimer * timer ; /*!< Timer to create a sleep between 2 missions */
    int next_square ; /*!< Next square to be targetted after a move is ended */

};

#endif // MAINWINDOW_H
