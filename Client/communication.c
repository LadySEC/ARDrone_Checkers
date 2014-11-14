#include "communication.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/**********************************************************************************/
/* Threads & Procedures														      */
/**********************************************************************************/
void socket_die(char *s)
{
    perror(s);
    exit(1);
}

int socket_init(protocol p, int port)
{
	/* Declaration */
	struct 	sockaddr_in client;
	int 				socket_id;

	/* Generate a socket */
	switch(p)
	{
		case TCP:
			socket_id = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
			break;

		case UDP:
			socket_id = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
			break;
	}

    if(socket_id == -1)
   	{
   		socket_die("socket");
   	}
   	/* Socket created */
   	else
   	{
   		/* zero out the structure */
    	memset((char *) &client, 0, sizeof(client));

   		client.sin_addr.s_addr 	= htonl(INADDR_ANY); 
	    client.sin_family 		= AF_INET;
	    client.sin_port 		= htons(port);
	 
	 	/* bind socket to port */
	    if( bind(socket_id, (struct sockaddr*)&client, sizeof(client) ) == -1)
	    {
	        socket_die("bind");
	    }
   	}

    return(socket_id);
}

void sendFrame(int socket_id, int port_dest, char* message)
{
	/* Declaration */
	struct 	sockaddr_in server;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(port_dest);

	if (sendto(socket_id, message, strlen(message)+1, 0, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        socket_die("sendto()");
    }
    else
    {
    	printf("\n\r%s", message);
    }
}

void sendBytes(int socket_id, int port_dest, unsigned char* bytes, unsigned char lenght)
{
	/* Declaration */
	struct 	sockaddr_in server;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(port_dest);

	if (sendto(socket_id, bytes, lenght, 0, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        socket_die("sendto()");
    }
}

void readFrame(int socket_id, int port_dest, unsigned int* data, unsigned char lenght)
{
	/* Declaration */
	struct 	sockaddr_in server;
	unsigned int 		lenght_server = sizeof(server);

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(port_dest);

	if (recvfrom(socket_id, data, lenght, 0u, (struct sockaddr*) &server, &lenght_server) == -1)
	{
		socket_die("recvfrom()");
	}
}