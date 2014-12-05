/**
 * \file 	communication.h
 * \brief 	Manages UDP/TCP communications
 * \author 	Lady team
 * \version 1.0
 * \date 	4 December 2014
 *
 */
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include <sys/socket.h>		// UDP/TCP
#include <netinet/in.h>
#include <arpa/inet.h> 		//inet_addr
#include <fcntl.h>
#include <string.h> 		// memset

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/


/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
/**
 * \struct 	T_protocol
 * \brief 	Defines a communication protocol
 */
typedef enum 
{
	TCP,			/*!< TCP protocol */
	UDP				/*!< UDP protocol */
} T_protocol;

/**
 * \struct 	T_role
 * \brief 	Defines a socket as server or client
 */
typedef enum  
{ 
	SERVER,			/*!< Server socket */
	CLIENT			/*!< Client socket */
} T_role;

/**
 * \struct 	T_state
 * \brief 	Defines the state of the socket
 */
typedef enum  
{  
	BLOCKING,		/*!< Blocking state */
	NON_BLOCKING	/*!< Non-blocking state */
} T_state;

/**
 * \struct 	T_reception_state
 * \brief 	Defines the state of a reading process
 */
typedef enum 
{  
	NO_PACKET_RECEIVED = 0u,	/*!< No packet received for a non-blocking function */
	RECEPTION_ERROR,			/*!< Communcation lost for TCP */
	PACKET_RECEIVED 			/*!< One packet is ready to be read */
} T_reception_state;

/**
 * \struct 	T_socket
 * \brief 	Defines a socket structure
 */
typedef struct 
{
	int 					id;				/*!< Identifier */
	struct 	sockaddr_in		parameters;		/*!< Parameters */
}T_socket;

/**
 * \struct 	T_comm
 * \brief 	Defines a communication structure
 */
typedef struct 
{
	T_protocol 	protocol;
	T_socket* 	client;		/*!< client socket */
	T_socket* 	server;		/*!< server socket */
}T_comm;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
T_comm* 			communication_initiate(T_protocol I_protocol, char* I_IP_addr_client, char* I_IP_addr_server, int I_port_client, int I_port_server, T_state I_state);
T_error 			socket_sendString(T_protocol I_protocol, int I_emitter_id, struct sockaddr_in* I_parameters, char* I_message);
T_error 			socket_sendBytes(T_protocol I_protocol, int I_emitter_id, struct sockaddr_in* I_parameters, unsigned char* I_bytes, unsigned char I_lenght);
T_reception_state 	socket_readPacket(T_protocol I_protocol, int I_receiver_id, struct sockaddr_in* I_parameters, void* O_data, int I_lenght, T_state I_state);
void 				socket_close(T_socket* I_socket);

#endif //! _COMMUNICATION_H_