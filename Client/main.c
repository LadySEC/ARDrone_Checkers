/* Useful libraries */
#include <stdio.h>			// Standard C ANSI
#include <pthread.h>		// POSIX library for thread management
//#include <malloc.h>		// Dynamic allocation
//#include <semaphore.h>	
#include <sys/socket.h>		// UDP/TCP
#include <netinet/in.h>

#include "global.h"

/* Global variables */
// Sockets

/* Threads */
void* test (void* arg)
{
	printf("\n\rRunning Thread");
  	return NULL;
}

/* Procedures */
void die(char *s)
{
    perror(s);
    exit(1);
}

int socket_init(protocol p, int port)
{
	/* Declaration */
	struct 	sockaddr_in client;
	int 				socket_id;

	// Generate a socket 
	switch(p)
	{
		case TCP:
			printf("\n\rCreating TCP socket");
			socket_id = socket(AF_INET , SOCK_STREAM , 0);
			break;

		case UDP:
			printf("\n\rCreating UDP socket");
			socket_id = socket(AF_INET , SOCK_DGRAM , 0);
			break;
	}

    if(socket_id == -1)
   	{
   		die("socket");
   	}
   	// Socket created
   	else
   	{
   		// zero out the structure
    	memset((char *) &client, 0, sizeof(client));

   		client.sin_addr.s_addr 	= htonl(INADDR_ANY); 
	    client.sin_family 		= AF_INET;
	    client.sin_port 		= htons(port);
	 
	 	//bind socket to port
	    if( bind(socket_id, (struct sockaddr*)&client, sizeof(client) ) == -1)
	    {
	        die("bind");
	    }

	    //Connect to remote server
	    if (connect(socket_id, (struct sockaddr *)&server, sizeof(server)) < 0)
	    {
	        printf("\n\rPort %d connected", port);
	    }
	    else
	   	{
	   		printf("\n\rPort %d error", port);
	   	}
   	}

    return(socket_id);
}
/*
void sendPacket(int socket_id, int port_dest, char* message)
{
	struct msghdr header;
}*/

/* Main program */
int main (int argc, char *argv[])
{
	/* Threads initialisation */
	pthread_t thread_id;
	/* Sockets */
	int socket_AT;

	printf("v0.1");
	/* Threads instantiation */
	pthread_create (&thread_id, NULL, &test, NULL);
	/* AT commands */
	socket_AT = socket_init(UDP, 0);

	return(0);
}
