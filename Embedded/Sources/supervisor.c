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
static const char* C_SUPERVISOR_IP				= "192.168.1.4";

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/
/* Socket */
T_comm* 	   G_comm_SPVSR;
/* Buffer */
char	       G_orders[RECV_BUFF_SIZE];

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

    /* Create a socket */
    // Supervisor socket with non blocking reception
    G_comm_SPVSR 	= communication_initiate(TCP, NULL, "127.0.0.1", SPVSR_CLIENT_PORT, SPVSR_CLIENT_PORT, NON_BLOCKING);

    if(G_comm_SPVSR->client->id == -1)
    {
        error = error;
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
            frame[3u] = arg[1u];
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
    socket_sendBytes(G_comm_SPVSR->server->id, &G_comm_SPVSR->client->parameters, frame, frame[1u]+2u);
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
    T_bool 	disconnected = FALSE;
    /* Make this thread periodic */
    struct  periodic_info info;
    char    test[2u];


    printf("\n\rStarting supervisor management thread");
    make_periodic (INTERACT_TEMPO, &info);   

    while(disconnected == FALSE)
    {
        /* zero out the structure */
        memset((char *) &G_orders, 0, sizeof(G_orders));

        /* Read orders from the supervisor */
        if(socket_readPacket(G_comm_SPVSR->server->id, &G_comm_SPVSR->server->parameters, &G_orders, sizeof(G_orders), NON_BLOCKING) == RECEPTION_ERROR)
        {
            printf("\n\rClient disconnected");
            disconnected = TRUE;
        }
        else
        {
            /* Processing order */
            printf("\n\rReceived paquet: %s", G_orders);

            if (strcmp(G_orders, "exit") == 0) 
            {
                disconnected = TRUE;
            }

            if (strcmp(G_orders, "takeoff") == 0) 
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
            }

            if (strcmp(G_orders, "land") == 0) 
            {
                if(ATcommand_FlyingState() == TRUE)
                {
                    /* Landing */
                    ATcommand_process(LANDING);
                    /* Wait the landing state */
                    while(ATcommand_FlyingState() != FALSE);
                }
            }

            if (strcmp(G_orders, "begin_m") == 0) 
            {
                ATcommand_moveDelay(PITCH_DOWN,     500000);
                ATcommand_moveDelay(HOVERING_BUFF,  2000000);
                ATcommand_moveDelay(ROLL_LEFT,      1500000);
            }

        }

#ifdef PRINT_TCPUDP_DATA_SENT
        printf("\n\rNav: %x, Batt: %d, Ang: %d %d %d, Alt: %d, Speed: %d %d",
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
        supervisor_sendData(NAVDATA_TCP,NULL);
        supervisor_sendData(BATTERY_TCP,NULL);
        supervisor_sendData(ANGLES_TCP,NULL);
        supervisor_sendData(ALTITUDE_TCP,NULL);
        supervisor_sendData(SPEEDS_TCP,NULL);

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    /* Close */
    supervisor_close();
    printf("\n\rEnding supervisor management thread");

    return(NULL);
}
