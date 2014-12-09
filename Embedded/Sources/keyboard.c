/**
 * \file    keyboard.c
 * \brief   Process keyboard entries
 * \author  Lady team
 * \version 1.0
 * \date    4 December 2014
 *
 */
#include "keyboard.h"

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/
T_bool G_triggered_mission      = FALSE;
T_bool G_reconnect_supervisor   = FALSE;

/**********************************************************************************/
/* Threads & Procedures								*/
/**********************************************************************************/
/**
 * \fn      void keyboard_rawMode(T_bool I_enable)
 * \brief   Enables user's keyboard entries in the shell
 *
 * \param   I_enable    TRUE: enable, FALSE: disable
 */
void keyboard_rawMode(T_bool I_enable)
{
    static struct termios Cooked;
    static int            Raw_enabled = 0u;
    struct termios 		  Raw;

    if(Raw_enabled == I_enable)
        return;

    if(I_enable == TRUE)
    {
        tcgetattr(STDIN_FILENO, &Cooked);

        Raw = Cooked;
        cfmakeraw(&Raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &Raw);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &Cooked);
    }

    Raw_enabled = (int)I_enable;
}

/**
 * \fn      int keyboard_hit(void)
 * \brief   Informs if a key has just been pressed by the user
 *
 * \return  1: Key pressed, 0: Nothing has happened 
 */
int keyboard_hit(void)
{
    struct timeval Tv = {0, 0};
    fd_set         Readfds;

    FD_ZERO(&Readfds);
    FD_SET(STDIN_FILENO, &Readfds);

    return select(STDIN_FILENO + 1, &Readfds, NULL, NULL, &Tv) == 1;
}

/**
 * \fn      unsigned char keyboard_getchar(void)
 * \brief   Process a special character from a keyboard entry 
 *
 * \return  Character value  
 */
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

/**********************************************************************************/
/* Threads                                                                        */
/**********************************************************************************/
/**
 * \fn      void*  kb_thread_drone_controller(void * args)
 * \brief   Thread that control the drone through the keyboard interface
 *
 * \param   arg     Input argument 
 * \return          Nothing
 *
 * This thread read the keyboards input
 * And then process them to control the drone 
 */
void*  kbd_thread_drone_controller(void * args)
{

    /* Declarations */
    unsigned char   key_pressed     = 0;
    unsigned int    key_selected    = 0;
    unsigned int    counter;

    /* Activate the terminal for raw mode */
    keyboard_rawMode(TRUE);
    /* Infinite loop */
    do
    {
        /* Test */
        key_pressed = keyboard_hit();

        if(key_pressed)
        {
            /* Read the selected key */
            key_selected = keyboard_getchar();

            switch(key_selected)
            {
                case ENTER_KEY :
                    if(ATcommand_enoughBattery() == TRUE)
                    {
                        if(ATcommand_FlyingState() == FALSE)
                        {
                        #ifdef ENABLE_CONFIG_VIDEO
                            /* Enable the bottom camera */
                            ATcommand_process(CONFIGURATION_IDS);
                            ATcommand_process(ENABLE_VISION);
                        #endif

                            /* Flat trim */
                            ATcommand_process(TRIM);
                            sleep(2u);
                            /* Take off */
                            ATcommand_process(TAKEOFF);
                            /* Wait the flying state */
			                printf("\n\r\rINFO : TAKEOFF (ENTER)");
                            while(ATcommand_FlyingState() != TRUE);
                        }
                        else
                        {
                            /* Landing */
                            ATcommand_process(LANDING);
                            /* Wait the landing state */
			                printf("\n\r\rINFO : LANDING (ENTER)");
                            while(ATcommand_FlyingState() != FALSE);

                        #ifdef ENABLE_CONFIG_VIDEO
                            /* Disable the bottom camera */
                            ATcommand_process(CONFIGURATION_IDS);
                            ATcommand_process(DISABLE_VISION);
                        #endif
                        }
                    }
                    else
                    {
                        /* Not enough battery to takeoff */
                        ATcommand_process(CONFIGURATION_IDS);
                        ATcommand_process(LED_ANIMATION);
                    }
                    break;

                case UP_KEY :
                    ATcommand_moveDelay(PITCH_DOWN, DEFAULT_DELAY);
                    break;

                case DOWN_KEY :
                    ATcommand_moveDelay(PITCH_UP, DEFAULT_DELAY);
                    break;

                case LEFT_KEY   :
                    ATcommand_moveDelay(YAW_LEFT, DEFAULT_DELAY);
                    break;

                case RIGHT_KEY :
                    ATcommand_moveDelay(YAW_RIGHT, DEFAULT_DELAY);
                    break;

                case Z_KEY :
                    ATcommand_moveDelay(VERTICAL_UP, DEFAULT_DELAY);
                    break;

                case S_KEY :
                    ATcommand_moveDelay(VERTICAL_DOWN, DEFAULT_DELAY);
                    break;

                case Q_KEY :
                    ATcommand_moveDelay(ROLL_LEFT, DEFAULT_DELAY);
                    break;

                case D_KEY :
                    ATcommand_moveDelay(ROLL_RIGHT, DEFAULT_DELAY);
                    break;

                case W_KEY :
                    /* Reconnect the supervisor */
                    G_reconnect_supervisor = TRUE;
                    break;

                case X_KEY :
                    /* Exit */
                    printf("\n\rExit pushed");
                    break;

                case SPACE_KEY :
                    ATcommand_process(TRIM);
                    break;
                    
                case BACKSPACE_KEY :
                    /* Change SSID */
                    ATcommand_process(CONFIGURATION_IDS);
                    ATcommand_process(CHANGE_SSID);
                    break;

                case A_KEY :
                #if 1
    	            ATcommand_moveDelay(PITCH_DOWN,     800000);
    		        ATcommand_moveDelay(HOVERING_BUFF,  3000000);
    	    	    ATcommand_moveDelay(ROLL_LEFT,      800000);
                #else
                    ATcommand_moveDelay(VERTICAL_UP,    2000000);
                    ATcommand_moveDelay(ROLL_RIGHT,     1000000);
                    ATcommand_moveDelay(ROLL_LEFT,      1000000);
                    ATcommand_moveDelay(HOVERING_BUFF,  2000000);
    	            ATcommand_moveDelay(PITCH_DOWN,     1500000);
                    ATcommand_moveDelay(HOVERING_BUFF,  2000000);
    	    	    ATcommand_moveDelay(PITCH_UP,       1500000);
                    ATcommand_moveDelay(VERTICAL_DOWN,  2000000);
                #endif
                    break;

                case L_KEY :
                    ATcommand_process(CONFIGURATION_IDS);
                    ATcommand_process(LED_ANIMATION);
                    break;

                case E_KEY :
                    ATcommand_process(EMERGENCY);
                    break;

        		case M_KEY :
        		    if(G_triggered_mission == TRUE)
        		    {
                        	G_triggered_mission = FALSE;
        		    }
        		    else 
        		    {
            			G_triggered_mission = TRUE;
            		    }
                    break;
            }
        }

        /* Empty the output buffer */
        fflush(stdout);
    }
    while(key_selected != X_KEY);

    /* Disable the raw mode */
    keyboard_rawMode(FALSE);

    /* Close this thread */
    pthread_exit(NULL);
}

/**********************************************************************************/
/* Getters & Setters                                                              */
/**********************************************************************************/

void keyboard_setRecoSupervisor(T_bool value)
{
    G_reconnect_supervisor = value;
}

T_bool keyboard_getRecoSupervisor(void)
{
    return(G_reconnect_supervisor);
}

T_bool get_mission(void)
{
    return G_triggered_mission;
}

void stop_mission(void)
{
    G_triggered_mission = FALSE;
}
