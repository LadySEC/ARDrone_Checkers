/**
 * \file 	supervisor.h
 * \brief 	Manages all interactions with the supervisor
 * \author 	Lady team
 * \version 1.0
 * \date 	21 november 2014
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
	STOP_TCP	= 	'R',
	BATTERY_TCP	=	'B',
	ANGLES_TCP	= 	'A',
	SPEEDS_TCP	=	'S',
	ALTITUDE_TCP=	'H'
}T_TCP_DATA;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
T_error supervisor_initiate(void);
void 	supervisor_close(void);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
void* 	supervisor_thread_interact(void* arg);

#endif //! _SUPERVISOR_H_
