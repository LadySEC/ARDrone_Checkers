/**
 * \file 	communication.h
 * \brief 	Manages UDP/TCP communications
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
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

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
int 				socket_initiate(T_protocol I_protocol, int I_port, T_state I_state);
T_error 			socket_sendString(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, char* I_message);
T_error 			socket_sendBytes(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, unsigned char* I_bytes, unsigned char I_lenght);
T_reception_state 	socket_readPacket(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, void* O_data, int I_lenght, T_state I_state);
void 				socket_close(int I_socket_id);

#endif //! _COMMUNICATION_H_