/**
 * \file 	at_command.c
 * \brief 	Manages all AT commands compatible with the AR-Drone firmware
 * \author 	Lady team
 * \version 1.0
 * \date    9 January 2015
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
static const char* C_ORDERS[NB_ORDERS] 			= { "TRIM", "TAKEOFF", "LANDING", "EMERGENCY", "HOVERING", "HOVERING_BUFF", "YAW_LEFT", "YAW_RIGHT", "ROLL_LEFT", "ROLL_RIGHT", "PITCH_UP", 
    "PITCH_DOWN", "VERTICAL_UP", "VERTICAL_DOWN", "PITCH_DOWN_ROLL_RIGHT", "PITCH_DOWN_ROLL_LEFT", "PITCH_UP_ROLL_RIGHT", "PITCH_UP_ROLL_LEFT","CONFIGURATION_IDS", "INIT_NAVDATA", "LED_ANIMATION", "ACK_COMMAND", "NAVDATA_REQUEST", 
    "RESET_WATCHDOG", "REMOVE_CONFIGS", "CHANGE_SESSION", "CHANGE_PROFILE", "CHANGE_APP", "CHANGE_SSID", "ENABLE_VIDEO", "DISABLE_VIDEO",
    "ENABLE_VISION", "DISABLE_VISION"};
static const char* C_DYNAMIC_PARAM[NB_DYNAMIC_PARAMETERS] = { "PITCH ANGLE", "ROLL ANGLE", "YAW ANGLE", "VERTICAL THRUST", "MOVE TEMPO"}; 

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Mutexes */
pthread_mutex_t 		G_mutex_seqNum 			= PTHREAD_MUTEX_INITIALIZER;
/* Sequence number */
static int 				G_sequenceNumber 		= 1u;
/* Buffer management */
static T_packetBuffer	G_packetBuffer;
/* Communications */
static T_comm* 			G_comm_AT;
static T_comm* 			G_comm_NAV;
/* Navdata */
static T_navdata_demo  	G_navdata;
/* Parameters*/
float                   G_dynamic_parameters[NB_DYNAMIC_PARAMETERS] = {PITCH_ANGLE_INIT, ROLL_ANGLE_INIT, YAW_ANGLE_INIT, VERTICAL_THRUST_INIT, MOVE_TEMPO_INIT};

/**********************************************************************************/
/* Static functions prototypes													  */
/**********************************************************************************/
/**
 * \fn      void ATcommand_generate(char* O_frame, int I_frameSize, T_ATcommands I_command, T_word32bits* I_array, char I_strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
 * \brief   Generates an 8-bit ASCII string from a given command and its arguments
 *
 * \param   O_frame     Output string
 * \param   I_frameSize Size of the frame
 * \param   I_command   Requested command to be processed
 * \param   I_array     32-bit arguments array
 * \param   I_strings   String arguments array
 *
 *  Tasks:
 *      - Process a given command
 *      - Generate the corresponding string
 */
static void                 ATcommand_generate(char* O_frame, int I_frameSize, T_ATcommands I_command, T_word32bits* I_array, char I_strings[NB_MAX_STRING_ARG][NB_MAX_CHAR]);

/**
 * \fn      static struct T_packet* createPacket(T_ATorders I_order, char* command)
 * \brief   Creates a packet to be buffered
 *
 * \param   I_order     Choosen order
 * \param   I_command   Assciated command
 *
 * \return  A pointer to the created packet
 *
 *  Tasks:
 *      - Allocates a new packet
 *      - Initialises all attributes
 */
static struct T_packet*     createPacket(T_ATorders I_order, char* I_command);

/**
 * \fn      static void deletePacket(struct T_packet* O_packet)
 * \brief   Deletes a packet
 *
 * \param   O_packet    Packet to be deleted
 */
static void                 deletePacket(struct T_packet* O_packet);

/**
 * \fn      static void emitPacket(struct T_packet* IO_packet)
 * \brief   Fill the buffer with a given packet
 *
 * \param   IO_packet   Packet to be buffered
 */
static void                 emitPacket(struct T_packet* IO_packet);

/**
 * \fn      static T_bufferState consumeBuffer(void)
 * \brief   Manages the FIFO buffer
 *
 * \return  BUFFER_EMPTY: All packets are sent, BUFFER_FULL: There is at least one packet to be sent
 *
 *  Tasks:
 *      - Send a command from the first packet
 *      - Delete the current packet and update the buffer state
 *      - Or send an hovering command to the Parrot server if the FIFO buffer is empty
 */
static T_bufferState        consumeBuffer(void);

/**********************************************************************************/
/* Getters                                                                        */
/**********************************************************************************/
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

T_bool ATcommand_enoughBattery(void)
{
    T_bool enough;

    if(G_navdata.vbat_flying_percentage > LOW_BATTERY_LEVEL)
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

T_navdata_demo* ATcommand_navdata(void)
{
    return(&G_navdata);
}

float getDynamicParameter(T_angle_param I_param)
{
    return(G_dynamic_parameters[I_param]);
}

void incDynamicParameter(T_angle_param I_param, float I_incrementation)
{
    G_dynamic_parameters[I_param] += I_incrementation;
    LOG_WriteLevel(LOG_INFO, "at_command : parameter %s = %f", C_DYNAMIC_PARAM[I_param], G_dynamic_parameters[I_param]);
}

/**********************************************************************************/
/* Procedures														     		  */
/**********************************************************************************/
T_error ATcommand_initiate(void)
{
    /* Declarations */
    char 	string[100u];
    T_error	error = NO_ERROR;

    /* Forward the port 5554 to 15214 */
    system("iptables -t nat -F");
    sprintf(string,"iptables -t nat -A POSTROUTING -p UDP --sport %d -j SNAT --to 127.0.0.1:%d", NAV_CLIENT_PORT, NAV_SERVER_PORT);
    system(string);
    sprintf(string,"iptables -t nat -A PREROUTING -p UDP -d 127.0.0.1 --dport %d -j DNAT --to 127.0.0.1:%d", NAV_SERVER_PORT, NAV_CLIENT_PORT);
    system(string);
    usleep(100000);

    /* Create a socket */
    // AT command socket
    G_comm_AT 	= communication_initiate(UDP, C_LOCALHOST_IP, C_LOCALHOST_IP, AT_CLIENT_PORT, AT_SERVER_PORT, BLOCKING);
    // Navdata socket with non blocking reception
    G_comm_NAV 	= communication_initiate(UDP, C_LOCALHOST_IP, C_LOCALHOST_IP, NAV_CLIENT_PORT, NAV_SERVER_PORT, NON_BLOCKING);

    if((G_comm_AT->client->id != -1) && (G_comm_NAV->client->id != -1))
    {
        /* Print the communication */
        LOG_WriteLevel(LOG_INFO, "at_command : commands socket %d connected to %s:%d",  
                        G_comm_AT->client->id, inet_ntoa(G_comm_AT->client->parameters.sin_addr), 
                        (int)ntohs(G_comm_AT->client->parameters.sin_port));

        LOG_WriteLevel(LOG_INFO, "at_command : navdata socket %d connected to %s:%d",  
                        G_comm_NAV->client->id, inet_ntoa(G_comm_NAV->client->parameters.sin_addr), 
                        (int)ntohs(G_comm_NAV->client->parameters.sin_port));
    
        /* Reset Watchdog first to avoid errors */
        G_sequenceNumber = 1u;
        ATcommand_process(RESET_WATCHDOG);

        /* Initiate the configuration */
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(REMOVE_CONFIGS);
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(CHANGE_SESSION);
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(CHANGE_PROFILE);
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(CHANGE_APP);
#ifdef ENABLE_CONFIG_VIDEO
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(DISABLE_VIDEO);
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(DISABLE_VISION);
#endif
        /* Initiate navdata reception */
        // Send a request to port 5554
        ATcommand_process(NAVDATA_REQUEST);

        // Read the received packet
        socket_readPacket(G_comm_NAV->protocol, G_comm_NAV->client->id, &G_comm_NAV->server->parameters, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
        // Init navdata demo
        ATcommand_process(CONFIGURATION_IDS);
        ATcommand_process(INIT_NAVDATA);
        usleep(100000);
        // Read the received packet
        socket_readPacket(G_comm_NAV->protocol, G_comm_NAV->client->id, &G_comm_NAV->server->parameters, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
        // Send Ack paquet
        ATcommand_process(ACK_COMMAND);

        LOG_WriteLevel(LOG_INFO, "at_command : communication opened");
    }
    else
    {
        error = ERROR;
    }

    return(error);
}

void ATcommand_close(void)
{
    socket_close(G_comm_AT->client);
    socket_close(G_comm_AT->server);
    socket_close(G_comm_NAV->client);
    socket_close(G_comm_NAV->server);
    free(G_comm_AT);
    free(G_comm_NAV);

    LOG_WriteLevel(LOG_INFO, "at_command : communication closed");
}

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
        case HOVERING_BUFF:
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
            ATarguments[4u].floating = G_dynamic_parameters[YAW_ANGLE];
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;	

        case YAW_LEFT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].integer = 0u;
            ATarguments[2u].integer = 0u;
            ATarguments[3u].integer = 0u;
            ATarguments[4u].floating = -G_dynamic_parameters[YAW_ANGLE];;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;	

        case ROLL_RIGHT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = G_dynamic_parameters[ROLL_ANGLE];
            ATarguments[2u].integer = 0u;
            ATarguments[3u].integer = 0u;
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;	

        case ROLL_LEFT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = -G_dynamic_parameters[ROLL_ANGLE];
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
            ATarguments[2u].floating = G_dynamic_parameters[PITCH_ANGLE];
            ATarguments[3u].integer = 0u;
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;	

        case PITCH_DOWN:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].integer = 0u;
            ATarguments[2u].floating = -G_dynamic_parameters[PITCH_ANGLE];
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
            ATarguments[3u].floating = G_dynamic_parameters[VERTICAL_THRUST];
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;	

        case VERTICAL_DOWN:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].integer = 0u;
            ATarguments[2u].integer = 0u;
            ATarguments[3u].floating = -G_dynamic_parameters[VERTICAL_THRUST];
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;

        case PITCH_DOWN_ROLL_RIGHT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = G_dynamic_parameters[ROLL_ANGLE];
            ATarguments[2u].floating = -G_dynamic_parameters[PITCH_ANGLE];
            ATarguments[3u].integer = 0u;
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;

        case PITCH_DOWN_ROLL_LEFT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = -G_dynamic_parameters[ROLL_ANGLE];
            ATarguments[2u].floating = -G_dynamic_parameters[PITCH_ANGLE];
            ATarguments[3u].integer = 0u;
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;

        case PITCH_UP_ROLL_RIGHT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = G_dynamic_parameters[ROLL_ANGLE];
            ATarguments[2u].floating = G_dynamic_parameters[PITCH_ANGLE];
            ATarguments[3u].integer = 0u;
            ATarguments[4u].integer = 0u;
            ATarguments[5u].integer = 0u;
            ATarguments[6u].integer = 0u;
            ATcommand_generate(frame, sizeof(frame), PCMD_MAG, ATarguments, ATstrings);
            break;

        case PITCH_UP_ROLL_LEFT:
            ATarguments[0u].integer = 1u;
            ATarguments[1u].floating = -G_dynamic_parameters[ROLL_ANGLE];
            ATarguments[2u].floating = G_dynamic_parameters[PITCH_ANGLE];
            ATarguments[3u].integer = 0u;
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
            strcpy(ATstrings[1u], "Ardrone1_Lady");
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
#ifdef PRINT_UDP_DATA_SENT
        LOG_WriteLevel(LOG_DEBUG, "at_command : %s command buffered", C_ORDERS[I_order]);
#endif
    }
    else
    {
        /* Send directly the packet */
#ifdef PRINT_UDP_DATA_SENT
        LOG_WriteLevel(LOG_DEBUG, "at_command : %s command requested", C_ORDERS[I_order]);
#endif
        if(I_order == NAVDATA_REQUEST)
        {
            socket_sendBytes(G_comm_NAV->protocol, G_comm_NAV->client->id, &G_comm_NAV->server->parameters, bytes, 5u);
        }
        else
        {
            socket_sendString(G_comm_AT->protocol, G_comm_AT->client->id, &G_comm_AT->server->parameters, frame);
        }
    }
}

void ATcommand_moveDelay(T_ATorders I_order, int I_us)
{
    unsigned int counter;
    unsigned int nb_iterations = I_us / BUFFER_TEMPO;

    for(counter = 0; counter < nb_iterations; counter++)
    {
        ATcommand_process(I_order);
    }
}

/**********************************************************************************/
/* Static functions                                                               */
/**********************************************************************************/
static void ATcommand_generate(char* O_frame, int I_frameSize, T_ATcommands I_command, T_word32bits* I_array, char I_strings[NB_MAX_STRING_ARG][NB_MAX_CHAR])
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

static struct T_packet* createPacket(T_ATorders I_order, char* I_command)
{
    /* Allocation memoire */
    struct T_packet* packet = (struct T_packet*)malloc(sizeof(struct T_packet));

    /* Initialisation du paquet */
    packet->order               = I_order;
    packet->data                = (char*)malloc((sizeof(char)*strlen(I_command)) + 1u);
    strcpy(packet->data, I_command);
    packet->next                = NULL;
    packet->previous            = NULL;

    return(packet);
}

static void deletePacket(struct T_packet* O_packet)
{
    free(O_packet->data);
    free(O_packet);
}

static void emitPacket(struct T_packet* IO_packet)
{
    if(G_packetBuffer.first == NULL)
    {
        G_packetBuffer.first        = IO_packet;
    }
    else
    {
        G_packetBuffer.last->next   = IO_packet;
        IO_packet->previous         = G_packetBuffer.last;
    }

    G_packetBuffer.last = IO_packet;
    G_packetBuffer.nb_packets++;            
}

static T_bufferState consumeBuffer(void)
{
    struct T_packet*    tmp_packet;
    T_bufferState       state;

    /* Test if the buffer is empty */
    if(G_packetBuffer.first == NULL)
    {
        /* Send an hovering command */
        if(ATcommand_FlyingState() == TRUE)
        {
            ATcommand_process(HOVERING);
        }

        /* Update the state */
        state = BUFFER_EMPTY;
    }
    else
    {
        /* Read the packet */
        /* Send the command through the local host */
#ifdef PRINT_UDP_DATA_SENT
        LOG_WriteLevel(LOG_DEBUG, "at_command : %s command requested (%d remaining packets)", 
                        C_ORDERS[G_packetBuffer.first->order],
                        G_packetBuffer.nb_packets - 1u);
#endif

        socket_sendString(G_comm_AT->protocol, G_comm_AT->client->id, &G_comm_AT->server->parameters, G_packetBuffer.first->data);

        /* Update the buffer */
        tmp_packet = G_packetBuffer.first;
        G_packetBuffer.first = tmp_packet->next;
        deletePacket(tmp_packet);

        if(G_packetBuffer.first != NULL)
        {
            G_packetBuffer.first->previous  = NULL;
            state                           = BUFFER_EMPTY;
        }
        else
        {
            state                           = BUFFER_FULL;
        }

        G_packetBuffer.nb_packets--;
    }

    return(state);
}

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
void* ATcommand_thread_movements(void* arg)
{
    /* Make this thread periodic */
    struct periodic_info info;


    make_periodic(BUFFER_TEMPO, &info); 
    LOG_WriteLevel(LOG_INFO, "at_command : thread period set to %dus", BUFFER_TEMPO);  

    while(1)
    {
        /* Empty the buffer or perform hovering */
        consumeBuffer();

        /* Read Navdata */
        socket_readPacket(G_comm_NAV->protocol, G_comm_NAV->client->id, &G_comm_NAV->server->parameters, &G_navdata, sizeof(G_navdata), NON_BLOCKING);
        /* Correct Navdata if there is an error */
        if(ATcommand_navdataError() == TRUE)
        {
            /* Inform the user */
            LOG_WriteLevel(LOG_ERROR, "at_command : incorrect navdata", BUFFER_TEMPO); 
            /* Reset the sequence number */
            G_sequenceNumber = 1u;
            ATcommand_process(RESET_WATCHDOG);
        }

        /* Reset Watchdog */
        ATcommand_process(RESET_WATCHDOG);

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    /* Close this thread */
    pthread_exit(NULL);
}
