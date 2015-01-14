/**
 * \file    keyboard.c
 * \brief   Process keyboard entries
 * \author  Lady team
 * \version 1.0
 * \date    14 January 2015
 *
 */
#include "keyboard.h"

/**********************************************************************************/
/* Global variables 								                              */
/**********************************************************************************/
/* Mission state */
T_bool G_triggered_mission      = FALSE;

/**********************************************************************************/
/* Static functions prototypes                                                    */
/**********************************************************************************/
/**
 * \fn      static int keyboard_hit(void)
 * \brief   Scans keyboard keys
 *
 * \return  1: a key has just been pressed, 0: noting has happened
 */
static int keyboard_hit(void);

/**********************************************************************************/
/* Procedures								                                      */
/**********************************************************************************/
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
/* Static functions                                                               */
/**********************************************************************************/
static int keyboard_hit(void)
{
    struct timeval Tv = {0, 0};
    fd_set         Readfds;

    FD_ZERO(&Readfds);
    FD_SET(STDIN_FILENO, &Readfds);

    return select(STDIN_FILENO + 1, &Readfds, NULL, NULL, &Tv) == 1;
}

/**********************************************************************************/
/* Getters                                                                        */
/**********************************************************************************/
T_bool get_mission(void)
{
    return G_triggered_mission;
}

/**********************************************************************************/
/* Setters                                                                        */
/**********************************************************************************/
void stop_mission(void)
{
    G_triggered_mission = FALSE;
}

/**********************************************************************************/
/* Threads                                                                        */
/**********************************************************************************/
void*  kbd_thread_drone_controller(void * args)
{

    /* Declarations */
    unsigned char   key_pressed     = 0;
    unsigned int    key_selected    = 0;
    unsigned int    counter;

    LOG_WriteLevel(LOG_INFO, "keyboard : thread set to aperiodic");
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
			                LOG_WriteLevel(LOG_INFO, "keyboard : ENTER_KEY pressed -> TAKEOFF");
                            while(ATcommand_FlyingState() != TRUE);
                        }
                        else
                        {
                            /* Landing */
                            ATcommand_process(LANDING);
                            /* Wait the landing state */
			                LOG_WriteLevel(LOG_INFO, "keyboard : ENTER_KEY pressed -> LANDING");
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
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(PITCH_DOWN, DEFAULT_DELAY);
                #else
                    incDynamicParameter(PITCH_ANGLE, ANGLE_DEFAULT_INC);
                #endif
                    break;

                case DOWN_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(PITCH_UP, DEFAULT_DELAY);
                #else
                    incDynamicParameter(PITCH_ANGLE, -ANGLE_DEFAULT_INC);
                #endif
                    break;

                case LEFT_KEY   :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(YAW_LEFT, DEFAULT_DELAY);
                #else
                    incDynamicParameter(YAW_ANGLE, ANGLE_DEFAULT_INC);
                #endif
                    break;

                case RIGHT_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(YAW_RIGHT, DEFAULT_DELAY);
                #else
                    incDynamicParameter(YAW_ANGLE, -ANGLE_DEFAULT_INC);
                #endif
                    break;

                case Z_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(VERTICAL_UP, DEFAULT_DELAY);
                #else
                    incDynamicParameter(VERTICAL_THRUST, ANGLE_DEFAULT_INC);
                #endif
                    break;

                case S_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(VERTICAL_DOWN, DEFAULT_DELAY);
                #else
                    incDynamicParameter(VERTICAL_THRUST, -ANGLE_DEFAULT_INC);
                #endif
                    break;

                case Q_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(ROLL_LEFT, DEFAULT_DELAY);
                #else
                    incDynamicParameter(ROLL_ANGLE, ANGLE_DEFAULT_INC);
                #endif
                    break;

                case D_KEY :
                #ifdef ENABLE_DRONE_CONTROL_KEYBOARD
                    ATcommand_moveDelay(ROLL_RIGHT, DEFAULT_DELAY);
                #else
                    incDynamicParameter(ROLL_ANGLE, -ANGLE_DEFAULT_INC);
                #endif
                    break;

                case W_KEY :
                    break;

                case X_KEY :
                    /* Exit */
                    LOG_WriteLevel(LOG_INFO, "keyboard : X_KEY pressed -> EXIT");
                    supervisor_setDisconnection(TRUE);
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
#ifndef ENABLE_SUPERVISOR
    while(key_selected != X_KEY);
#else
    while(1);
#endif

    /* Disable the raw mode */
    keyboard_rawMode(FALSE);

    /* Close this thread */
    pthread_exit(NULL);
}

