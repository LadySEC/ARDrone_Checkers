/**
 * \file    kbd_control.h
 * \brief   Process keyboard entries to control the drone
 * \author  Lady team
 * \version 1.0
 * \date    22 november 2014
 *
 */
#ifndef _KBD_CONTROL_H_
#define _KBD_CONTROL_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include "keyboard.h"
#include "at_command.h"

/**********************************************************************************/
/* Prototype													      			  */
/**********************************************************************************/
void*  kbd_thread_drone_controller(void * args);

#endif //! _KEYBOARD_H_
