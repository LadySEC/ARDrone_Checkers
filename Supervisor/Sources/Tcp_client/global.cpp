#include "global.h"


QString mission_state_to_QString(mission_state current_state)
{
    if (current_state == mission_ready)
        return "Mission ready" ;
    else if (current_state == mission_paused)
        return "Mission paused" ;
    else if (current_state == mission_init)
        return "Mission initialized" ;
    else if (current_state == mission_started)
        return "Mission started" ;
    else if (current_state == mission_stopped)
        return "Mission stopped" ;
    else if (current_state == mission_stopped_emergency)
        return "EMERGENCY LANDING" ;
}


QString flight_status_to_QString(state_of_flight flight)
{
    if (flight == drone_landed)
        return STATE_LANDED;
    else if (flight == drone_flying)
        return STATE_IN_FLIGHT ;
}
