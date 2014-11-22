/**
 * \file    keyboard.h
 * \brief   Process keyboard entries
 * \author  Lady team
 * \version 1.0
 * \date    21 november 2014
 *
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include <termios.h>

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/


/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
typedef enum
{
	UP_KEY 				= 0x41u,
	DOWN_KEY 			= 0x42u,
	LEFT_KEY 			= 68u,
	RIGHT_KEY			= 67u,
 	ENTER_KEY			= 0x0Du,
	SPACE_KEY			= 32u,		
	CTRL_C_KEY			= 0x03u,
	L_KEY    			= 108u,
	D_KEY 				= 100u,
	Q_KEY 				= 113u,
	E_KEY 				= 101u,
	A_KEY  				= 97u,
	Z_KEY				= 122u,
	S_KEY 				= 115u,
	BACKSPACE_KEY    	= 8u
} T_keys;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
void 			keyboard_rawMode(T_bool I_enable);
int 			keyboard_hit(void);
unsigned char 	keyboard_getchar(void);

#endif //! _KEYBOARD_H_