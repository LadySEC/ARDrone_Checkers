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
				printf("\n\r\r----- MISSION - Beggin the mission");
			}
			else
			{
				/*If the drone is in flight phase*/
				//if(ATcommand_FlyingState() == TRUE)
				//{
					//pos_tag = detect_wrapper("MOMO","triangle");
					x 			= position_tag.abs;
					y 			= position_tag.ord;
					found_ou_pas_found 	= position_tag.found;
					printf("\n\r\r----- MISSION - found = %d, x = %d, y=%d",found_ou_pas_found,x,y);
					if(found_ou_pas_found == 1)
					{
						//Si je suis au dessus du tag			
						if((x < _X_TOL_MAX && x > _X_TOL_MIN) && (y < _Y_TOL_MAX && y > _Y_TOL_MIN))
						{
							stop_mission();
							printf("\n\r\r----- MISSION - ****** END ****** LANDING");
						}
						//Si je ne suis pas au dessus du tag
						else
						{
							if(x < _PIXEL_X_MIDDLE)
							{
								if(y < _PIXEL_Y_MIDDLE)
								{
									//En bas à gauche
									printf("\n\r\r----- MISSION - je vais en bas/droite");
								}
								else
								{
									//En haut à gauche
									printf("\n\r\rMISSION - je vais en haut/droite");	
								}
							}
							else
							{	
								if(y < _PIXEL_Y_MIDDLE)
								{
									//En En bas à  droite
									printf("\n\r\r----- MISSION - je vais en bas/gauche");
								}
								else
								{
									//En haut à droite
									printf("\n\r\r----- MISSION - je vais en haut/gauche");	
								}	
							}
						}
						//voir dans detect_tag.h : remet à 0 cette variable pour ne pas diverger
						reset_x_y_last();					
					}
					else
					{
						printf("\n\r\r----- MISSION - HOVERING");	
					}
				/*}
				else
				{
					printf("\n\r\rMISSION - You have to take off !");					
				}*/
			}
			cpt_mission ++;	
		}
		else
		{
			printf("\n\r\r----- MISSION - aucune mission");
			cpt_mission = 0;
			reset_x_y_last();	
		}	
		
		printf("\n\r\r----- MISSION - cpt = %d\n",cpt_mission);

        	/* Wait until the next period is achieved */
        	wait_period (&info);
    	}

    	printf("\n\rEnding calcul_order_thread");

    	return(NULL);
}
