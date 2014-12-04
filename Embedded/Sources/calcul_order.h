
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
/**********************************************************************************/
/* Constants						      			  */
/**********************************************************************************/
/* Temporisations */
#define _CALCUL_PERIOD          (unsigned int)7000000
#define _PIXEL_X_MAX 		1280
#define _PIXEL_Y_MIN		720
#define _PIXEL_X_MIDDLE		640
#define _PIXEL_Y_MIDDLE		360
/**********************************************************************************/
/* Types					      				  */
/**********************************************************************************/

/**********************************************************************************/
/* Prototypes				        	      			  */
/**********************************************************************************/

/**********************************************************************************/
/* Threads						     		  	  */
/**********************************************************************************/
void* 	calcul_order_thread(void* arg);

#endif //! _SUPERVISOR_H_