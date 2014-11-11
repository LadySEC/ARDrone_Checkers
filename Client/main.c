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
#include <termios.h>

#include <time.h>
#include <signal.h>

#include "global.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/* Sockets */
int socket_AT;
/* Buffer */
char 	commandBuffer[NB_MAX_BITS_COMMAND][NB_MAX_COMMANDS]; 
int 	nb_received_commands 	= 0u;
int 	sequence_number 		= 1u;
/* Mutexes */
pthread_mutex_t mutex_seqNum = PTHREAD_MUTEX_INITIALIZER;

/**********************************************************************************/
/* Threads & Procedures														      */
/**********************************************************************************/

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

void ATcommand_generate(char* frame, ATcommands command, word32bits* array, char strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
{
	/* Reset the frame */
	memset((char *) frame, 0, sizeof(frame));
	/* Generate correct AT command */
	switch(command)
	{
		case REF:
			sprintf(frame,"%s=%d,%d\r",commands[command], sequence_number, array[0u].integer);
			break;

		case PCMD:
		case PCMD_MAG:
			sprintf(frame,"%s=%d,%d,%d,%d,%d,%d\r",commands[command], sequence_number, 
					array[0u].integer, array[1u].integer, array[2u].integer, array[3u].integer, array[4u].integer);
			break;

		case FTRIM:
			sprintf(frame,"%s=%d\r",commands[command], sequence_number);
			break;

		case CONFIG:
			sprintf(frame,"%s=%d,%s,%s\r",commands[command], sequence_number,
					strings[0u], strings[1u]);
			break;

		case CONFIG_IDS:
			sprintf(frame,"%s=%d,%s,%s,%s\r",commands[command], sequence_number,
					strings[0u], strings[1u], strings[3u]);
			break;	

		case COMWDG:
			sprintf(frame,"%s=%d\r",commands[command], sequence_number);
			break;

		case CALIB:
			sprintf(frame,"%s=%d,%d\r",commands[command], sequence_number, array[0u].integer);
			break;		
	}

	/* Update sequence number */
	sequence_number++;
}

void ATcommand_sendToBuffer(ATorders order)
{
	char 		frame[NB_MAX_BITS_COMMAND];
	/* At commands management */
	word32bits 	ATarguments[NB_MAX_UNION_ARG];
	char 		ATstrings[NB_MAX_STRING_ARG][NB_MAX_CHAR];

	/* Build the frame */
	switch(order)
	{
		case TAKEOFF:
			ATarguments[0u].integer = TAKEOFF_COMMAND;
			ATcommand_generate(frame, REF, ATarguments, ATstrings);
			break;

		case LANDING:
			ATarguments[0u].integer = LANDING_COMMAND;
			ATcommand_generate(frame, REF, ATarguments, ATstrings);
			break;

		case YAW_RIGHT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].floating = 0.5f;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;	

		case YAW_LEFT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].floating = -0.5f;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;	

		case PITCH_UP:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].floating = 0.5f;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;	

		case PITCH_DOWN:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].floating = -0.5f;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;	

		case VERTICAL_UP:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0.5f;
			ATarguments[3u].floating = 0.5f;
			ATarguments[4u].integer = 0u;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;	

		case VERTICAL_DOWN:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0.5f;
			ATarguments[3u].floating = 0.5f;
			ATarguments[4u].integer = 0u;
			ATcommand_generate(frame, PCMD, ATarguments, ATstrings);
			break;

		case CONFIGURATION_IDS:
			strcpy(ATstrings[0u], session_id);
			strcpy(ATstrings[1u], profile_id);
			strcpy(ATstrings[2u], application_id);
			ATcommand_generate(frame, CONFIG_IDS, ATarguments, ATstrings);
			break;

		case LED_ANIMATION:
			strcpy(ATstrings[0u], "\"leds:leds_anim\"");
			strcpy(ATstrings[1u], "\"3,1073741824,2\"");
			ATcommand_generate(frame, CONFIG, ATarguments, ATstrings);
			break;
	}

	/* Add the frame to the buffer */
	printf("\n\r%s:", orders[order]);
	strcpy(commandBuffer[nb_received_commands], frame);
	if(nb_received_commands < (NB_MAX_COMMANDS - 1))
	{
		nb_received_commands++;
	}
	else
	{
		nb_received_commands = 0u;
	}
}

void Mode_raw(int Activer)
{
    static struct termios Cooked;
    static int            Raw_Actif = 0;
    struct termios 		  Raw;

    if(Raw_Actif == Activer)
        return;

    if(Activer)
    {
        tcgetattr(STDIN_FILENO, &Cooked);

        Raw = Cooked;
        cfmakeraw(&Raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &Raw);
    }
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &Cooked);

    Raw_Actif = Activer;
}

int kbhit(void)
{
    struct timeval Tv = {0, 0};
    fd_set         Readfds;

    FD_ZERO(&Readfds);
    FD_SET(STDIN_FILENO, &Readfds);

    return select(STDIN_FILENO + 1, &Readfds, NULL, NULL, &Tv) == 1;
}

unsigned char _getch(void)
{
	unsigned char character = 0;


	character = getchar();		/* Lecture du caractere */

	/* Gestion des 3 octets codant un caractere special */
	if(character == 0x1B)
	{
		character = getchar();
		if(character ==	0x5B)
			character = getchar();
	}

	return(character);
}

/* Threads */
void* emptyBuffer (void* arg)
{
	int 	nb_sent_commands = 0u;

	printf("\n\rDebut du thread");

	while(1)
	{
		if(((nb_received_commands == 0u) && (nb_sent_commands > 0u)) || (nb_sent_commands < nb_received_commands))
		{
			/* Send the frame through local host */
			sendFrame(socket_AT, 5556, commandBuffer[nb_sent_commands]);
			/* Echo */
			printf("\n\rAT command sent: %s", commandBuffer[nb_sent_commands]);
			/* Update */
			if(nb_sent_commands < (NB_MAX_COMMANDS - 1))
			{
				nb_sent_commands++;
			}
			else
			{
				nb_sent_commands = 0u;
			}
		}
	
		/* Wait */
		usleep(CYCLE_TEMPO);
	}

  	return NULL;
}

/**********************************************************************************/
/* Main program													      			  */
/**********************************************************************************/
int main (int argc, char *argv[])
{
	/* Declarations */
	unsigned char  	key_pressed  	= 0;
	unsigned int   	key_selected	= 0;
	pthread_t 		thread1;
	unsigned char 	flying 			= 0u;

	/* Client version */
	printf("Client v0.3\n\r");

	/* Initialize the thread */
	pthread_create (&thread1, NULL, emptyBuffer, NULL);

	/* Create a socket */
	socket_AT = socket_init(UDP, 0u);

	/* Activate the terminal for brut mode */
	Mode_raw(1);

	do
	{
		/* Test */
        key_pressed = kbhit();
        if(key_pressed)
        {
            /* Read the selected key */
            key_selected = _getch();
	        switch(key_selected)
	        {
	            case UP_KEY	:
	            	ATcommand_sendToBuffer(PITCH_DOWN);
                	break;

	            case DOWN_KEY :
	            	ATcommand_sendToBuffer(PITCH_UP);
                	break;

                case LEFT_KEY	:
	            	ATcommand_sendToBuffer(YAW_LEFT);
                	break;

	            case RIGHT_KEY :
	            	ATcommand_sendToBuffer(YAW_RIGHT);
                	break;

                case ENTER_KEY :
	            	if(flying == 0u)
	            	{
	            		ATcommand_sendToBuffer(TAKEOFF);
	            		flying = 1u;
	            	}
	            	else
	            	{
	            		ATcommand_sendToBuffer(LANDING);
	            		flying = 0u;
	            	}
                	break;

                case SPACE_KEY :
	            	ATcommand_sendToBuffer(VERTICAL_UP);
                	break;
	        }

	        /* Empty the output buffer */
			fflush(stdout);
        }
	}
	while(key_selected != CTRL_C_KEY);

	printf("\n\rEnd");

	/* Activate the terminal for brut mode */
	Mode_raw(0);

	/* Close current threads */
   	pthread_cancel(thread1);

    /* Close the socket */
	close(socket_AT);

	return(0);
}
