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
/* Keyboard keys */


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
	BACKSPACE_KEY    	= 8u
} T_keys;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
void 			keyboard_rawMode(int I_enable);
int 			keyboard_hit(void);
unsigned char 	keyboard_getchar(void);

#endif //! _KEYBOARD_H_