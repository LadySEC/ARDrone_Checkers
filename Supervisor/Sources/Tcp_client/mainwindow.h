#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "global.h"
#include <QDebug>

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
    void open_connexion();

    void mark_connexion() ;
    void unmark_connexion() ;

    void start_mission ();
    void stop_mission();
    void pause_mission();

    void send_takeoff() ;
    void send_landing() ;
    void send_exit() ;

    void send_M_Bl_Re() ;
    void send_M_Bl_Tr() ;
    void send_M_Bl_Ci() ;
    void send_M_Ro_Re() ;
    void send_M_Ro_Tr() ;
    void send_M_Ro_Ci() ;
    void send_M_Gr_Re() ;
    void send_M_Gr_Tr() ;
    void send_M_Gr_Ci() ;

private:

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


    Ui::MainWindow *ui;
    client C ;
};

#endif // MAINWINDOW_H
