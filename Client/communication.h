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
} protocol;

typedef enum  
{ 
	SERVER,
	CLIENT
} role;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
int socket_init(protocol p, int port);
void sendFrame(int socket_id, int port_dest, char* message);
void sendBytes(int socket_id, int port_dest, unsigned char* bytes, unsigned char lenght);
void readFrame(int socket_id, int port_dest, unsigned int* data, unsigned char lenght);


#endif //! _COMMUNICATION_H_