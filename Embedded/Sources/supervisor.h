/**
 * \file 	supervisor.h
 * \brief 	Manages all interactions with the supervisor
 * \author 	Lady team
 * \version 1.0
 * \date 	4 December 2014
 *
 */
#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include "communication.h"
#include "at_command.h"
#include "keyboard.h"
#include "calcul_order.h"
 
/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/
/* Sockets */
#define SPVSR_CLIENT_PORT	4000u
/* Temporisations */
#define INTERACT_TEMPO		(unsigned int)1000000
#define	RECV_BUFF_SIZE		512u

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
typedef enum 
{  
	NAVDATA_TCP = 	'N',
	TARGET_TCP	=	'G',
	TAKEOFF_TCP	=	'T',
	MISSION_TCP	= 	'M',
	BATTERY_TCP	=	'B',
	ANGLES_TCP	= 	'A',
	SPEEDS_TCP	=	'S',
	ALTITUDE_TCP=	'H',
	DECON_TCP	= 	'D',
	EMERGENCY_TCP=	'E',
	TIME_TCP 	= 	'Y'
}T_TCP_DATA;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
T_error supervisor_initiate(void);
void 	supervisor_close(void);
unsigned char getSquare(void);
T_bool supervisor_commLost(void);
void supervisor_setDisconnection(T_bool value);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
void* 	supervisor_thread_interact(void* arg);

#endif //! _SUPERVISOR_H_
