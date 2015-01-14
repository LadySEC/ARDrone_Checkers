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
#include "global.h"												/*!< Retrieve all common tools */
#include "at_command.h"											/*!< Send AT commands */
#include "calcul_order.h"										/*!< Interact with the mission */
 
/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/
/* Sockets */
#define SPVSR_CLIENT_PORT	4000u								/*!< Port number of the client socket */
/* Temporisations */
#define INTERACT_TEMPO		(unsigned int)1500000 			 	/*!< Thread temporisation in us */
#define	RECV_BUFF_SIZE		512u								/*!< Maximum size of a received TCP frame */

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
/**
* \struct 	T_TCP_data
* \brief 	Defines all TCP mnemonics related to our communication protocol between the client and the GUI
*/
typedef enum 
{  
	NAVDATA_TCP = 	'N', 										/*!< Share the current drone state */
	TARGET_TCP	=	'G',										/*!< Send reached square */
	TAKEOFF_TCP	=	'T',										/*!< Send a TAKEOFF/LANDING order */
	MISSION_TCP	= 	'M',										/*!< Retrieve the next square to reach */
	BATTERY_TCP	=	'B',										/*!< Share the battery level */
	ANGLES_TCP	= 	'A',										/*!< Share all Euler angles */
	SPEEDS_TCP	=	'S',										/*!< Share all drone speeds */
	ALTITUDE_TCP=	'H',										/*!< Share the drone altitude */
	DECON_TCP	= 	'D',										/*!< Disconnect and close the supervisor */
	EMERGENCY_TCP=	'E',										/*!< Send an EMERGENCY order */
	TIME_TCP 	= 	'Y'											/*!< Retrieve the current timestamp from the GUI to init the date and time (doesn't work properly) */
}T_TCP_data;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
/**
 * \fn 		T_error supervisor_initiate(void)
 * \brief 	Initializes the TCP communication between the client and the supervisor
 *
 * \return 	ERROR: Unable to establish a communication, NO_ERROR: Success - 
 */
T_error 		supervisor_initiate(void);

/**
 * \fn 		void supervisor_close(void)
 * \brief 	Close the instantiated TCP socket
 *
 * \return 	ERROR: Unable to close the socket, NO_ERROR: Success
 */
void 			supervisor_close(void);


/**********************************************************************************/
/* Getters                                                                        */
/**********************************************************************************/
/**
 * \fn 		unsigned char getSquare(void)
 * \brief 	Gives the target square
 *
 * \return 	The target square number
 */
unsigned char 	getSquare(void);

/**
 * \fn 		T_bool supervisor_commLost(void)
 * \brief 	Informs about the communication state
 *
 * \return 	TRUE: communication lost, FALSE: communication works properly
 */
T_bool 			supervisor_commLost(void);

/**********************************************************************************/
/* Setters                                                                        */
/**********************************************************************************/
/**
 * \fn 		void supervisor_setDisconnection(T_bool value)
 * \brief 	Disconnects the supervisor
 */
void 			supervisor_setDisconnection(T_bool value);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
/**
 * \fn 		void* supervisor_thread_interact(void* arg)
 * \brief 	Thread whih manages received orders
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 *
 *  Tasks:
 *      - Initialise the thread as periodic
 *      - Share data with the GUI
 *      - Read data from the GUI and perform actions
 */
void* 			supervisor_thread_interact(void* arg);

#endif //! _SUPERVISOR_H_
