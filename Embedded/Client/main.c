/**
 * \file 	main.c
 * \brief 	Main program of the AR-drone embedded client
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include "keyboard.h"
#include "supervisor.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/**********************************************************************************/
/* Procedures														      */
/**********************************************************************************/

/**********************************************************************************/
/* Main program													      			  */
/**********************************************************************************/
/**
 * \fn 		int main (int argc, char *argv[])
 * \brief 	Program entry
 *
 * \param 	argc 	Input argument
 * \param 	argv  	Input arguments
 * \return 			Program output
 */
int main (int argc, char *argv[])
{
	/* Declarations */
	unsigned char  	key_pressed  	= 0;
	unsigned int   	key_selected	= 0;
	/* Thread */
	pthread_t 		thread1;
#ifdef ENABLE_SUPERVISOR
	pthread_t 		thread2;
#endif


	printf("Start\n\r");

#ifdef ENABLE_SUPERVISOR
	/* Initialize the supervisor thread (blocking function) */
	printf("\n\rInitiating communication with the supervisor");
	if(supervisor_initiate() == NO_ERROR)
	{
		pthread_create (&thread2, NULL, supervisor_thread_interact, NULL);
	}
	else
	{
		printf("\n\rUnable to connect the supervisor");
	}
#endif

	/* Initialize the communication with the Parrot server */
	printf("\n\rInitiating communication with the Parrot server");
	if(ATcommand_initiate() == NO_ERROR)
	{
		/* Initialize the movements thread */
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
		        	case ENTER_KEY :
	                	ATcommand_process(CONFIGURATION_IDS);
	                	ATcommand_process(LED_ANIMATION);

		            	if(ATcommand_FlyingState() == FALSE)
		            	{
		            		/* Flat trim */
		            		ATcommand_process(TRIM);
							sleep(2u);
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

	                case Z_KEY :
	                	ATcommand_process(VERTICAL_UP);
	                	break;

	                case S_KEY :
	                	ATcommand_process(VERTICAL_DOWN);
	                	break;

	                case Q_KEY :
	                	ATcommand_process(ROLL_LEFT);
	                	break;

	                case D_KEY :
	                	ATcommand_process(ROLL_RIGHT);
	                	break;

	                case SPACE_KEY :
		            	ATcommand_process(TRIM);
	                	break;

	                case BACKSPACE_KEY :
	                	
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

#ifdef ENABLE_SUPERVISOR	   	
	    pthread_cancel(thread2);
	    supervisor_close();
#endif
	}

	return(0);
}
