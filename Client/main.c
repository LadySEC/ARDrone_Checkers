/* Useful libraries */
#include <stdio.h>			// Standard C ANSI
#include <stdlib.h>
#include <pthread.h>		// POSIX library for thread management
#include <malloc.h>			// Dynamic allocation
//#include <semaphore.h>	
#include <sys/socket.h>		// UDP/TCP
#include <netinet/in.h>
#include <string.h> 
#include <unistd.h>			// usleep

#include "global.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/* Sockets */
int socket_AT;

/**********************************************************************************/
/* Threads & Procedures														      */
/**********************************************************************************/

/* Threads */
void* test (void* arg)
{
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
   		die("socket");
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
	        die("bind");
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
        die("sendto()");
    }
}

void ATcommand_generate(char* frame, ATcommands command, int* sequence_number, word32bits* array, char strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
{
	/* Reset the frame */
	memset((char *) frame, 0, sizeof(frame));
	/* Generate correct AT command */
	switch(command)
	{
		case REF:
			sprintf(frame,"%s=%d,%d\r",commands[command], *sequence_number, array[0u].integer);
			break;

		case PCMD:
		case PCMD_MAG:
			sprintf(frame,"%s=%d,%d,%d,%d,%d,%d\r",commands[command], *sequence_number, 
					array[0u].integer, array[1u].integer, array[2u].integer, array[3u].integer, array[4u].integer);
			break;

		case FTRIM:
			sprintf(frame,"%s=%d\r",commands[command], *sequence_number);
			break;

		case CONFIG:
			sprintf(frame,"%s=%d,%s,%s\r",commands[command], *sequence_number,
					strings[0u], strings[1u]);
			break;

		case CONFIG_IDS:
			sprintf(frame,"%s=%d,%s,%s,%s\r",commands[command], *sequence_number,
					strings[0u], strings[1u], strings[3u]);
			break;	

		case COMWDG:
			sprintf(frame,"%s=%d\r",commands[command], *sequence_number);
			break;

		case CALIB:
			sprintf(frame,"%s=%d,%d\r",commands[command], *sequence_number, array[0u].integer);
			break;		
	}

	/* Update sequence number */
	*sequence_number = *sequence_number + 1u;
}

void ATcommand_send(ATorders order, int* sequence)
{
	char 		frame[NB_MAX_BITS_COMMAND];
	/* At commands management */
	word32bits 	ATarguments[NB_MAX_UNION_ARG];
	char 		ATstrings[NB_MAX_STRING_ARG][NB_MAX_CHAR];

	switch(order)
	{
		case TAKEOFF:
			ATarguments[0u].integer = TAKEOFF_COMMAND;
			ATcommand_generate(frame, REF, sequence, ATarguments, ATstrings);
			sendFrame(socket_AT, 5556, frame);
			break;

		case LANDING:
			ATarguments[0u].integer = LANDING_COMMAND;
			ATcommand_generate(frame, REF, sequence, ATarguments, ATstrings);
			sendFrame(socket_AT, 5556, frame);
			break;

		case HOVERING:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATcommand_generate(frame, PCMD, sequence, ATarguments, ATstrings);
			sendFrame(socket_AT, 5556, frame);
			break;	
	}

	/* Echo */
	printf("\n\rAT command sent: %s",frame);
}

void sprint1_demo(void)
{
	// Sequence number for AT commands
	int 		sequence = 1u;
	int 		cpt;

	/* Takeoff / hovering / landing */
	// Create a socket
	socket_AT = socket_init(UDP, 0u);

	printf("\n\rStart demo");
	// Takeoff
	ATcommand_send(TAKEOFF, &sequence);
	// Hovering
	for(cpt = 0u; cpt < NB_CYCLES; cpt++)
	{
		usleep(CYCLE_TEMPO);
		ATcommand_send(HOVERING, &sequence);
	}
	// Landing
	usleep(CYCLE_TEMPO);
	ATcommand_send(LANDING, &sequence);
	printf("\n\rEnd");

	// Close the socket
	close(socket_AT);
}

/**********************************************************************************/
/* Main program													      			  */
/**********************************************************************************/
int main (int argc, char *argv[])
{
	/* Declarations */
	/* Client version */
	printf("Client v0.3\n\r");

	/* Launch the demo */
	sprint1_demo();

	return(0);
}
