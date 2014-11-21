/**
 * \file 	supervisor.c
 * \brief 	Manages all interactions with the supervisor
 * \author 	Lady team
 * \version 1.0
 * \date 	21 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "supervisor.h"

/**********************************************************************************/
/* Constants 															  		  */
/**********************************************************************************/
static const char* C_SUPERVISOR_IP				= "192.168.1.4";

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Socket */
int 	G_socket_SPVSR;
/* Buffer */
char	G_orders[RECV_BUFF_SIZE];

/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/
/**
 * \fn 		T_error supervisor_initiate(void)
 * \brief 	Initializes the TCP communication between the client and the supervisor
 *
 * \return 	ERROR: Unable to establish a communication, NO_ERROR: Success
 */
T_error supervisor_initiate(void)
{
	T_error error = NO_ERROR;

	/* Create a socket */
	// Supervisor socket with non blocking reception
	G_socket_SPVSR 	= socket_initiate(TCP, SPVSR_CLIENT_PORT, NON_BLOCKING);
	if(G_socket_SPVSR == -1)
	{
		error = error;
	}

	return(error);
}

/**
 * \fn 		void supervisor_close(void)
 * \brief 	Close the instantiated TCP socket
 *
 * \return 	ERROR: Unable to close the socket, NO_ERROR: Success
 */
void supervisor_close(void)
{
	socket_close(G_socket_SPVSR);
}

/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
/**
 * \fn 		void* supervisor_thread_interact(void* arg)
 * \brief 	Thread whih manages received orders
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 *
 * This thread reads received packets from the supervisor
 * And then process them to control the drone 
 */
void* supervisor_thread_interact(void* arg)
{
	T_bool 	disconnected = FALSE;


	printf("\n\rStarting supervisor management thread");

	while(disconnected == FALSE)
	{
		/* zero out the structure */
		memset((char *) &G_orders, 0, sizeof(G_orders));

		/* Read orders from the supervisor */
		if(socket_readPacket(G_socket_SPVSR, C_SUPERVISOR_IP, SPVSR_CLIENT_PORT, &G_orders, sizeof(G_orders), NON_BLOCKING) == RECEPTION_ERROR)
		{
			printf("\n\rClient disconnected");
			disconnected = TRUE;
		}
		else
		{
			/* Processing order */
			printf("\n\rReceived paquet: %s", G_orders);

			if (strcmp(G_orders, "exit") == 0) 
			{
				disconnected = TRUE;
			}

			if (strcmp(G_orders, "takeoff") == 0) 
			{
		        ATcommand_process(TAKEOFF);
			}

			if (strcmp(G_orders, "land") == 0) 
			{
				ATcommand_process(LANDING);
			}
		}

		usleep(INTERACT_TEMPO);
	}

	/* Close */
	supervisor_close();
	printf("\n\rEnding supervisor management thread");

	return(NULL);
}