#ifndef GLOBAL_H
#define GLOBAL_H

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
    /*
    static const QString ICON_GREEN_START = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/green_start.jpg";
    static const QString ICON_ORANGE_PAUSE = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/orange_pause.jpg";
    static const QString ICON_RED_STOP = "/home/fabrice/ARDrone_Checkers/Supervisor/Sources/Tcp_client/tags/red_stop.jpg";
    */

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#endif






static int NUM_PORT_CLIENT = 4000 ;
static QString ADDR_IP_CLIENT = "192.168.1.1";

#endif // GLOBAL_H
