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
