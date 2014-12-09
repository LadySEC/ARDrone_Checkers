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
#include "detect_tag.h"
/**********************************************************************************/
/* Constants 							  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/
/* informed the mission's status */
/*	0 : The drone are going toward the case */
/*	1 : The drone are returning toward the base */
int round_mission = 0;
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
	int 		cpt_mission = 0;
	T_Position 	pos_tag;

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

				// - Je reçois l'ordre du superviseur
			}
			else
			{
				/*If the drone is in flight phase
				if(ATcommand_FlyingState() == TRUE)
				{*/
					pos_tag = W_getPosition(5, 2);
					printf("\n\r\r----- MISSION - x = %d, y = %d",pos_tag.abs,pos_tag.ord);
					//Donne un mouvement selon la position
					posTag_ATcommand(pos_tag.abs,pos_tag.ord);					
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
		}	
		
		printf("\n\r\r----- MISSION - cpt = %d\n",cpt_mission);

        	/* Wait until the next period is achieved */
        	wait_period (&info);
    	}

    	printf("\n\rEnding calcul_order_thread");

    	return(NULL);
}


void posTag_ATcommand(int x,int y)
{
	if(x >= -POS_TOLERANCE && x <= POS_TOLERANCE)		//-120 <= X <= 120, CENTRE
	{
		if(y >= -POS_TOLERANCE && y <= POS_TOLERANCE)	  //-120 <= Y <= 120, CENTRE
		{
			if(round_mission == 0)
			{			
				printf("\n\r\r----- MISSION - je suis arrivé à la Case");
				round_mission = 1;

                        ATcommand_moveDelay(VERTICAL_UP, 800000);
                        ATcommand_moveDelay(HOVERING_BUFF, 800000);
                        ATcommand_moveDelay(VERTICAL_DOWN, 800000);
			}
			else
			{
				printf("\n\r\r----- MISSION - [END] je suis arrivé à la Base");
				round_mission = 0;
			}	
		}
		if(y < -POS_TOLERANCE)			  	  //Y < -120 
		{
			printf("\n\r\r----- MISSION - je vais en haut");
                        ATcommand_moveDelay(PITCH_DOWN, 100000);
		}
		if(y > POS_TOLERANCE)			  	  //Y > 120
		{
			printf("\n\r\r----- MISSION - je vais en bas");	
                        ATcommand_moveDelay(PITCH_UP, 100000);
		}
	}
	if(y >= -POS_TOLERANCE && y <= POS_TOLERANCE)		//-120 <= Y <= 120, CENTRE
	{
		if(x < -POS_TOLERANCE)				  //X < -120 
		{
			printf("\n\r\r----- MISSION - je vais en gauche");	
                        ATcommand_moveDelay(ROLL_LEFT, 100000);
		}
		if(x > POS_TOLERANCE)				  //X > 120
		{
			printf("\n\r\r----- MISSION - je vais en droite");	
                        ATcommand_moveDelay(ROLL_RIGHT, 100000);
		}
	}
	if(x < -POS_TOLERANCE)					//X < -120 
	{
		if(y < -POS_TOLERANCE)				  //Y < -120 
		{
			printf("\n\r\r----- MISSION - je vais en gauche/haut");
                        ATcommand_moveDelay(ROLL_LEFT, 100000);
                        ATcommand_moveDelay(HOVERING_BUFF, 100000);
                        ATcommand_moveDelay(PITCH_DOWN, 100000);

		}
		if(y > POS_TOLERANCE)				  //Y > 120
		{
			printf("\n\r\r----- MISSION - je vais en gauche/bas");
                        ATcommand_moveDelay(ROLL_LEFT, 100000);
                        ATcommand_moveDelay(HOVERING_BUFF, 100000);
                        ATcommand_moveDelay(PITCH_UP, 100000);
		}	
	}
	if(x > POS_TOLERANCE)					//X > 120
	{
		if(y < -POS_TOLERANCE)				  //Y < -120 
		{
			printf("\n\r\r----- MISSION - je vais en droite/haut");
                        ATcommand_moveDelay(ROLL_RIGHT, 100000);
                        ATcommand_moveDelay(HOVERING_BUFF, 100000);
                        ATcommand_moveDelay(PITCH_DOWN, 100000);
		}
		if(y > POS_TOLERANCE)				  //Y > 120
		{
			printf("\n\r\r----- MISSION - je vais en droite/bas");
                        ATcommand_moveDelay(ROLL_RIGHT, 100000);
                        ATcommand_moveDelay(HOVERING_BUFF, 100000);
                        ATcommand_moveDelay(PITCH_UP, 100000);
		}	
	}
}
