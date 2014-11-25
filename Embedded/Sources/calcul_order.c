/**
 * \file 	calcul_order.c
 * \brief 	Make the calculation for the next drone orders
 * \author 	Lady team
 * \version 1.0
 * \date 	23 november 2014
 *
 */
/**********************************************************************************/
/* Libraries									*/
/**********************************************************************************/
#include "calcul_order.h"
#include "keyboard.h"
/**********************************************************************************/
/* Constants 							  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/

/**********************************************************************************/
/* Procedures									*/
/**********************************************************************************/

/**********************************************************************************/
/* Threads									*/
/**********************************************************************************/
/**
 * \fn 		void* calcul_order_thread(void* arg)
 * \brief 	Thread which receive the tag position and calcul the next orders
 * \param 	arg 	Input argument
 * \return  		Nothing
 *
 * This thread reads received datas from the image processing thread
 * And then calcul the next orders
 */
void* calcul_order_thread(void* arg)
{
    int cpt_AT_cmd = 0;

    /* Make this thread periodic */
    struct periodic_info info;
    make_periodic (_CALCUL_PERIOD, &info);


    while(1)
    {
	/* Triggered with 'M_KEY' if you are not executing one mission*/
	if(get_mission() == TRUE)
	{
		printf("\n\r---------------------------------------------------");
		printf("\n\rMISSION - Beggin/Continue the mission");
		printf("\n\r---------------------------------------------------");

		/*If the drone is in flight phase*/
		if(ATcommand_FlyingState() == TRUE)
		{
			for(cpt_AT_cmd = 0; cpt_AT_cmd < 45; cpt_AT_cmd ++)
			{
				if(get_mission() == TRUE)
				{
					ATcommand_process(PITCH_DOWN);	
				}
			}
			printf("\n\rMISSION - PITCH_DOWN");

			for(cpt_AT_cmd = 0; cpt_AT_cmd < 45; cpt_AT_cmd ++)
			{
				if(get_mission() == TRUE)
				{
					ATcommand_process(ROLL_LEFT);
				}
			}
			printf("\n\rMISSION - ROLL_LEFT");

			
		}
	}	

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    printf("\n\rEnding calcul_order_thread");

    return(NULL);
}
