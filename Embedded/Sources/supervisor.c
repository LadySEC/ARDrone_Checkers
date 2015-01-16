/**
 * \file 	supervisor.c
 * \brief 	Manages all interactions with the supervisor
 * \author 	Lady team
 * \version 1.0
 * \date 	4 December 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "supervisor.h"

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Socket */
T_comm* 	        G_comm_SPVSR;
/* Buffer */
char	            G_orders[RECV_BUFF_SIZE];
unsigned char       G_square            = 0u;
/* communication */
T_bool              G_disconnected      = FALSE;
T_bool              G_comm_lost         = FALSE;
/* Mission */
T_bool              G_mission_started   = FALSE;

/**********************************************************************************/
/* Static functions prototypes                                                    */
/**********************************************************************************/
/**
 * \fn      void supervisor_sendData(T_TCP_data I_data)
 * \brief   Shares requested data through the TCP communication
 */
static void supervisor_sendData(T_TCP_data I_data);

/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/
T_error supervisor_initiate(void)
{
    T_error error = NO_ERROR;

    /* Initialisation */
    G_disconnected  = FALSE;
    G_comm_lost     = FALSE;

    /* Create a socket */
    // Supervisor socket with non blocking reception
    G_comm_SPVSR 	= communication_initiate(TCP, NULL, NULL, SPVSR_CLIENT_PORT, SPVSR_CLIENT_PORT, NON_BLOCKING);

    if(G_comm_SPVSR == NULL)
    {
        error = ERROR;
    }
    else
    {
        /* Print the communication */
        LOG_WriteLevel(LOG_INFO, "supervisor : socket %d connected to %s:%d", 
                        G_comm_SPVSR->client->id, inet_ntoa(G_comm_SPVSR->client->parameters.sin_addr), 
                        (int)ntohs(G_comm_SPVSR->client->parameters.sin_port));
        LOG_WriteLevel(LOG_INFO, "supervisor : communication opened");
    }

    return(error);
}

void supervisor_close(void)
{
    socket_close(G_comm_SPVSR->client);
    socket_close(G_comm_SPVSR->server);
    free(G_comm_SPVSR);

    LOG_WriteLevel(LOG_INFO, "supervisor : communication closed");
}

/**********************************************************************************/
/* Static functions                                                               */
/**********************************************************************************/
static void supervisor_sendData(T_TCP_data I_data)
{
    char    frame[15u];
    int     tmp;

    /* Mnémonique */
    frame[0u] = I_data;
    switch(I_data)
    {
        //Tested
        case NAVDATA_TCP:
            frame[1u] = 4u;
            memcpy(&frame[2u], &ATcommand_navdata()->ctrl_state, 4u);
            break;

        //Tested
        case BATTERY_TCP:
            frame[1u] = 1u;
            frame[2u] = (char)ATcommand_navdata()->vbat_flying_percentage;
            break;

        //Tested
        case TARGET_TCP:
            frame[1u] = 2u;
            frame[2u] = G_square;
            break;

        //Tested
        case ANGLES_TCP:
            frame[1u] = 12u;
            tmp       = (int)ATcommand_navdata()->theta;
            memcpy(&frame[2u], &tmp, 4u);
            tmp       = (int)ATcommand_navdata()->phi;
            memcpy(&frame[6u], &tmp, 4u);
            tmp       = (int)ATcommand_navdata()->psi;
            memcpy(&frame[10u], &tmp, 4u);
            break;

        //Tested
        case ALTITUDE_TCP:
            frame[1u] = 4u;
            memcpy(&frame[2u], &ATcommand_navdata()->altitude, 4u);
            break;

        // Not tested
        case SPEEDS_TCP:
            frame[1u] = 8u;
            tmp       = (int)ATcommand_navdata()->vx;
            memcpy(&frame[2u], &tmp, 4u);
            tmp       = (int)ATcommand_navdata()->vy;
            memcpy(&frame[6u], &tmp, 4u);
            break;

        case MISSION_TCP:
            frame[1u] = 1u;
            frame[2u] = (unsigned char)G_mission_started;
            break;
    }

    /* Send */
    socket_sendBytes(G_comm_SPVSR->protocol, G_comm_SPVSR->client->id, &G_comm_SPVSR->client->parameters, frame, frame[1u]+2u);
}

/**********************************************************************************/
/* Getters                                                                        */
/**********************************************************************************/
unsigned char getSquare(void)
{
    return(G_square);
}

T_bool supervisor_commLost(void)
{
    return(G_comm_lost);
}

/**********************************************************************************/
/* Setters                                                                        */
/**********************************************************************************/
void supervisor_setDisconnection(T_bool value)
{
    G_disconnected = value;
}

/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
void* supervisor_thread_interact(void* arg)
{
    /* Make this thread periodic */
    struct              periodic_info info;
    char                test[2u];
    T_reception_state   state;
    char                order_string[50u];
    unsigned long       timeStamp;
    char                date[50u];
    unsigned char       index;

#ifdef PRINT_TCP_DATA_RECEIVED
    T_bool              print = TRUE;
    char                frame_received[(RECV_BUFF_SIZE*3u) + 1u];
    char                byte_ascii[20u];
    unsigned char       index_frame = 0u;
#endif

    make_periodic (INTERACT_TEMPO, &info);   
    LOG_WriteLevel(LOG_INFO, "supervisor : thread period set to %dus",INTERACT_TEMPO);

    while((G_disconnected == FALSE) && (G_comm_lost == FALSE))
    {
        /* Share data with the supervisor */
    #ifdef DEBUG_NAVDATA
        LOG_WriteLevel(LOG_DEBUG, "supervisor : Nav: %x | Batt: %d | Ang: %f %f %f | Alt: %d | Speed: %d %d",
                ATcommand_navdata()->ctrl_state,
                (char)ATcommand_navdata()->vbat_flying_percentage,
                (int)ATcommand_navdata()->theta,
                (int)ATcommand_navdata()->phi,
                (int)ATcommand_navdata()->psi
                ATcommand_navdata()->altitude,
                (int)ATcommand_navdata()->vx,
                (int)ATcommand_navdata()->vy);
    #endif

        // Mission management 
        if((G_mission_started == TRUE) && (get_stateMission() == 0))
        {
            /* End of mission */
            LOG_WriteLevel(LOG_INFO, "supervisor : end of mission detected");
            /* Share the target square */
            supervisor_sendData(TARGET_TCP);
            /* Initialization */
            G_square      = 0u;
            G_mission_started = FALSE;
        }
        // Others data
        supervisor_sendData(NAVDATA_TCP);
        supervisor_sendData(BATTERY_TCP);
        supervisor_sendData(ANGLES_TCP);
        supervisor_sendData(ALTITUDE_TCP);
        supervisor_sendData(SPEEDS_TCP);
        supervisor_sendData(MISSION_TCP);

        /* Read an process orders from the supervisor */
        memset((char *) &G_orders, 0, sizeof(G_orders));
        state = socket_readPacket(G_comm_SPVSR->protocol, G_comm_SPVSR->client->id, &G_comm_SPVSR->client->parameters, &G_orders, sizeof(G_orders), NON_BLOCKING);
        switch(state)
        {
            case RECEPTION_ERROR:
                G_comm_lost = TRUE;
                LOG_WriteLevel(LOG_WARN, "supervisor : communication lost");
                break;

            case PACKET_RECEIVED:
            #ifdef PRINT_TCP_DATA_RECEIVED
                print = TRUE;
            #endif

                /* Process the received command */
                switch((T_TCP_data)G_orders[0u])
                {
                    case TAKEOFF_TCP:
                        if(G_orders[2u] == 1u)
                        {
                            if(ATcommand_enoughBattery() == TRUE)
                            {
                                if(ATcommand_FlyingState() == FALSE)
                                {
                                    /* Flat trim */
                                    ATcommand_process(TRIM);
                                    sleep(2u);
                                    /* Take off */
                                    ATcommand_process(TAKEOFF);
                                    /* Wait the flying state */
                                    while(ATcommand_FlyingState() != TRUE);
                                }
                            }
                            else
                            {
                                /* Not enough battery to takeoff */
                                ATcommand_process(CONFIGURATION_IDS);
                                ATcommand_process(LED_ANIMATION);
                            }
                            /* Update order to print */
                            strcpy(order_string, "TAKEOFF");
                        }
                        /* Landing */
                        else
                        {
                            if(ATcommand_FlyingState() == TRUE)
                            {
                                /* Landing */
                                ATcommand_process(LANDING);
                                /* Wait the landing state */
                                while(ATcommand_FlyingState() != FALSE);
                            }
                            /* Update order to print */
                            strcpy(order_string, "LANDING");
                        }
                        break;

                    /* incomplete */
                    case TARGET_TCP:
                        /* Do nothing for the moment */
                        G_square = G_orders[2u];
                        /* Start the mission */
                        G_mission_started = TRUE;
                        /* Update order to print */
                        sprintf(order_string, "REACH SQUARE %d", G_orders[2u]);
                        break;

                    case DECON_TCP:
                        if(G_orders[2u] == 1u)
                        {
                            G_disconnected = TRUE;
                            strcpy(order_string, "DISCONNECTION");
                        }
                        break;

                    case EMERGENCY_TCP:
                        ATcommand_process(EMERGENCY);
                        strcpy(order_string, "EMERGENCY");
                        break;

                    case TIME_TCP:
                        timeStamp = 0ul;
                        for(index = 0u; index < 4u; index++)
                        {
                            timeStamp |= ((unsigned long)G_orders[2u + index]) << (8u*(3u - index));
                        }
                        LOG_WriteLevel(LOG_DEBUG, "timeStamp = %x, %d", timeStamp, timeStamp);

                        /* Change the date */
                        sprintf(date, "date --set='@%d'", timeStamp);
                        system(date);
                        break;

                    default:
                    #ifdef PRINT_TCP_DATA_RECEIVED
                        print = FALSE;
                    #endif
                        break;
                }

            #ifdef PRINT_TCP_DATA_RECEIVED
                if(print == TRUE)
                {
                    /* printf */
                    sprintf(frame_received, "supervisor : bytes received: %x %x", G_orders[0u], G_orders[1u]);
                    index_frame = strlen(frame_received);
                    for(index = 0u; index < G_orders[1u]; index++)
                    {
                        sprintf(byte_ascii, " %x", G_orders[index + 2u]);
                        strcpy(&frame_received[index_frame], byte_ascii);
                        index_frame = strlen(frame_received);
                    }
                    LOG_WriteLevel(LOG_DEBUG, "%s -> %s order", frame_received, order_string);
                }
                else
                {
                    LOG_WriteLevel(LOG_DEBUG, "supervisor : incorrect data received");
                }
            #endif
                break;

            case NO_PACKET_RECEIVED:
                /* Do nothing */
                break;
        }

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    /* Inform the disconnection */
    LOG_WriteLevel(LOG_INFO, "supervisor : disconnected");
    /* Close */
    supervisor_close();
    /* Close this thread */
    pthread_exit(NULL);
}
