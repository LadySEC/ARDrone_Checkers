#include "keyboard.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/**********************************************************************************/
/* Threads & Procedures														      */
/**********************************************************************************/
/* Enbale user inputs */
void keyboard_rawMode(int I_enable)
{
    static struct termios Cooked;
    static int            Raw_enabled = 0u;
    struct termios 		  Raw;

    if(Raw_enabled == I_enable)
        return;

    if(I_enable)
    {
        tcgetattr(STDIN_FILENO, &Cooked);

        Raw = Cooked;
        cfmakeraw(&Raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &Raw);
    }
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &Cooked);

    Raw_enabled = I_enable;
}

/* Detect if a keyboard key has been pressed */
int keyboard_hit(void)
{
    struct timeval Tv = {0, 0};
    fd_set         Readfds;

    FD_ZERO(&Readfds);
    FD_SET(STDIN_FILENO, &Readfds);

    return select(STDIN_FILENO + 1, &Readfds, NULL, NULL, &Tv) == 1;
}

/* Read special characters from keyboard */
unsigned char keyboard_getchar(void)
{
	unsigned char character = 0;

	character = getchar();

	/* Bytes management for reading special characters */
	if(character == 0x1B)
	{
		character = getchar();
		if(character ==	0x5B)
			character = getchar();
	}

	return(character);
}