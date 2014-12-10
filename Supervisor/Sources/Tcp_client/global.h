#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

    static const QString ICON_RED_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_rectangle.jpg";
    static const QString ICON_BLUE_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_rectangle.jpg";
    static const QString ICON_GREEN_RECTANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_rectangle.jpg";
    static const QString ICON_RED_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_triangle.jpg";
    static const QString ICON_BLUE_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_triangle.jpg";
    static const QString ICON_GREEN_TRIANGLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_triangle.jpg";
    static const QString ICON_RED_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_circle.jpg";
    static const QString ICON_BLUE_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/blue_circle.jpg";
    static const QString ICON_GREEN_CIRCLE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_circle.jpg";
    static const QString DRONE_IMAGE_PATH = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/drone.png";


#elif defined(_WIN32) || defined(WIN32)   /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
    static const QString ICON_RED_RECTANGLE_PATH = "..\\..\\..\\tags\\red_rectangle.jpg";
    static const QString ICON_BLUE_RECTANGLE_PATH = "..\\..\\..\\tags\\blue_rectangle.jpg";
    static const QString ICON_GREEN_RECTANGLE_PATH = "..\\..\\..\\tags\\green_rectangle.jpg";
    static const QString ICON_RED_TRIANGLE_PATH = "..\\..\\..\\tags\\red_triangle.jpg";
    static const QString ICON_BLUE_TRIANGLE_PATH = "..\\..\\..\\tags\\blue_triangle.jpg";
    static const QString ICON_GREEN_TRIANGLE_PATH = "..\\..\\..\\tags\\green_triangle.jpg";
    static const QString ICON_RED_CIRCLE_PATH = "..\\..\\..\\tags\\red_circle.jpg";
    static const QString ICON_BLUE_CIRCLE_PATH = "..\\..\\..\\tags\\blue_circle.jpg";
    static const QString ICON_GREEN_CIRCLE_PATH = "..\\..\\..\\tags\\green_circle.jpg";

#endif



static QString NO_COMMUNICATION = "No communication" ;
static QString STATE_IN_FLIGHT = "Drone flying" ;
static QString STATE_LANDED = "Drone landed" ;

typedef enum
{
    mission_stopped,
    mission_started,
    mission_paused,
    mission_ready,
    mission_init
    
} mission_state ;

QString mission_state_to_QString(mission_state current_state) ;

static int NUM_PORT_CLIENT = 4000 ;
static QString ADDR_IP_CLIENT = "192.168.1.1";


#endif // GLOBAL_H
