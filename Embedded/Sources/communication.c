/**
 * \file 	communication.c
 * \brief 	Manages UDP/TCP communications
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "communication.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/
/**
 * \fn 		int socket_initiate(T_protocol I_protocol, int I_port, T_state I_state)
 * \brief 	Create and initialize a UDP/TCP socket
 *
 * \param 	I_protocol 	Protocol configuration 
 * \param 	I_ip_addr  	IP address
 * \param 	I_port  	Choosen port
 * \param 	I_state  	Socket status configuration
 * \return 				Socket ID
 */
int socket_initiate(T_protocol I_protocol, int I_port, T_state I_state)
{
	/* Declaration */
	struct 	sockaddr_in client;
	struct 	sockaddr_in server;
	int 				socket_client_id = -1;
	int 				socket_server_id = -1;
	int 				socket_lenght;
	int 				flags;


	/* Generate a socket */
	switch(I_protocol)
	{
		case TCP:
			socket_server_id = socket(AF_INET , SOCK_STREAM , IPPROTO_IP);
			if(socket_server_id == -1)
		   	{
		   		perror("\n\rsocket");
		   	}
		   	/* Socket created */
		   	else
		   	{
		   		/* zero out the structure */
		    	memset((char *) &server, 0, sizeof(server));

		   		server.sin_addr.s_addr 	= htonl(INADDR_ANY);//inet_addr(I_ip_addr); 
			    server.sin_family 		= AF_INET;
			    server.sin_port 		= htons(I_port);
			 
			 	/* bind socket to port */
			 	printf("\n\rBinding socket %d ...", socket_server_id);
			    if( bind(socket_server_id, (struct sockaddr*)&server, sizeof(server) ) == -1)
			    {
			        perror("\n\rbind");
			    }
			    else
			    {
		    		/* Waiting for a communication */
		    		printf("\n\rWaiting for the supervisor");
	    			if(listen(socket_server_id, 3u) == -1)		//3 ?
	    			{
	    				perror("\n\rlisten");
	    			}
	    			else
	    			{
	    				/* Accepting the communication */
					    socket_lenght = sizeof(client);
					    socket_client_id = accept(socket_server_id, (struct sockaddr *)&client, (socklen_t*)&socket_lenght);
					    if(socket_client_id == -1)
					    {
					        perror("\n\raccept");
					    }
					    else
					    {
					    	printf("\n\rClient connected to %s:%d", inet_ntoa(client.sin_addr), client.sin_port);
					    }
	    			}
			    }
		   	}
			break;

		case UDP:
			socket_client_id = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
			if(socket_client_id == -1)
		   	{
		   		perror("socket");
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
			 	printf("\n\rBinding socket %d ...", socket_client_id);
			    if( bind(socket_client_id, (struct sockaddr*)&client, sizeof(client) ) == -1)
			    {
			        perror("bind");
			    }
		   	}
			break;
	}

    /* Set the socket as non-blocking */
    if((I_state ==  NON_BLOCKING) && (socket_client_id != -1))
   	{
   		flags 		= fcntl(socket_client_id, F_GETFL);
		fcntl(socket_client_id, F_SETFL, flags | O_NONBLOCK);
   	}

    return(socket_client_id);
}

/**
 * \fn 		T_error socket_sendString(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, char* O_message)
 * \brief 	Send an 8-bit ASCII string through a packet
 *
 * \param 	I_socket_id 	ID of the emitter socket  
 * \param 	I_ip_addr_dest  Destination IP adress
 * \param 	I_port_dest  	Destination port 
 * \param 	I_message  		String to be sent
 * \return 					ERROR: Transmission error, NO_ERROR: Success
 */
T_error socket_sendString(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, char* I_message)
{
	/* Declaration */
	struct 	sockaddr_in server;
	T_error 			error 	= NO_ERROR;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= inet_addr(I_ip_addr_dest); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

	if (sendto(I_socket_id, I_message, strlen(I_message)+1, 0, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        perror("sendto()");
        error = ERROR;
    }
    else
    {
	//--------------------------------------------------------------------------------------------------------
    	//printf("\n\rString sent: %s", I_message);
    }

    return(error);
}

/**
 * \fn 		T_error socket_sendBytes(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, unsigned char* O_bytes, unsigned char I_lenght)
 * \brief 	Send an 8-bit array of provided lenght through a packet
 *
 * \param 	I_socket_id 	ID of the emitter socket  
 * \param 	I_ip_addr_dest  Destination IP adress
 * \param 	I_port_dest  	Destination port 
 * \param 	I_bytes  		Array to be sent
 * \param 	I_lenght  		Lenght of the array
 * \return 					ERROR: Transmission error, NO_ERROR: Success
 */
T_error socket_sendBytes(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, unsigned char* I_bytes, unsigned char I_lenght)
{
	/* Declaration */
	struct 	sockaddr_in server;
	T_error 			error 	= NO_ERROR;
	char				frame_sent[(I_lenght*3u) + 1u];
	char 				byte_ascii[4u];
	unsigned char		index, index_frame = 0u;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= inet_addr(I_ip_addr_dest);  
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

	if (sendto(I_socket_id, I_bytes, I_lenght, 0u, (struct sockaddr*) &server, sizeof(server)) == -1)
    {
        perror("sendto()");
        error = ERROR;
    }
    else
    {
    	/* printf */
    	for(index = 0u; index < I_lenght; index++)
    	{
    		sprintf(byte_ascii, "%x ", I_bytes[index]);
    		strcpy(&frame_sent[index_frame], byte_ascii);
    		index_frame = strlen(frame_sent);
    	}
	
		printf("\n\rBytes sent: %s", frame_sent);
    }

    return(error);
}

/**
 * \fn 		T_reception_state socket_readPacket(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, void* O_data, int I_lenght, T_state I_state)
 * \brief 	Read data from UDP/TCP communication
 *
 * \param 	I_socket_id 	ID of the receiver socket  
 * \param 	I_ip_addr_dest  Destination IP adress
 * \param 	I_port_dest  	Destination port 
 * \param 	O_data  		Expected data to be read
 * \param 	I_lenght  		Lenght of the expected data
 * \param 	I_state  		State of the reception
 * \return 					NO_PACKET_RECEIVED: No problem, PACKET_RECEIVED: Success, RECEPTION_ERROR: Something went wrong
 */
T_reception_state socket_readPacket(int I_socket_id, const char* I_ip_addr_dest, int I_port_dest, void* O_data, int I_lenght, T_state I_state)
{
	/* Declaration */
	struct 	sockaddr_in server;
	unsigned int 		lenght_server 	= sizeof(server);
	T_reception_state	state 			= RECEPTION_ERROR;
	int 				lenght_message;

	/* zero out the structure */
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= inet_addr(I_ip_addr_dest); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(I_port_dest);

    switch(I_state)
    {
    	case BLOCKING:
    		lenght_message = recvfrom(I_socket_id, O_data, I_lenght, 0u, (struct sockaddr*) &server, &lenght_server);
    		break;

    	case NON_BLOCKING:
    		lenght_message = recvfrom(I_socket_id, O_data, I_lenght, MSG_DONTWAIT, (struct sockaddr*) &server, &lenght_server);
    		break;
    }

	if (lenght_message < 0)
	{
		state = NO_PACKET_RECEIVED;
	}
	else
	{
		if (lenght_message > 0)
		{
			state = PACKET_RECEIVED;
		}
		else
		{
			state = RECEPTION_ERROR;
		}
	}

	return(state);
}

/**
 * \fn 		void socket_close(int I_socket_id)
 * \brief 	Close a used socket
 *
 * \param 	I_socket_id 	ID of the socket to be closed  
 */
void socket_close(int I_socket_id)
{
	/* Close the socket */
	close(I_socket_id);
}
