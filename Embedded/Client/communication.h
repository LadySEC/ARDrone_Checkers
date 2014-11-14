#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include <sys/socket.h>		// UDP/TCP
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h> 		// memset

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/


/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
typedef enum 
{
	TCP,
	UDP
} T_protocol;

typedef enum  
{ 
	SERVER,
	CLIENT
} T_role;

typedef enum  
{  
	BLOCKING,
	NON_BLOCKING
} T_state;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
int 	socket_initiate(T_protocol I_protocol, int I_port, T_state I_state);
void 	socket_sendString(int I_socket_id, int I_port_dest, char* O_message);
void 	socket_sendBytes(int I_socket_id, int I_port_dest, unsigned char* O_bytes, unsigned char I_lenght);

void readFrame(int socket_id, int port_dest, unsigned int* data, unsigned char lenght);


#endif //! _COMMUNICATION_H_