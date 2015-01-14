
/**
 * \file 	calcul_order.c
 * \brief 	Make the calculation for the next drone orders
 * \author 	Lady team
 * \version 1.0
 * \date 	23 november 2014
 *
 */

#ifndef _CALCUL_ORDER_H_
#define _CALCUL_ORDER_H_

/**********************************************************************************/
/* Libraries	                        			      		  */
/**********************************************************************************/
#include "global.h"
#include "communication.h"
#include "at_command.h"
#include "supervisor.h"
/**********************************************************************************/
/* Constants						      			  */
#define C_MAX_THETA	4.0
#define C_MAX_PHI	4.0
/**********************************************************************************/
/* Temporisations */
#define _CALCUL_PERIOD          (unsigned int)500000
/**********************************************************************************/
/* Types					      				  */
/**********************************************************************************/

/**********************************************************************************/
/* Prototypes				        	      			  */
/**********************************************************************************/
void 	posTag_ATcommand	(int x,int y);
void 	process_end_mission	(int value_statemission);

/**********************************************************************************/
/* Threads						     		  	  */
/**********************************************************************************/
void* 	calcul_order_thread	(void* arg);
int	get_stateMission	(void);

#endif //! _SUPERVISOR_H_
