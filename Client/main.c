/* Useful libraries */
#include <stdio.h>			// Standard C ANSI
#include <stdlib.h>
#include <pthread.h>		// POSIX library for thread management
#include <malloc.h>			// Dynamic allocation
//#include <semaphore.h>	
#include <sys/socket.h>		// UDP/TCP
#include <netinet/in.h>
#include <string.h> 

#include "global.h"

/* Global variables */


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
   	}

    return(socket_id);
}

void sendFrame(int socket_id, int port_dest, char* message)
{
	/* Declaration */
	struct 	sockaddr_in server;
	char 	buf[256];

	// zero out the structure
	memset((char *) &server, 0, sizeof(server));

	server.sin_addr.s_addr 	= htonl(INADDR_ANY); 
    server.sin_family 		= AF_INET;
    server.sin_port 		= htons(port_dest);
#if 0
   	sprintf(buf, "AT*CONFIG_IDS=%d,\"%s\",\"%s\",\"%s\"\r", 0, ARDRONE_SESSION_ID, ARDRONE_PROFILE_ID, ARDRONE_APPLOCATION_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));
	sprintf(buf, "AT*CONFIG=%d,\"custom:session_id\",\"%s\"\r", 1, ARDRONE_SESSION_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));

	sprintf(buf, "AT*CONFIG_IDS=%d,\"%s\",\"%s\",\"%s\"\r", 2, ARDRONE_SESSION_ID, ARDRONE_PROFILE_ID, ARDRONE_APPLOCATION_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));
	sprintf(buf, "AT*CONFIG=%d,\"custom:profile_id\",\"%s\"\r", 3, ARDRONE_PROFILE_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));

	sprintf(buf, "AT*CONFIG_IDS=%d,\"%s\",\"%s\",\"%s\"\r", 4, ARDRONE_SESSION_ID, ARDRONE_PROFILE_ID, ARDRONE_APPLOCATION_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));
	sprintf(buf, "AT*CONFIG=%d,\"custom:application_id\",\"%s\"\r", 5, ARDRONE_APPLOCATION_ID);
	sendto(socket_id, buf, strlen(buf)+1, 0, (sockaddr*)&server, sizeof(server));
#endif
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

/* Main program */
int main (int argc, char *argv[])
{
	/* Threads initialisation */
	pthread_t thread_id;
	/* Sockets */
	int socket_AT;
	/* AT commands */
	word32bits 	ATarguments[NB_MAX_UNION_ARG];
	char 		ATstrings[NB_MAX_STRING_ARG][NB_MAX_CHAR];
	char 		frame[NB_MAX_BITS_COMMAND];
	int 		sequence = 1u;

	printf("Client v0.3\n\r");
	/* Threads instantiation */
	pthread_create (&thread_id, NULL, &test, NULL);
	/* AT commands */
	socket_AT = socket_init(UDP, 0);

#if 0
	ATarguments[0u].floating = -0.8f;
	ATarguments[1u].floating = 1.35f;
	ATarguments[2u].floating = 15.4f;
	ATarguments[3u].floating = -2.45f;
	ATarguments[4u].floating = 3.987f;
#endif

#if 0
	/* Led animation */
	strcpy(ATstrings[0u], "\"leds:leds_anim\"");
	strcpy(ATstrings[1u], "\"3,1073741824,2\"");
	ATcommand_generate(frame, CONFIG, &sequence, ATarguments, ATstrings);
	printf("%s",frame);
	sendFrame(socket_AT, 5556, frame);
#endif

	/* Takeoff */
	ATarguments[0u].integer = TAKEOFF_COMMAND;
	ATcommand_generate(frame, REF, &sequence, ATarguments, ATstrings);
	printf("%s",frame);
	sendFrame(socket_AT, 5556, frame);
	close(socket_AT);

	return(0);
}
