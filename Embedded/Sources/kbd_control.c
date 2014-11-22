/**
 * \file    kbd_control.c
 * \brief   Process keyboard entries to control the drone
 * \author  Lady team
 * \version 1.0
 * \date    22 november 2014
 *
 */
#include "kbd_control.h"


/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
/**
 * \fn      void*  kb_thread_drone_controller(void * args)
 * \brief   Thread that control the drone through the keyboard interface
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 *
 * This thread read the keyboards input
 * And then process them to control the drone 
 */
void*  kbd_thread_drone_controller(void * args)
{

    /* Declarations */
    unsigned char  	key_pressed  	= 0;
    unsigned int   	key_selected	= 0;
    	unsigned int 	counter;

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
			            		/* Enable the bottom camera */
			            		ATcommand_process(CONFIGURATION_IDS);
			            		ATcommand_process(ENABLE_VISION);
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
			            		/* Disable the bottom camera */
			            		ATcommand_process(CONFIGURATION_IDS);
			            		ATcommand_process(DISABLE_VISION);
			            	}
		        		}
		        		else
		        		{
		        			/* Not enough battery to takeoff */
		        			ATcommand_process(CONFIGURATION_IDS);
	                		ATcommand_process(LED_ANIMATION);
		        		}
	                	break;

		            case UP_KEY	:
		            	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
		            		ATcommand_process(PITCH_DOWN);
		            	}
	                	break;

		            case DOWN_KEY :
		            	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
		            		ATcommand_process(PITCH_UP);
		            	}
	                	break;

	                case LEFT_KEY	:
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
		            		ATcommand_process(YAW_LEFT);
		            	}
	                	break;

		            case RIGHT_KEY :
		            	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
		            		ATcommand_process(YAW_RIGHT);
		            	}
	                	break;

	                case Z_KEY :
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
	                		ATcommand_process(VERTICAL_UP);
	                	}
	                	break;

	                case S_KEY :
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
	                		ATcommand_process(VERTICAL_DOWN);
	                	}
	                	break;

	                case Q_KEY :
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
	                		ATcommand_process(ROLL_LEFT);
	                	}
	                	break;

	                case D_KEY :
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
	                		ATcommand_process(ROLL_RIGHT);
	                	}
	                	break;

	                case SPACE_KEY :
		            	ATcommand_process(TRIM);
	                	break;

	                /* Sequence test */
	                case BACKSPACE_KEY :
	                	for(counter = 0u; counter < 10u; counter++)
		            	{
	                		ATcommand_process(VERTICAL_UP);
	                	}
	                	for(counter = 0u; counter < NB_ORDER_OCCUR; counter++)
		            	{
	                		ATcommand_process(VERTICAL_DOWN);
	                	}
	                	for(counter = 0u; counter < 10u; counter++)
		            	{
	                		ATcommand_process(PITCH_DOWN);
	                	}
	                	for(counter = 0u; counter < 10u; counter++)
		            	{
	                		ATcommand_process(YAW_LEFT);
	                	}
	                	for(counter = 0u; counter < 10u; counter++)
		            	{
	                		ATcommand_process(PITCH_DOWN);
	                	}
	                	break;

	                case A_KEY :
	                	/* Disable the bottom camera */
	            		ATcommand_process(CONFIGURATION_IDS);
	            		ATcommand_process(DISABLE_VISION);
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

}

