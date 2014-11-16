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
int 			socket_initiate(T_protocol I_protocol, const char* I_ip_addr, int I_port, T_state I_state);
T_error 		socket_sendString(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, char* O_message);
T_error 		socket_sendBytes(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, unsigned char* O_bytes, unsigned char I_lenght);
T_error 		socket_readPaquet(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, void* O_data, int I_lenght, T_state I_state);
void 			socket_close(int I_socket_id);

#endif //! _COMMUNICATION_H_