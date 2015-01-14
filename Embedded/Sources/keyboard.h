/**
 * \file    keyboard.h
 * \brief   Process keyboard entries
 * \author  Lady team
 * \version 1.0
 * \date    14 January 2015
 *
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"												/*!< Retrieve all common tools */
#include <termios.h>											/*!< Enable the user to interact with the terminal */
#include "at_command.h"											/*!< Send AT commands */
#include "supervisor.h"											/*!< Close the supervisor's thread if necessary */

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
 /**
 * \struct 	T_keys
 * \brief 	Defines all keyboard keys which interact with the program
 */
typedef enum
{
	UP_KEY 				= 0x41u,								/*!< Up arrow key: PITCH DOWN order or decresase pitch angle */
	DOWN_KEY 			= 0x42u,								/*!< Down arrow key: PITCH UP order or incresase pitch angle */
	LEFT_KEY 			= 68u,									/*!< Left arrow key: YAW LEFT order or decresase yaw angle */
	RIGHT_KEY			= 67u,									/*!< Right arrow key: YAW RIGHT order or incresase yaw angle  */
 	ENTER_KEY			= 0x0Du,								/*!< Enter key: TAKEOFF/LANDING order */
	SPACE_KEY			= 32u,									/*!< Space key: FLAT TRIM order */
	CTRL_C_KEY			= 0x03u,								/*!< CTRL+C combination value: not used */
	L_KEY    			= 108u,									/*!< L key: LED ANIMATION order */
	D_KEY 				= 100u,									/*!< D key: ROLL RIGHT order or decrease roll angle */
	Q_KEY 				= 113u,									/*!< Q key: ROLL LEFT order or increase roll angle */
	E_KEY 				= 101u,									/*!< E key: enable/disable emergency mode */
	A_KEY  				= 97u,									/*!< A key: not used */
	Z_KEY				= 122u,									/*!< Z key: VERTICAL UP order or increase vertical thrust */
	S_KEY 				= 115u,									/*!< S key: VERTICAL DOWN order or decrease vertical thrust */
	M_KEY				= 109u,									/*!< M key: enable/disable a mission manually (not used) */
	W_KEY				= 119u,									/*!< W key: not used */
	X_KEY 				= 120u,									/*!< X key: close the program */
	BACKSPACE_KEY		= 8u 									/*!< Backspace key: change the WiFi name */
} T_keys;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
/**
 * \fn      void keyboard_rawMode(T_bool I_enable)
 * \brief   Enables user's keyboard entries in the shell
 *
 * \param   I_enable    TRUE: enable, FALSE: disable
 */
void 					keyboard_rawMode(T_bool I_enable);

/**
 * \fn      unsigned char keyboard_getchar(void)
 * \brief   Process a special character from a keyboard entry 
 *
 * \return  Character value  
 */
unsigned char 	       	keyboard_getchar(void);

/**********************************************************************************/
/* Getters														     		  	  */
/**********************************************************************************/
/**
 * \fn      T_bool get_mission(void)
 * \brief   Gives the state mission
 *
 * \return  TRUE: a mission is running, FALSE: no mission launched 
 */
T_bool					get_mission(void);

/**********************************************************************************/
/* Setters														     		  	  */
/**********************************************************************************/
/**
 * \fn      void stop_mission(void)
 * \brief   Stops the current mission
 */
void 					stop_mission(void);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
/**
 * \fn      void*  kb_thread_drone_controller(void * args)
 * \brief   Thread that control the drone through the keyboard interface
 *
 * \param   arg     Input argument 
 *
 * \return          Nothing
 *
 *  Tasks:
 *      - Read the keyboard inputs
 *      - Perform actions according to the hit key 
 *      - Can close the program
 */
void*  					kbd_thread_drone_controller(void * args);

#endif //! _KEYBOARD_H_
