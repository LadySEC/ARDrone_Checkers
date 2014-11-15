#include "global.h"

/* Lady team libraries */
#include "keyboard.h"
#include "at_command.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* States */
unsigned char 	flying 					= 0u;

/**********************************************************************************/
/* Threads & Procedures														      */
/**********************************************************************************/

/**********************************************************************************/
/* Main program													      			  */
/**********************************************************************************/
int main (int argc, char *argv[])
{
	/* Declarations */
	unsigned char  	key_pressed  	= 0;
	unsigned int   	key_selected	= 0;
	/* Thread */
	pthread_t 		thread1;


	printf("Start\n\r");
	/* Initialize the communication with the server */
	ATcommand_initiate();
	/* Initialize the threads */
	pthread_create (&thread1, NULL, ATcommand_thread_movements, NULL);
	/* Activate the terminal for raw mode */
	keyboard_rawMode(1u);
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
	            case UP_KEY	:
	            	ATcommand_process(PITCH_DOWN);
                	break;

	            case DOWN_KEY :
	            	ATcommand_process(PITCH_UP);
                	break;

                case LEFT_KEY	:
	            	ATcommand_process(YAW_LEFT);
                	break;

	            case RIGHT_KEY :
	            	ATcommand_process(YAW_RIGHT);
                	break;

                case ENTER_KEY :
                	ATcommand_process(CONFIGURATION_IDS);
                	ATcommand_process(LED_ANIMATION);

	            	if(flying == 0u)
	            	{
	            		/* Calibrate the drone */
						ATcommand_process(CALIBRATION);
						sleep(2);
	            		ATcommand_process(TAKEOFF);
	            		sleep(5);
	            		flying = 1u;
	            	}
	            	else
	            	{
	            		ATcommand_process(LANDING);
	            		flying = 0u;
	            		/* Security */
	            		usleep(1000000);
	            	}
                	break;

                case SPACE_KEY :
	            	ATcommand_process(VERTICAL_UP);
                	break;

                case BACKSPACE_KEY :
                	ATcommand_process(VERTICAL_DOWN);
                	break;

                case L_KEY :
                	ATcommand_process(CONFIGURATION_IDS);
                	ATcommand_process(LED_ANIMATION);
                	ATcommand_process(EMERGENCY);
                	break;

                case E_KEY :
                	ATcommand_process(EMERGENCY);
                	break;

                case Q_KEY :
                	ATcommand_process(ROLL_LEFT);
                	break;

                case D_KEY :
                	ATcommand_process(ROLL_RIGHT);
                	break;

                case A_KEY :
                	ATcommand_process(CALIBRATION);
                	break;
	        }
        }

        /* Empty the output buffer */
		fflush(stdout);
	}
	while(key_selected != CTRL_C_KEY);

	printf("\n\rEnd");

	/* Disable the raw mode */
	keyboard_rawMode(0u);

	/* Close current threads */
   	pthread_cancel(thread1);
    /* Close all communications */
    ATcommand_close();

	return(0);
}
