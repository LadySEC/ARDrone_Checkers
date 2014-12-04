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
#include "detect_tag_wrapper.h"
/**********************************************************************************/
/* Constants 							  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/

/**********************************************************************************/
/* Procedures									*/
/**********************************************************************************/
extern Position position_tag;
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
	int cpt_mission = 0;
	int x = 0, y = 0, found_ou_pas_found = 0;
	Position pos_tag;

    	/* Make this thread periodic */
    	struct periodic_info info;
    	make_periodic (_CALCUL_PERIOD, &info);

    	while(1)
    	{
		/* Triggered with 'M_KEY' if you are not executing one mission*/
		if(get_mission() == TRUE)
		{
	
			if(cpt_mission == 0)
			{
				printf("\n\r\rMISSION - Beggin the mission");
			}
			else
			{
				/*If the drone is in flight phase*/
				if(ATcommand_FlyingState() == TRUE)
				{
					printf("\n\r\rMISSION - Seek the tag");
					//pos_tag = detect_wrapper("MOMO","triangle");
					x 			= position_tag.abs;
					y 			= position_tag.ord;
					found_ou_pas_found 	= position_tag.found;
					
					if(found_ou_pas_found == 1)
					{
						if(x < _PIXEL_X_MIDDLE)
						{
							if(y < _PIXEL_Y_MIDDLE)
							{
								//En bas à gauche
								printf("\n\r\rMISSION - PITCH_UP");
								printf("\n\r\rMISSION - ROLL_LEFT");
							}
							else
							{
								//En haut à gauche
								printf("\n\r\rMISSION - PITCH_DOWN");
								printf("\n\r\rMISSION - ROLL_LEFT");	
							}
						}
						else
						{	if(y < _PIXEL_Y_MIDDLE)
							{
								//En En bas à  droite
								printf("\n\r\rMISSION - PITCH_UP");
								printf("\n\r\rMISSION - ROLL_RIGHT");
							}
							else
							{
								//En haut à droite
								printf("\n\r\rMISSION - PITCH_DOWN");
								printf("\n\r\rMISSION - ROLL_WRITE");	
							}	
						}				
					}
					else
					{
						printf("\n\r\rMISSION - HOVERING");	
					}
				}
				else
				{
					printf("\n\r\rMISSION - You have to take off !");					
				}
			}
			
		}	
		cpt_mission ++;
		printf("\n\r\rMISSION - cpt = %d",cpt_mission);

        	/* Wait until the next period is achieved */
        	wait_period (&info);
    	}

    	printf("\n\rEnding calcul_order_thread");

    	return(NULL);
}
