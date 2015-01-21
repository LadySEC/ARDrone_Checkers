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
int const offset_y 	= 0;
/*** it represents the time when the ATcomman are sending */
int const I_offset_time = (_CALCUL_PERIOD)/3;

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/
/*** Informed the mission's round 						*/
/*	0 : The drone are going toward the case 				*/
/*	1 : The drone are returning toward the base 				*/
int round_mission = 0;

int 		cpt_mission 	= 0;

/*** Informed the mission's status 						*/
/*	0 : The drone did not finshed the mission asked by the supervisor 	*/
/*	1 : The drone tookoff and it is going to stabilised over the base	*/
/*	2 : The drone fished the mission asked by he supervisor 		*/
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
	int				num_square	= 0;
	T_Position 		pos_tag;
	float 			angle;
	T_navdata_demo*	pNavData;

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
				statemission = 1;
				round_mission = 0;
				LOG_WriteLevel(LOG_INFO, "calcul_order : BEGIN MISSION");

				LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - Begin the mission");
				LOG_WriteLevel(LOG_INFO, "calcul_order : Temps AT_commande = %d",I_offset_time);
			}
			else
			{
				if (1)//if(ATcommand_FlyingState() == TRUE)
				{
					if (round_mission == 0) 
					{
						switch (statemission)
						{
							case 0 :
								process_end_mission(0);
								LOG_WriteLevel(LOG_INFO, "calcul_order : thread: case 0 ERROR");

							break;
	
							case 1 :
								/* stabilisation over the BASE */
								LOG_WriteLevel(LOG_INFO, "calcul_order : thread: statemission = 1, STABILISATION");
								
								LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - stabilisation");
								
								pNavData = ATcommand_navdata();
								
								if (abs(pNavData->phi/1000.0) < C_MAX_PHI && abs(pNavData->theta/1000.0) < C_MAX_THETA) {
									pos_tag = W_getPosition(5, 5);
								} else {
									pos_tag.abs = 0;
									pos_tag.ord = 0;
									pos_tag.bIsFound = 0;
								}
								
								setDynamicParameter(PITCH_ANGLE, C_MIN_PITCH + (C_MAX_PITCH - C_MIN_PITCH) * abs(pos_tag.ord)/360.0);
								setDynamicParameter(ROLL_ANGLE, C_MIN_ROLL + (C_MAX_ROLL - C_MIN_ROLL) * abs(pos_tag.abs)/360.0);
								
								if(pos_tag.bIsFound == 1)
								{
									posTag_ATcommand(pos_tag.abs,pos_tag.ord);	
								}
							break;

							case 2 :
								
								LOG_WriteLevel(LOG_INFO, "calcul_order : thread: statemission = 2, VERS LA CASE round = 0");

								if (abs(pNavData->phi/1000.0) < C_MAX_PHI && abs(pNavData->theta/1000.0) < C_MAX_THETA) {
									pos_tag = W_getPosition(5,num_square);
									/* Base -> Case */
									setDynamicParameter(PITCH_ANGLE, C_MIN_PITCH + (C_MAX_PITCH - C_MIN_PITCH) * abs(pos_tag.ord)/360.0);
									setDynamicParameter(ROLL_ANGLE, C_MIN_ROLL + (C_MAX_ROLL - C_MIN_ROLL) * abs(pos_tag.abs)/360.0);
								
									posTag_ATcommand(pos_tag.abs,pos_tag.ord);	
								}
								
							break;
	
							default :
								LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - error state mission");

								process_end_mission(0);
							break;
						}
					}
					else 		
					{
						/* Case -> Base */
						if (abs(pNavData->phi/1000.0) < C_MAX_PHI && abs(pNavData->theta/1000.0) < C_MAX_THETA) {
							pos_tag = W_getPosition(num_square, 5);
						} else {
							pos_tag.abs = 0;
							pos_tag.ord = 0;
							pos_tag.bIsFound = 0;
						}

						posTag_ATcommand(pos_tag.abs,pos_tag.ord);	
		
						LOG_WriteLevel(LOG_INFO, "calcul_order : thread: VERS LA BASE (round = 1)");
	
					}

					LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - x = %d, y = %d",pos_tag.abs,pos_tag.ord);
					
				}
				else
				{
					LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - You have to take off !");					
				}
			}
			cpt_mission ++;	
		}
		else
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - aucune mission");
			statemission = 0;
			cpt_mission = 0;	
		}	
		
		LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - cpt = %d",cpt_mission);

        	/* Wait until the next period is achieved */
        	wait_period (&info);
    	}

    	LOG_WriteLevel(LOG_INFO, "calcul_order : Ending calcul_order_thread");

    	return(NULL);
}

/* This function give the command according to the drone's position, updated 'roundmission' and 'statemission' */
void posTag_ATcommand(int x,int y)
{
	if(x >= -POS_TOLERANCE && x <= POS_TOLERANCE)	
	{
		if(y >= (-POS_TOLERANCE-offset_y) && y <= (POS_TOLERANCE-offset_y))	  
		{
			if(round_mission == 0) 	//Base -> Case
			{	
				switch (statemission)
				{
					case 0 :
						LOG_WriteLevel(LOG_INFO, "calcul_order : posTag_ATcommand : error statemission 0 END MISSION");
						process_end_mission(0);
					break;

					case 1 :
						// On est stable, on part en mission
						statemission  = 2;
						round_mission = 0; 
					break;

					case 2 :
						//process_end_mission(0);
						//statemission  = 2;
						round_mission = 1;
					break;

					default :
						LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - error state mission");
						process_end_mission(0);
					
					break;
				}
			}
			else 			//Case -> Base
			{
				LOG_WriteLevel(LOG_INFO, "calcul_order : posTag_ATcommand : round 1, END MISSION");			
				process_end_mission(0); 
			}
		}
		if(y < (-POS_TOLERANCE-offset_y))			  	  
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en haut");
			ATcommand_moveDelay(PITCH_DOWN, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))			  	 
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en bas");	
			ATcommand_moveDelay(PITCH_UP, 		I_offset_time);
		}
	}
	if(y >= (-POS_TOLERANCE-offset_y) && y <= (POS_TOLERANCE-offset_y))		
	{
		if(x < -POS_TOLERANCE)				  
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en gauche");	
			ATcommand_moveDelay(ROLL_LEFT, 		I_offset_time);
		}
		if(x > POS_TOLERANCE)				 
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en droite");	
			ATcommand_moveDelay(ROLL_RIGHT, 	I_offset_time);
		}
	}
	if(x < -POS_TOLERANCE)					
	{
		if(y < (-POS_TOLERANCE-offset_y))				  
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en gauche/haut");
			ATcommand_moveDelay(PITCH_DOWN_ROLL_LEFT, 	I_offset_time);

		}
		if(y > (POS_TOLERANCE-offset_y))				  
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en gauche/bas");
			ATcommand_moveDelay(PITCH_UP_ROLL_LEFT,		I_offset_time);
		}
	}
	if(x > POS_TOLERANCE)					
	{
		if(y < (-POS_TOLERANCE-offset_y))				   
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en droite/haut");
			ATcommand_moveDelay(PITCH_DOWN_ROLL_RIGHT, 	I_offset_time);
		}
		if(y > (POS_TOLERANCE-offset_y))				  
		{
			LOG_WriteLevel(LOG_INFO, "calcul_order : MISSION - je vais en droite/bas");
			ATcommand_moveDelay(PITCH_UP_ROLL_RIGHT, 	I_offset_time);
		}
	}
}

int get_stateMission(void)
{
	return statemission;
}

void process_end_mission(int value_statemission)
{
	/*ATcommand_process(LANDING);
	printf("              - LANDING\n\r");
	LOG_WriteLevel(LOG_INFO, "calcul_order : Square found -> landing");
	while(ATcommand_FlyingState() != FALSE);*/
	
	LOG_WriteLevel(LOG_INFO, "calcul_order : G_triggered_mission = FALSE");

	/* Reset the mode mission ('M') for the keyboard.c (G_triggered_mission = FALSE )*/
	stop_mission();
	
	/* The second round of this mission is finished */
	round_mission = 0;

	/* For the supervisor */
	statemission = value_statemission;
	
	cpt_mission = 0;
}
