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
#include "../../Common/log.h"

/**********************************************************************************/
/* Constants 							  		  */
/**********************************************************************************/
/*** it represents the size between the camera position on the drone and it takeoff base */
int const offset_y 	= 0;
/*** it represents the time when the ATcomman are sending */
int const I_offset_time = 2 * (_CALCUL_PERIOD / 3);

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
	int			num_square	= 0;
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
				printf("----- MISSION - * Begin the mission *\n\r");
				printf("-----         - Temps AT_commande = %d\n\r",I_offset_time);
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

					printf("----- MISSION - x = %d, y = %d\n\r",pos_tag.abs,pos_tag.ord);

					/* Sent AT_command according to the (x;y) */
					posTag_ATcommand(pos_tag.abs,pos_tag.ord);					
				}
				else
				{
					printf("MISSION - You have to take off !\n\r");					
				}
			}
			cpt_mission ++;	
		}
		else
		{
			printf("----- MISSION - aucune mission\n\r");
			statemission = 0;
			cpt_mission = 0;	
		}	
		
		printf("----- MISSION - cpt = %d\n\r",cpt_mission);

        	/* Wait until the next period is achieved */
        	wait_period (&info);
    	}

    	printf("Ending calcul_order_thread\n\r");

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

				printf("----- MISSION - [END1] je suis arrive a la Case\n\r");

				/* For a perfect take off :) */
				ATcommand_moveDelay(HOVERING_BUFF, 	_CALCUL_PERIOD);
				ATcommand_process(LANDING);
				printf("              - LANDING\n\r");
				LOG_WriteLevel(LOG_INFO, "calcul_order : Square found -> landing\n");
					
				// The first round of this mission is finished 
				//round_mission = 1;
				
				/* Reset the mode mission ('M') for the keyboard.c */
				stop_mission();

				/* For the supervisor */
				statemission = 0;

			}
			else
			{
				ATcommand_process(LANDING);
				printf("              - LANDING\n\r");
				LOG_WriteLevel(LOG_INFO, "calcul_order : Square found -> landing\n");

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
			printf("----- MISSION - je vais en haut\n\r");
						ATcommand_moveDelay(PITCH_DOWN, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))			  	  //Y > 120-offset_y
		{
			printf("----- MISSION - je vais en bas\n\r");	
						ATcommand_moveDelay(PITCH_UP, 		I_offset_time);
		}
	}
	if(y >= (-POS_TOLERANCE-offset_y) && y <= (POS_TOLERANCE-offset_y))		//-120-offset_y <= Y <= 120-offset_y, CENTRE
	{
		if(x < -POS_TOLERANCE)				  //X < -120 
		{
			printf("----- MISSION - je vais en gauche\n\r");	
						ATcommand_moveDelay(ROLL_LEFT, 		I_offset_time);
		}
		if(x > POS_TOLERANCE)				  //X > 120
		{
			printf("----- MISSION - je vais en droite\n\r");	
						ATcommand_moveDelay(ROLL_RIGHT, 	I_offset_time);
		}
	}
	if(x < -POS_TOLERANCE)					//X < -120 
	{
		if(y < (-POS_TOLERANCE-offset_y))				  //Y < -120-offset_y
		{
			printf("----- MISSION - je vais en gauche/haut\n\r");
						ATcommand_moveDelay(PITCH_DOWN_ROLL_LEFT, 	I_offset_time);

		}
		if(y > (POS_TOLERANCE-offset_y))				  //Y > 120-offset_y
		{
			printf("----- MISSION - je vais en gauche/bas\n\r");
						ATcommand_moveDelay(PITCH_UP_ROLL_LEFT,		I_offset_time);
		}
	}
	if(x > POS_TOLERANCE)					//X > 120
	{
		if(y < (-POS_TOLERANCE-offset_y))				  //Y < -120-offset_y 
		{
			printf("----- MISSION - je vais en droite/haut\n\r");
						ATcommand_moveDelay(PITCH_DOWN_ROLL_RIGHT, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))				  //Y > 120-offset_y
		{
			printf("----- MISSION - je vais en droite/bas\n\r");
						ATcommand_moveDelay(PITCH_UP_ROLL_RIGHT, 	I_offset_time);
		}
	}
}

int get_stateMission(void)
{
	return statemission;
}
