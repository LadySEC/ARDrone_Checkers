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
#include <termios.h>											/*!< */
#include "at_command.h"											/*!< */
#include "supervisor.h"											/*!< */

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
 /**
 * \struct 	T_keys
 * \brief 	Defines all keyboard keys which interact with the program
 */
typedef enum
{
	UP_KEY 				= 0x41u,								/*!< */
	DOWN_KEY 			= 0x42u,								/*!< */
	LEFT_KEY 			= 68u,									/*!< */
	RIGHT_KEY			= 67u,									/*!< */
 	ENTER_KEY			= 0x0Du,								/*!< */
	SPACE_KEY			= 32u,									/*!< */
	CTRL_C_KEY			= 0x03u,								/*!< */
	L_KEY    			= 108u,									/*!< */
	D_KEY 				= 100u,									/*!< */
	Q_KEY 				= 113u,									/*!< */
	E_KEY 				= 101u,									/*!< */
	A_KEY  				= 97u,									/*!< */
	Z_KEY				= 122u,									/*!< */
	S_KEY 				= 115u,									/*!< */
	M_KEY				= 109u,									/*!< */
	W_KEY				= 119u,									/*!< */
	X_KEY 				= 120u,									/*!< */
	BACKSPACE_KEY		= 8u 									/*!< */
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
