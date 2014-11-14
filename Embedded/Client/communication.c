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

int socket_initiate(T_protocol I_protocol, int I_port, T_state I_state)
{
	/* Declaration */
	struct 	sockaddr_in client;
	int 				socket_id;
	int 				flags;

	/* Generate a socket */
	switch(I_protocol)
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
	    client.sin_port 		= htons(I_port);
	 
	 	/* bind socket to port */
	    if( bind(socket_id, (struct sockaddr*)&client, sizeof(client) ) == -1)
	    {
	        socket_die("bind");
	    }

	    /* Set the socket as non-blocking */
	    if(I_state ==  NON_BLOCKING)
	   	{
	   		flags 		= fcntl(socket_id, F_GETFL);
			fcntl(socket_id, F_SETFL, flags | O_NONBLOCK);
	   	}
   	}

    return(socket_id);
}

void socket_sendString(int I_socket_id, int I_port_dest, char* O_message)
{
	/* Declaration */
	struct 	sockaddr_in server;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

	if (sendto(I_socket_id, O_message, strlen(O_message)+1, 0, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        socket_die("sendto()");
    }
    else
    {
    	printf("\n\rString sent: %s", O_message);
    }
}

void socket_sendBytes(int I_socket_id, int I_port_dest, unsigned char* O_bytes, unsigned char I_lenght)
{
	/* Declaration */
	struct 	sockaddr_in server;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

	if (sendto(I_socket_id, O_bytes, I_lenght, 0u, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        socket_die("sendto()");
    }
}

unsigned char socket_readPaquet(int I_socket_id, int I_port_dest, void* O_data, int I_lenght, T_state I_state)
{
	/* Declaration */
	struct 	sockaddr_in server;
	unsigned int 		lenght_server 	= sizeof(server);
	unsigned char		error 			= 0u;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

    switch(I_state)
    {
    	case BLOCKING:
    		if (recvfrom(I_socket_id, O_data, I_lenght, 0u, (struct sockaddr*) &server, &lenght_server) == -1)
			{
				error = 1u;
			}
    		break;

    	case NON_BLOCKING:
    		if (recvfrom(I_socket_id, O_data, I_lenght, MSG_DONTWAIT, (struct sockaddr*) &server, &lenght_server) == -1)
			{
				error = 1u;
			}
    		break;
    }

	return(error);
}