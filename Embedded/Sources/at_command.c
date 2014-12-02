/**
 * \file 	at_command.c
 * \brief 	Manages all AT commands compatible with the AR-Drone firmware
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "at_command.h"

/**********************************************************************************/
/* Constants 															  		  */
/**********************************************************************************/
/* Local host */
static const char* C_LOCALHOST_IP				= "127.0.0.1";
/* CONFIG_IDS arguments */
static const char* C_SESSION_ID 				= "00000000";
static const char* C_PROFILE_ID 				= "00000000";
static const char* C_APPLICATION_ID 			= "00000000"; 
/* Arrays */
static const char* C_COMMANDS[NB_AT_COMMANDS] 	= { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB", "AT*CTRL" };
static const char* C_ORDERS[NB_ORDERS] 			= { "TRIM", "TAKEOFF", "LANDING", "EMERGENCY", "HOVERING", "YAW_LEFT", "YAW_RIGHT", "ROLL_LEFT", "ROLL_RIGHT", "PITCH_UP", "PITCH_DOWN", 
													"VERTICAL_UP", "VERTICAL_DOWN", "CONFIGURATION_IDS", "INIT_NAVDATA", "LED_ANIMATION", "ACK_COMMAND", "NAVDATA_REQUEST", 
													"RESET_WATCHDOG", "REMOVE_CONFIGS", "CHANGE_SESSION", "CHANGE_PROFILE", "CHANGE_APP", "CHANGE_SSID", "ENABLE_VIDEO", "DISABLE_VIDEO",
													"ENABLE_VISION", "DISABLE_VISION"};

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Mutexes */
pthread_mutex_t 		G_mutex_seqNum 			= PTHREAD_MUTEX_INITIALIZER;
/* Sequence number */
static int 				G_sequenceNumber 		= 1u;
/* Buffer management */
static T_packetBuffer	G_packetBuffer;
/* Socket */
static int 				G_socket_AT;
static int 				G_socket_NAV;
/* Navdata */
static T_navdata_demo  G_navdata;

/**********************************************************************************/
/* Prototypes														     		  */
/**********************************************************************************/
/* Getters */
T_bool 						ATcommand_FlyingState(void);
T_bool 						ATcommand_enoughBattery(void);
/* Static functions */
static void 				displayNavdata(T_navdata_display I_display);
static struct T_packet* 	createPacket(T_ATorders order, char* command);
static void 				deletePacket(struct T_packet* packet);
static void 				emitPacket(struct T_packet* packet);
static T_bufferState 		consumeBuffer(void);

/**********************************************************************************/
/* Procedures														     		  */
/**********************************************************************************/
/**
 * \fn 		T_error ATcommand_initiate(void)
 * \brief 	Allows the client to communicate with the Parrot server
 *
 * \return 	ERROR: Something went wrong during the process, NO_ERROR: Success
 */
T_error ATcommand_initiate(void)
{
	/* Declarations */
	char 	string[100u];
	T_error	error = NO_ERROR;

	/* Create a socket */
	// AT command socket
	G_socket_AT 	= socket_initiate(UDP, AT_CLIENT_PORT, BLOCKING);
	// Navdata socket with non blocking reception
	G_socket_NAV 	= socket_initiate(UDP, NAV_CLIENT_PORT, NON_BLOCKING);

	if((G_socket_AT != -1) && (G_socket_NAV != -1))
	{
		/* Initiate the configuration */
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(REMOVE_CONFIGS);
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(CHANGE_SESSION);
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(CHANGE_PROFILE);
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(CHANGE_APP);
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(CHANGE_SSID);
#ifdef CONFIG_VIDEO
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(DISABLE_VIDEO);
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(DISABLE_VISION);
#endif
		/* Initiate navdata reception */
		// Send a request to port 5554
		ATcommand_process(NAVDATA_REQUEST);
		// Forward the port 5554 to 15214
		system("iptables -t nat -F");
		sprintf(string,"iptables -t nat -A POSTROUTING -p UDP --sport %d -j SNAT --to 127.0.0.1:%d", NAV_CLIENT_PORT, NAV_SERVER_PORT);
		system(string);
		sprintf(string,"iptables -t nat -A PREROUTING -p UDP -d 127.0.0.1 --dport %d -j DNAT --to 127.0.0.1:%d", NAV_SERVER_PORT, NAV_CLIENT_PORT);
		system(string);
		usleep(100000);
		// Read the received packet
		socket_readPacket(G_socket_NAV, C_LOCALHOST_IP, NAV_CLIENT_PORT, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
		displayNavdata(PROCESSED_NAVDATA);
		// Init navdata demo
		ATcommand_process(CONFIGURATION_IDS);
		ATcommand_process(INIT_NAVDATA);
		usleep(100000);
		// Read the received packet
		socket_readPacket(G_socket_NAV, C_LOCALHOST_IP, NAV_CLIENT_PORT, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
		displayNavdata(PROCESSED_NAVDATA);
		// Send Ack paquet
		ATcommand_process(ACK_COMMAND);
	}
	else
	{
		error = ERROR;
	}

	return(error);
}

/**
 * \fn 		void ATcommand_close(void)
 * \brief 	Close all used sockets
 */
void ATcommand_close(void)
{
	socket_close(G_socket_AT);
	socket_close(G_socket_NAV);
}

/**
 * \fn 		void ATcommand_generate(char* O_frame, T_ATcommands I_command, T_word32bits* I_array, char I_strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
 * \brief 	Generates an 8-bit ASCII string from a given command and its arguments
 *
 * \param 	O_frame		Output string
 * \param 	I_command	Requested command
 * \param 	I_array		32-bit arguments array
 * \param 	I_strings	String arguments array
 */
void ATcommand_generate(char* O_frame, int I_frameSize, T_ATcommands I_command, T_word32bits* I_array, char I_strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
{
	/* Reset the frame */
	memset((char *) O_frame, 0, I_frameSize);
	/* Generate correct AT command */
	switch(I_command)
	{
		case REF:
			sprintf(O_frame,"%s=%d,%d\r",C_COMMANDS[I_command], G_sequenceNumber, I_array[0u].integer);
			break;

		case PCMD:
			sprintf(O_frame,"%s=%d,%d,%d,%d,%d,%d\r",C_COMMANDS[I_command], G_sequenceNumber, 
					I_array[0u].integer, I_array[1u].integer, I_array[2u].integer, I_array[3u].integer, I_array[4u].integer);
			break;

		case PCMD_MAG:
			sprintf(O_frame,"%s=%d,%d,%d,%d,%d,%d,%d,%d\r",C_COMMANDS[I_command], G_sequenceNumber, 
					I_array[0u].integer, I_array[1u].integer, I_array[2u].integer, I_array[3u].integer, I_array[4u].integer, I_array[5u].integer, I_array[6u].integer);
			break;

		case FTRIM:
			sprintf(O_frame,"%s=%d\r",C_COMMANDS[I_command], G_sequenceNumber);
			break;

		case CONFIG:
			sprintf(O_frame,"%s=%d,\"%s\",\"%s\"\r",C_COMMANDS[I_command], G_sequenceNumber,
					I_strings[0u], I_strings[1u]);
			break;

		case CONFIG_IDS:
			sprintf(O_frame,"%s=%d,\"%s\",\"%s\",\"%s\"\r",C_COMMANDS[I_command], G_sequenceNumber,
					I_strings[0u], I_strings[1u], I_strings[2u]);
			break;	

		case COMWDG:
			sprintf(O_frame,"%s=%d\r",C_COMMANDS[I_command], G_sequenceNumber);
			break;

		case CALIB:
			sprintf(O_frame,"%s=%d,%d\r",C_COMMANDS[I_command], G_sequenceNumber, I_array[0u].integer);
			break;		

		case CTRL:
			sprintf(O_frame,"%s=%d,%d\r",C_COMMANDS[I_command], G_sequenceNumber, I_array[0u].integer);
			break;	
	}

	/* Update sequence number */
	pthread_mutex_lock(&G_mutex_seqNum);
	G_sequenceNumber++;
	pthread_mutex_unlock(&G_mutex_seqNum);
}

/**
 * \fn 		void ATcommand_process(T_ATorders I_order)
 * \brief 	Processes high-level orders 
 *
 * \param 	I_order		Choosen order 
 */
void ATcommand_process(T_ATorders I_order)
{
	char 			frame[NB_MAX_BYTES_COMMAND];
	/* At commands management */
	T_word32bits 	ATarguments[NB_MAX_UNION_ARG];
	char 			ATstrings[NB_MAX_STRING_ARG][NB_MAX_CHAR];
	int 			sendToBuffer 	= 1u;
	unsigned char 	bytes[5u];

	/* Build the frame */
	switch(I_order)
	{
		case TRIM:
			sendToBuffer 			= 0u;
			ATcommand_generate(frame, sizeof(frame), FTRIM, ATarguments, ATstrings);
			break;

		case TAKEOFF:
			ATarguments[0u].integer = TAKEOFF_COMMAND;
			ATcommand_generate(frame, sizeof(frame), REF, ATarguments, ATstrings);
			break;

		case LANDING:
			ATarguments[0u].integer = LANDING_COMMAND;
			ATcommand_generate(frame, sizeof(frame), REF, ATarguments, ATstrings);
			break;

		case EMERGENCY:
			sendToBuffer 			= 0u;
			ATarguments[0u].integer = EMERGENCY_COMMAND;
			ATcommand_generate(frame, sizeof(frame), REF, ATarguments, ATstrings);
			break;

		case HOVERING:
			sendToBuffer 			= 0u;
			ATarguments[0u].integer = 0u;
			/* ROLL */
			ATarguments[1u].integer = 0u;
			/* PITCH */
			ATarguments[2u].integer = 0u;
			/* VERTICAL */
			ATarguments[3u].integer = 0u;
			/* YAW */
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;

		case YAW_RIGHT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].floating = YAW_CONSTANT;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case YAW_LEFT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].floating = -YAW_CONSTANT;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case ROLL_RIGHT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].floating = ROLL_CONSTANT;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case ROLL_LEFT:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].floating = -ROLL_CONSTANT;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case PITCH_UP:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].floating = PITCH_CONSTANT;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case PITCH_DOWN:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].floating = -PITCH_CONSTANT;
			ATarguments[3u].integer = 0u;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case VERTICAL_UP:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].floating = VERTICAL_CONSTANT;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;	

		case VERTICAL_DOWN:
			ATarguments[0u].integer = 1u;
			ATarguments[1u].integer = 0u;
			ATarguments[2u].integer = 0u;
			ATarguments[3u].floating = -VERTICAL_CONSTANT;
			ATarguments[4u].integer = 0u;
			ATarguments[5u].integer = 0u;
			ATarguments[6u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
			break;

		case INIT_NAVDATA:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "general:navdata_demo");
			strcpy(ATstrings[1u], "TRUE");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case CONFIGURATION_IDS:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], C_SESSION_ID);
			strcpy(ATstrings[1u], C_PROFILE_ID);
			strcpy(ATstrings[2u], C_APPLICATION_ID);
			ATcommand_generate(frame, sizeof(frame), CONFIG_IDS, ATarguments, ATstrings);
			break;

		case LED_ANIMATION:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "leds:leds_anim");
			strcpy(ATstrings[1u], "3,1073741824,2");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case ACK_COMMAND:
			sendToBuffer 			= 0u;
			ATarguments[0u].integer = 0u;
			ATcommand_generate(frame, sizeof(frame), CTRL, ATarguments, ATstrings);
			break;

		case NAVDATA_REQUEST:
			sendToBuffer 			= 0u;
			bytes[0u] 				= 1u;
			bytes[1u] 				= 0u;
			bytes[2u] 				= 0u;
			bytes[3u] 				= 0u;
			bytes[4u] 				= 0u;
			break;

		case RESET_WATCHDOG:
			sendToBuffer 			= 0u;
			ATcommand_generate(frame, sizeof(frame), COMWDG, ATarguments, ATstrings);
			break;

		case REMOVE_CONFIGS:
			sendToBuffer 			= 0;
			strcpy(ATstrings[0u], "custom:session_id");
			strcpy(ATstrings[1u], "-all");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case CHANGE_SESSION:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "custom:session_id");
			strcpy(ATstrings[1u], C_SESSION_ID);
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case CHANGE_PROFILE:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "custom:profile_id");
			strcpy(ATstrings[1u], C_PROFILE_ID);
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case CHANGE_APP:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "custom:application_id");
			strcpy(ATstrings[1u], C_APPLICATION_ID);
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);		
			break;

		case CHANGE_SSID:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "network:ssid_single_player");
			strcpy(ATstrings[1u], "Ardrone2_Lady");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case ENABLE_VIDEO:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "video_enable");
			strcpy(ATstrings[1u], "TRUE");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case DISABLE_VIDEO:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "video_enable");
			strcpy(ATstrings[1u], "FALSE");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case ENABLE_VISION:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "vision_enable");
			strcpy(ATstrings[1u], "TRUE");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;

		case DISABLE_VISION:
			sendToBuffer 			= 0u;
			strcpy(ATstrings[0u], "vision_enable");
			strcpy(ATstrings[1u], "FALSE");
			ATcommand_generate(frame, sizeof(frame), CONFIG, ATarguments, ATstrings);
			break;
	}

	/* Add the frame to the buffer */
	if(sendToBuffer == 1u)
	{
		/* Add a packet to the buffer */
		emitPacket(createPacket(I_order, frame));
	}
	else
	{
		/* Send directly the packet */
		//--------------------------------------------------------------------------------------------------------
		//printf("\n\r[%s] ", C_ORDERS[I_order]);
		if(I_order == NAVDATA_REQUEST)
		{
			socket_sendBytes(G_socket_NAV, C_LOCALHOST_IP, NAV_SERVER_PORT, bytes, 5u);
		}
		else
		{
			socket_sendString(G_socket_AT, C_LOCALHOST_IP, AT_SERVER_PORT, frame);
		}
	}
}

void moveDelay(T_ATorders I_order, int I_us)
{
	unsigned int counter;
	unsigned int nb_iterations = I_us / BUFFER_TEMPO;

	printf("\n\rMove Delay : nb_iterations = %d",nb_iterations);

	for(counter = 0; counter < nb_iterations; counter++)
	{
		ATcommand_process(I_order);
	}
}

/**
 * \fn 		T_bool ATcommand_FlyingState(void)
 * \brief 	Informs if the drone is flying or not
 *
 * \return 	TRUE: The drone is flying, FALSE: the drone is on the ground
 */
T_bool ATcommand_FlyingState(void)
{
	T_bool flying;

	if((G_navdata.ardrone_state & 0x1u) == 0u)
	{
		flying = FALSE;
	}
	else
	{
		flying = TRUE;
	}

	return(flying);
}


/**
 * \fn 		T_bool ATcommand_enoughBattery(void)
 * \brief 	Informs if there is enough battery level to takeoff
 *
 * \return 	TRUE: There is enough power, FALSE: Not enough battery level
 */
T_bool ATcommand_enoughBattery(void)
{
	T_bool enough;

	if(G_navdata.vbat_flying_percentage > 30u)
	{
		enough = TRUE;
	}
	else
	{
		enough = FALSE;
	}

	return(enough);
}


T_bool ATcommand_navdataError(void)
{
	T_bool error;

	if(((G_navdata.ardrone_state >> 30u) & 0x1u) == 0u)
	{
		error = FALSE;
	}
	else
	{
		error = TRUE;
	}

	return(error);
}

/**
 * \fn 		static void displayNavdata(T_navdata_display I_display)
 * \brief 	Displays usefull information from navdata
 *
 * \param 	I_display 	Navdata display format 
 */
static void displayNavdata(T_navdata_display I_display)
{
#ifdef DEBUG_NAVDATA
	switch(I_display)
	{
		case ALL_NAVDATA:
			/* Echo */
			//--------------------------------------------------------------------------------------------------------
			/*printf("\n\rNAVDATA: %x %x %x %x | %x  %x  %x %x | %f %f %f | %x | %f %f | %x %x %x", 
				G_navdata.header, G_navdata.ardrone_state, G_navdata.sequence, G_navdata.vision_defined, 
				G_navdata.tag, G_navdata.size, G_navdata.ctrl_state, G_navdata.vbat_flying_percentage, 
				G_navdata.theta, G_navdata.phi, G_navdata.psi, G_navdata.altitude , G_navdata.vx, G_navdata.vy,
				G_navdata.cks_id, G_navdata.cks_size, G_navdata.cks_data);*/
			break;

		case PROCESSED_NAVDATA:
			//--------------------------------------------------------------------------------------------------------
			/*printf("\n\rBatt: %d | Flying: %d | Theta: %d | Phi: %d | Psi: %d | Alt: %d | Vx: %d | Vy: %d | Err: %d", 	G_navdata.vbat_flying_percentage, 
																						G_navdata.ardrone_state & 0x1u,
																						(int)G_navdata.theta,
																						(int)G_navdata.phi,
																						(int)G_navdata.psi,
																						G_navdata.altitude,
																						(int)G_navdata.vx, (int)G_navdata.vy,
																						(G_navdata.ardrone_state >> 30u) & 0x1u);*/
			break;
	}
#endif
}

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
/**
 * \fn 		void* ATcommand_thread_movements(void* arg)
 * \brief 	Thread which manages the drone movements and updates navdata
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 * 
 * This periodic thread either reads the buffer content or send an hovering command by default
 * It also checks if a new navdata appeared and reset the watchdog
 */
void* ATcommand_thread_movements(void* arg)
{
    /* Make this thread periodic */
    struct periodic_info info;


    printf("\n\rStarting drone moves management thread");
#ifdef ENABLE_SIGWAIT
    make_periodic(BUFFER_TEMPO, &info);   
#endif

	while(1)
	{
		/* Empty the buffer or perform hovering */
		consumeBuffer();
	
		/* Read Navdata */
		socket_readPacket(G_socket_NAV, C_LOCALHOST_IP, NAV_CLIENT_PORT, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
		/* Display */
		displayNavdata(PROCESSED_NAVDATA);
		/* Reset Watchdog */
		ATcommand_process(RESET_WATCHDOG);

		/* Wait */
#ifdef ENABLE_SIGWAIT
        /* Wait until the next period is achieved */
       	wait_period (&info);
#else
       	usleep(BUFFER_TEMPO);
#endif
    }

    printf("\n\rEnding drone moves management thread");

    return NULL;
}

/**********************************************************************************/
/* Static procedures														      */
/**********************************************************************************/
/* Create a packet */
static struct T_packet* createPacket(T_ATorders order, char* command)
{
    struct T_packet* packet = (struct T_packet*)malloc(sizeof(struct T_packet));	/* Allocation memoire */

	/* Initialisation du paquet */
	packet->order 				= order;
    packet->data                = (char*)malloc((sizeof(char)*strlen(command)) + 1u);
    strcpy(packet->data, command);
    packet->next             	= NULL;
    packet->previous            = NULL;

    return(packet);
}

/* Delete a packet */
static void deletePacket(struct T_packet* packet)
{
    free(packet->data);
	free(packet);
}

/* Fill the buffer */
static void emitPacket(struct T_packet* packet)
{
    if(G_packetBuffer.first == NULL)
    {
        G_packetBuffer.first 		= packet;
    }
    else
    {
        G_packetBuffer.last->next 	= packet;
        packet->previous            = G_packetBuffer.last;
    }

    G_packetBuffer.last = packet;
    G_packetBuffer.nb_packets++;			
}

/* Empty the buffer */
static T_bufferState consumeBuffer(void)
{
	struct T_packet* 	tmp_packet;
	T_bufferState		state;

	/* Test if the buffer is empty */
    if(G_packetBuffer.first == NULL)
    {
    	/* Send an hovering command */
    	if(ATcommand_FlyingState() == TRUE)
		{
			ATcommand_process(HOVERING);
		}

       	/* Update the state */
        state 						= BUFFER_EMPTY;
    }
    else
    {
    	/* Read the packet */
		/* Send the command through the local host */
		//--------------------------------------------------------------------------------------------------------
		//printf("\n\r[%s] ", C_ORDERS[G_packetBuffer.first->order]);
		socket_sendString(G_socket_AT, C_LOCALHOST_IP, AT_SERVER_PORT, G_packetBuffer.first->data);
		//printf("(%d remaining commands)", G_packetBuffer.nb_packets - 1u);

    	/* Update the buffer */
    	tmp_packet = G_packetBuffer.first;
    	G_packetBuffer.first = tmp_packet->next;
    	deletePacket(tmp_packet);

    	if(G_packetBuffer.first != NULL)
    	{
    		G_packetBuffer.first->previous 	= NULL;
    		state 							= BUFFER_EMPTY;
    	}
    	else
    	{
    		state 							= BUFFER_FULL;
    	}

    	G_packetBuffer.nb_packets--;
    }

    return(state);
}

