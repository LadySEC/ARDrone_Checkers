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
/*** it represents the size between the camera position on the drone and it takeoff base */
int const offset_y 	= 35;
/*** it represents the time when the ATcomman are sending */
int const I_offset_time = (2 * _CALCUL_PERIOD / 3);

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/
/*** Informed the mission's round 						*/
/*	0 : The drone are going toward the case 				*/
/*	1 : The drone are returning toward the base 				*/
int round_mission = 0;

/*** Informed the mission's status 						*/
/*	0 : The drone did not finshed the mission asked by the supervisor 	*/
/*	1 : The drone fished the mission asked by he supervisor 		*/
int statemission = 0;

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
	int 		cpt_mission 	= 0;
	int		num_square	= 0;
	T_Position 	pos_tag;

    	/* Make this thread periodic */
    	struct periodic_info info;
    	make_periodic (_CALCUL_PERIOD, &info);

    	while(1)
    	{
		/* Triggered the mission mode*/
		if(getSquare() != 0)
		{
			/* check the square number sent by the supervisor */
			num_square = getSquare();

			if(cpt_mission == 0)
			{
				printf("\n\r\r----- MISSION - * Begin the mission *");
				printf("\n\r\r-----         - Temps AT_commande = %d",I_offset_time);
				printf("\n\r\r-----         - Angle roll        = %d",ROLL_CONSTANT);
				printf("\n\r\r-----         - Angle pitch       = %d",PITCH_CONSTANT);
			}
			else
			{
				if(ATcommand_FlyingState() == TRUE)
				{
					/* For the supervisor */
					statemission = 1;

					if (round_mission == 0)
					{
						/* direction : case */
						pos_tag = W_getPosition(5, num_square);
					}
					else
					{
						/* direction : base */
						pos_tag = W_getPosition(num_square, 5);
					}

					printf("\n\r\r----- MISSION - x = %d, y = %d",pos_tag.abs,pos_tag.ord);

					/* Sent AT_command according to the (x;y) */
					posTag_ATcommand(pos_tag.abs,pos_tag.ord);					
				}
				else
				{
					printf("\n\r\rMISSION - You have to take off !");					
				}
			}
			cpt_mission ++;	
		}
		else
		{
			printf("\n\r\r----- MISSION - aucune mission");
			statemission = 0;
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
		if(y >= (-POS_TOLERANCE-offset_y) && y <= (POS_TOLERANCE-offset_y))	  //-120-offset_y <= Y <= 120-offset_y, CENTRE
		{
			if(round_mission == 0)
			{			
	
				// The first round of this mission is finished 
				//round_mission = 1;

				/* Reset the mode mission ('M') for the keyboard.c */
				stop_mission();

				/* For the supervisor */
				statemission = 0;

				printf("\n\r\r----- MISSION - [END1] je suis arrive a la Case");

				/* For a perfect take off :) */
				ATcommand_moveDelay(HOVERING_BUFF, 	_CALCUL_PERIOD);
		            	ATcommand_process(LANDING);
			        printf("\n\r\r              - LANDING");

			}
			else
			{
				printf("\n\r\r----- MISSION - [END2] je suis arrive a la Base");
		            	ATcommand_moveDelay(HOVERING_BUFF, 	_CALCUL_PERIOD);
		            	ATcommand_process(LANDING);
			        printf("\n\r\r              - LANDING");

				/* Reset the mode mission ('M') for the keyboard.c */
				stop_mission();

				/* The second round of this mission is finished */
				round_mission = 0;

				/* For the supervisor */
				statemission = 0;
			}	
		}
		if(y < (-POS_TOLERANCE-offset_y))			  	  //Y < -120-offset_y
		{
			printf("\n\r\r----- MISSION - je vais en haut");
                        ATcommand_moveDelay(PITCH_DOWN, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))			  	  //Y > 120-offset_y
		{
			printf("\n\r\r----- MISSION - je vais en bas");	
                        ATcommand_moveDelay(PITCH_UP, 		I_offset_time);
		}
	}
	if(y >= (-POS_TOLERANCE-offset_y) && y <= (POS_TOLERANCE-offset_y))		//-120-offset_y <= Y <= 120-offset_y, CENTRE
	{
		if(x < -POS_TOLERANCE)				  //X < -120 
		{
			printf("\n\r\r----- MISSION - je vais en gauche");	
                        ATcommand_moveDelay(ROLL_LEFT, 		I_offset_time);
		}
		if(x > POS_TOLERANCE)				  //X > 120
		{
			printf("\n\r\r----- MISSION - je vais en droite");	
                        ATcommand_moveDelay(ROLL_RIGHT, 	I_offset_time);
		}
	}
	if(x < -POS_TOLERANCE)					//X < -120 
	{
		if(y < (-POS_TOLERANCE-offset_y))				  //Y < -120-offset_y
		{
			printf("\n\r\r----- MISSION - je vais en gauche/haut");
                        ATcommand_moveDelay(ROLL_LEFT, 		I_offset_time);
                        ATcommand_moveDelay(HOVERING_BUFF, 	I_offset_time);
                        ATcommand_moveDelay(PITCH_DOWN, 	I_offset_time);

		}
		if(y > (POS_TOLERANCE-offset_y))				  //Y > 120-offset_y
		{
			printf("\n\r\r----- MISSION - je vais en gauche/bas");
                        ATcommand_moveDelay(ROLL_LEFT, 		I_offset_time);
                        ATcommand_moveDelay(HOVERING_BUFF, 	I_offset_time);
                        ATcommand_moveDelay(PITCH_UP, 		I_offset_time);
		}	
	}
	if(x > POS_TOLERANCE)					//X > 120
	{
		if(y < (-POS_TOLERANCE-offset_y))				  //Y < -120-offset_y 
		{
			printf("\n\r\r----- MISSION - je vais en droite/haut");
                        ATcommand_moveDelay(ROLL_RIGHT, 	I_offset_time);
                        ATcommand_moveDelay(HOVERING_BUFF, 	I_offset_time);
                        ATcommand_moveDelay(PITCH_DOWN, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))				  //Y > 120-offset_y
		{
			printf("\n\r\r----- MISSION - je vais en droite/bas");
                        ATcommand_moveDelay(ROLL_RIGHT, 	I_offset_time);
                        ATcommand_moveDelay(HOVERING_BUFF, 	I_offset_time);
                        ATcommand_moveDelay(PITCH_UP, 		I_offset_time);
		}	
	}
}

int get_stateMission(void)
{
	return statemission;
}
