/**
 * \file 	global.h
 * \brief 	Common declarations useful for the interface and for the TCP socket on the client's side
 * \author 	Lady team
 * \version 1.0
 * \date 	9 January 2015
 *
 */

#ifndef GLOBAL_H
#define GLOBAL_H

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/

#include <QString>

/**********************************************************************************/
/* Constants for the GUI's icons according to the OS used                         */
/**********************************************************************************/

#ifdef __unix__
    static const QString DRONE_IMAGE_PATH = "../tags/drone.png";
    static const QString PATH_TO_CIRCLE = "../tags/black_circle.png" ;
    static const QString PATH_TO_CROSS = "../tags/black_cross.png" ;
    static const QString EMERGENCY_BUTTON_PATH = "../tags/emergency.png" ;
    static const QString START_PATH = "../tags/drone_takeoff.png" ;
    static const QString STOP_PATH = "../tags/drone_landing.png" ;
    static const QString RESET_PATH = "../tags/reset.png" ;
    static const QString START_SCENARIO_PATH = "../tags/start.png" ;
    static const QString STOP_SCENARIO_PATH = "../tags/stop.png" ;

#elif defined(_WIN32) || defined(WIN32)
    static const QString DRONE_IMAGE_PATH = "..\\..\\tags\\drone.png";
    static const QString PATH_TO_CIRCLE = "..\\..\\tags\\black_circle.png" ;
    static const QString PATH_TO_CROSS = "..\\..\\tags\\black_cross.png" ;
    static const QString EMERGENCY_BUTTON_PATH = "..\\..\\tags\\emergency.png" ;
    static const QString START_PATH = "..\\..\\tags\\drone_takeoff.png";
    static const QString STOP_PATH = "..\\..\\tags\\drone_landing.png" ;
    static const QString RESET_PATH = "..\\..\\tags\\reset.png" ;
    static const QString START_SCENARIO_PATH = "..\\..\\tags\\start.png" ;
    static const QString STOP_SCENARIO_PATH = "..\\..\\tags\\stop.png" ;

#endif


/**********************************************************************************/
/* Constants                                                                      */
/**********************************************************************************/

static QString NO_COMMUNICATION = "No communication" ; /*!< String to be displayed on the Interface if no connexion between the supervisor and the drone */
static QString STATE_IN_FLIGHT = "Drone flying" ; /*!< String to display if the drone is flying */
static QString STATE_LANDED = "Drone landed" ; /*!< String to display if the drone is landed */
static int NUM_PORT_CLIENT = 4000 ; /*< Constant socket's pin number for the TCP connexion */
static QString ADDR_IP_CLIENT = "192.168.1.1"; /*< Constant Interface's IP Address for the TCP connexion */


/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/

/**
 * \struct 	mission_state
 * \brief 	Defines a state machine for the mission
 */
typedef enum
{
    mission_stopped, /*!< When no connexion between the drone and the supervisor or when the mission is stopped through the Interface */
    mission_ready, /*!< When the connexion is established, and the drone is landed, or after going out of the emergency mode */
    mission_init, /*!< State of mission when the drone has taken off and can begin a mission */
    mission_started, /*!< State of mission when the mission is started */
    mission_paused, /*!< State of mission when the mission is paused through the Interface */
    mission_stopped_emergency /*!< State of mission when the mission was paused due to an emergency stop */
    
} mission_state ;

/**
 * \struct 	state_of_flight
 * \brief 	Defines a state machine for the drone : in flight or landed
 */
typedef enum
{
    drone_flying , /*!< Drone flying */
    drone_landed /*!< Drone landed */

} state_of_flight;


/**********************************************************************************/
/* Public Methods                                                                 */
/**********************************************************************************/

/** Convert mission_state to String
 * @param mission_state current_state
 * @return string mission_state converted to string
 */
QString mission_state_to_QString(mission_state current_state) ;

/** Convert state_of_flight to String
 * @param state_of_flight flight
 * @return string state_of_flight converted to string
 */
QString flight_status_to_QString(state_of_flight flight) ;

#endif // GLOBAL_H
