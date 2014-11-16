#include "global.h"

/* Lady team libraries */
#include "keyboard.h"
#include "at_command.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

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

	/* Initialize the communication with the Parrot server */
	if(ATcommand_initiate() == NO_ERROR)
	{
		/* Initialize the threads */
		pthread_create (&thread1, NULL, ATcommand_thread_movements, NULL);
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

		            	if(ATcommand_FlyingState() == FALSE)
		            	{
		            		/* Calibrate the drone : flat trim */
							ATcommand_process(CALIBRATION);
							sleep(2);
							/* Take off */
		            		ATcommand_process(TAKEOFF);
		            		/* Wait the flying state */
		            		while(ATcommand_FlyingState() != TRUE);
		            	}
		            	else
		            	{
		            		/* Landing */
		            		ATcommand_process(LANDING);
		            		/* Wait the landing state */
		            		while(ATcommand_FlyingState() != FALSE);
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
	                	ATcommand_process(CONFIGURATION_IDS);
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
		keyboard_rawMode(FALSE);

		/* Close current threads */
	   	pthread_cancel(thread1);
	    /* Close all communications */
	    ATcommand_close();
	}

	return(0);
}
