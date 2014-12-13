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
/* Constants 															  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Socket */
T_comm* 	        G_comm_SPVSR;
/* Buffer */
char	            G_orders[RECV_BUFF_SIZE];
unsigned char       G_square = 0u;
/* communication */
T_bool              G_disconnected = FALSE;
T_bool              G_comm_lost    = FALSE;
/* Mission */
T_bool              G_mission_started = FALSE;

/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/
/**
 * \fn 		T_error supervisor_initiate(void)
 * \brief 	Initializes the TCP communication between the client and the supervisor
 *
 * \return 	ERROR: Unable to establish a communication, NO_ERROR: Success
 */
T_error supervisor_initiate(void)
{
    T_error error = NO_ERROR;

    /* Initialisation */
    G_disconnected  = FALSE;
    G_comm_lost     = FALSE;

    /* Create a socket */
    // Supervisor socket with non blocking reception
    G_comm_SPVSR 	= communication_initiate(TCP, NULL, NULL, SPVSR_CLIENT_PORT, SPVSR_CLIENT_PORT, NON_BLOCKING);

    if(G_comm_SPVSR->client->id == -1)
    {
        error = ERROR;
    }
    else
    {
        /* Print the communication */
        printf("\n\rSPVSR Socket %d connected to %s:%d",   G_comm_SPVSR->client->id, inet_ntoa(G_comm_SPVSR->client->parameters.sin_addr), 
                                                                    (int)ntohs(G_comm_SPVSR->client->parameters.sin_port));
    }

    return(error);
}

/**
 * \fn 		void supervisor_close(void)
 * \brief 	Close the instantiated TCP socket
 *
 * \return 	ERROR: Unable to close the socket, NO_ERROR: Success
 */
void supervisor_close(void)
{
    socket_close(G_comm_SPVSR->client);
    socket_close(G_comm_SPVSR->server);
    free(G_comm_SPVSR);

     printf("\n\rSupervisor communication closed");
}

void supervisor_sendData(T_TCP_DATA I_data, char* arg)
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
            frame[2u] = arg[0u];
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
    }

    /* Send */
    socket_sendBytes(G_comm_SPVSR->protocol, G_comm_SPVSR->client->id, &G_comm_SPVSR->client->parameters, frame, frame[1u]+2u);
}

/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
/**
 * \fn 		void* supervisor_thread_interact(void* arg)
 * \brief 	Thread whih manages received orders
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 *
 * This thread reads received packets from the supervisor
 * And then process them to control the drone 
 */
void* supervisor_thread_interact(void* arg)
{
    /* Make this thread periodic */
    struct              periodic_info info;
    char                test[2u];
    T_reception_state   state;
    char                order_string[50u];

#ifdef PRINT_TCPUDP_DATA_SENT
    T_bool              print = TRUE;
    char                frame_received[(RECV_BUFF_SIZE*3u) + 1u];
    char                byte_ascii[20u];
    unsigned char       index;
    unsigned char       index_frame = 0u;
#endif


    make_periodic (INTERACT_TEMPO, &info);   

    while((G_disconnected == FALSE) && (G_comm_lost == FALSE))
    {
        /* zero out the structure */
        memset((char *) &G_orders, 0, sizeof(G_orders));

        /* Read orders from the supervisor */
        state = socket_readPacket(G_comm_SPVSR->protocol, G_comm_SPVSR->client->id, &G_comm_SPVSR->client->parameters, &G_orders, sizeof(G_orders), NON_BLOCKING);
        if(state == RECEPTION_ERROR)
        {
            G_comm_lost = TRUE;
            printf("\n\rCommunication with the supervisor lost");
        }
        else
        {
            /* Identifying the state */
            if(state == PACKET_RECEIVED)
            {
                #ifdef PRINT_TCPUDP_DATA_SENT
                    print = TRUE;
                #endif

                /* Process the received command */
                switch((T_TCP_DATA)G_orders[0u])
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
                            strcpy(order_string, "TAKEOFF REQUESTED");
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
                            strcpy(order_string, "LANDING REQUESTED");
                        }
                        break;

                    /* incomplete */
                    case TARGET_TCP:
                        /* Do nothing for the moment */
                        G_square = G_orders[2u];
                        /* Start the mission */
                        G_mission_started = TRUE;
                        /* Update order to print */
                        sprintf(order_string, "REACH SQUARE %d REQUESTED", G_orders[2u]);
                        break;

                    /* incomplete */
                    case STOP_TCP:
                        if(G_orders[2u] == 1u)
                        {
                            strcpy(order_string, "RESUME GAME REQUESTED");
                        }
                        else
                        {
                            strcpy(order_string, "PAUSE GAME REQUESTED");
                        }
                        break;

                    case DECON_TCP:
                        if(G_orders[2u] == 1u)
                        {
                            G_disconnected = TRUE;
                            strcpy(order_string, "DISCONNECTION REQUESTED");
                        }
                        break;

                    default:
                    #ifdef PRINT_TCPUDP_DATA_SENT
                        print = FALSE;
                    #endif
                        break;
                }

            #ifdef PRINT_TCPUDP_DATA_RECEIVED
                if(print == TRUE)
                {
                    /* printf */
                    sprintf(frame_received, "\n\rBytes received: %x %x", G_orders[0u], G_orders[1u]);
                    index_frame = strlen(frame_received);
                    for(index = 0u; index < G_orders[1u]; index++)
                    {
                        sprintf(byte_ascii, " %x", G_orders[index + 2u]);
                        strcpy(&frame_received[index_frame], byte_ascii);
                        index_frame = strlen(frame_received);
                    }
                    printf("%s through TCP -> [%s]", frame_received, order_string);
                }
                else
                {
                    printf("\n\rBytes received: ? through TCP");
                }
            #endif
                    
            }
            else
            {
                /* Do nothing */
            }
        }

#ifdef PRINT_TCPUDP_DATA_SENT
        printf("\n\r[SHARE_DATA] Nav: %x, Batt: %d, Ang: %f %f %f, Alt: %d, Speed: %d %d",
                ATcommand_navdata()->ctrl_state,
                (char)ATcommand_navdata()->vbat_flying_percentage,
                (int)ATcommand_navdata()->theta,
                (int)ATcommand_navdata()->phi,
                (int)ATcommand_navdata()->psi,
                ATcommand_navdata()->altitude,
                (int)ATcommand_navdata()->vx,
                (int)ATcommand_navdata()->vy);
#endif

        /* Share data with the supervisor */
        // Mission management 
        if((G_mission_started == TRUE) && (get_stateMission() == 0))
        {
            /* End of mission */
            printf("\n\rSupervisor has detected the end of the mission");
            /* Share it */
            test[0] = G_square;
            supervisor_sendData(TARGET_TCP,test);
            /* Initialization */
            G_square      = 0u;
            G_mission_started = FALSE;
        }

        supervisor_sendData(NAVDATA_TCP,NULL);
        supervisor_sendData(BATTERY_TCP,NULL);
        supervisor_sendData(ANGLES_TCP,NULL);
        supervisor_sendData(ALTITUDE_TCP,NULL);
        supervisor_sendData(SPEEDS_TCP,NULL);

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    printf("\n\rSupervisor disconnected");
    /* Close */
    supervisor_close();
    /* Close this thread */
    pthread_exit(NULL);
}

unsigned char getSquare(void)
{
    return(G_square);
}

T_bool supervisor_commLost(void)
{
    return(G_comm_lost);
}