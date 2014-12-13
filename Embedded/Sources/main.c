/**
 * \file    main.c
 * \brief   Main program of the AR-drone embedded client
 * \author  Lady team
 * \version 1.0
 * \date    4 December 2014
 *
 */
/**********************************************************************************/
/* Libraries                                                                      */
/**********************************************************************************/
#include "global.h"
#include "keyboard.h"
#include "supervisor.h"
#include "calcul_order.h"
#include "../../Common/log.h"
/**********************************************************************************/
/* Global variables                                                               */
/**********************************************************************************/

/**********************************************************************************/
/* Procedures                                                                     */
/**********************************************************************************/
/* Block all real time signals so they can be used for the timers.
To be done before any threads are created so they all inherit the same mask. 
Doing it later is subject to race conditions */
void RTsignals_init(void)
{
    sigset_t        alarm_sig;
    int             i;

    sigemptyset (&alarm_sig);

    for (i = SIGRTMIN; i <= SIGRTMAX; i++)
    {
        sigaddset (&alarm_sig, i);
    }

    sigprocmask (SIG_BLOCK, &alarm_sig, NULL);
}

/**********************************************************************************/
/* Main program                                                                   */
/**********************************************************************************/
/**
 * \fn      int main (int argc, char *argv[])
 * \brief   Program entry
 *
 * \param   argc    Input argument
 * \param   argv    Input arguments
 * \return          Program output
 */
int main (int argc, char *argv[])
{
	int logLevel = LOG_DEBUG;
    /* Basic threads */
    pthread_t       th_ATcommand;

#ifdef ENABLE_KEYBOARD
    pthread_t       th_keyboard;
#endif

    /* Additional threads */
#ifdef ENABLE_SUPERVISOR
    pthread_t       th_supervisor;
#endif

#ifdef ENABLE_CALCUL_ORDER
    pthread_t       th_calcul_order;
#endif


    printf("\n\rStart\n\r");

    /* Initialize RT signals to enable threads to be periodic */
    RTsignals_init();
    printf("\n\rReal-time signals initialized");

    /* Initialize the logs */
    if (argc == 2) 
    { 
        logLevel = atoi(argv[1]); 
    }
    LOG_Init("log.log", logLevel);
    printf("\n\rLogs initialized");

    /* Initialize the communication with the Parrot server */
    printf("\n\rInitiating communication with the Parrot server ...");
    if(ATcommand_initiate() == NO_ERROR)
    {
        /* Initialize the movements thread */
        pthread_create (&th_ATcommand, NULL, ATcommand_thread_movements, NULL);
        printf("\n\rTh_ATcommand created");

#ifdef ENABLE_KEYBOARD
        /* Initialize the keyboard thread */
        pthread_create (&th_keyboard, NULL, kbd_thread_drone_controller, NULL);
        printf("\n\rTh_keyboard created");
#endif

#ifdef ENABLE_CALCUL_ORDER 
    	/* Initialize the mission thread */
    	pthread_create (&th_calcul_order, NULL, calcul_order_thread, NULL);
        printf("\n\rTh_calcul_order created");
#endif

#ifdef ENABLE_SUPERVISOR
        do
        {
            /* Initialize the supervisor thread (blocking function) */
            printf("\n\rInitiating communication with the supervisor ...");
            /* Blocking function */
            if(supervisor_initiate() == NO_ERROR)
            {
                pthread_create(&th_supervisor, NULL, supervisor_thread_interact, NULL);
                printf("\n\rTh_supervisor created");

                /* Waiting the end of supervisor thread */
                pthread_join(th_supervisor, NULL);
                printf("\n\rTh_supervisor closed");

                /* Emergency landing = Security */
                if(ATcommand_FlyingState() == TRUE)
                {
                    printf("\n\rEmergency landing");
                    /* Landing */
                    ATcommand_process(LANDING);
                    /* Wait the landing state */
                    while(ATcommand_FlyingState() != FALSE);
                }
            }
            else
            {
                printf("\n\rUnable to connect to the supervisor");
            }  
        }
        while(supervisor_commLost() == TRUE);
        
    #ifdef ENABLE_KEYBOARD
        /* Cancel the keyboard management */ 
        pthread_cancel(th_keyboard);
        printf("\n\rTh_keyboard canceled"); 
        /* Disable the raw mode */
        keyboard_rawMode(FALSE);
    #endif
#else
    #ifdef ENABLE_KEYBOARD
        /* Waiting the end of keyboard thread */
        pthread_join(th_keyboard, NULL);
        printf("\n\rTh_keyboard closed");
    #endif
#endif

#ifdef ENABLE_CALCUL_ORDER       
        pthread_cancel(th_calcul_order);
        printf("\n\rTh_calcul_order canceled"); 
#endif

        pthread_cancel(th_ATcommand);
        printf("\n\rTh_ATcommand canceled");
        ATcommand_close();
    }
    else
    {
        printf("\n\rUnable to initiate the communication with the Parrot server");
    }
	
	LOG_End();

    printf("\n\r\n\rEnd\n\r");
    return(0);
}
