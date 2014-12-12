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
    pthread_t       th_keyboard;
	
	if (argc == 2) { logLevel = atoi(argv[1]); }
	LOG_Init("log.log", logLevel);

    /* Additional threads */
#ifdef ENABLE_SUPERVISOR
    pthread_t       th_supervisor;
#endif

#ifdef ENABLE_CALCUL_ORDER
    pthread_t       th_calcul_order;
#endif


    printf("\n\rStart\n\r");

    /* Initialize RT signals to enable threads to be periodic */
    printf("\n\rInitializing RT signals");
    RTsignals_init();

    /* Initialize the communication with the Parrot server */
    printf("\n\rInitiating communication with the Parrot server");
    if(ATcommand_initiate() == NO_ERROR)
    {
        /* Initialize the movements thread */
        printf("\n\rStarting th_ATcommand");
        pthread_create (&th_ATcommand, NULL, ATcommand_thread_movements, NULL);

        /* Initialize the keyboard thread */
        printf("\n\rStarting th_keyboard");
        pthread_create (&th_keyboard, NULL, kbd_thread_drone_controller, NULL);

#ifdef ENABLE_CALCUL_ORDER 
    	/* Initialize the mission thread */
        printf("\n\rStarting th_calcul_order");
    	pthread_create (&th_calcul_order, NULL, calcul_order_thread, NULL);
#endif

#ifdef ENABLE_SUPERVISOR
        do
        {
            /* Initialize the supervisor thread (blocking function) */
            printf("\n\rInitiating communication with the supervisor");
            if(supervisor_initiate() == NO_ERROR)
            {
                printf("\n\rStarting th_supervisor");
                pthread_create (&th_supervisor, NULL, supervisor_thread_interact, NULL);

                /* Waiting the end of supervisor thread */
                pthread_join(th_supervisor, NULL);
                printf("\n\rTh_supervisor closed");
            }
            else
            {
                printf("\n\rUnable to connect the supervisor");
            }  
        }
        while(supervisor_commLost() == TRUE);

        printf("\n\rClosing th_keyboard");  
        pthread_cancel(th_keyboard);
#else
        /* Waiting the end of keyboard thread */
        pthread_join(th_keyboard, NULL);
        printf("\n\rTh_keyboard closed");
#endif

#ifdef ENABLE_CALCUL_ORDER      
        printf("\n\rClosing th_calcul_order");  
        pthread_cancel(th_calcul_order);
#endif

        printf("\n\rClosing th_ATcommand");
        pthread_cancel(th_ATcommand);
        printf("\n\rClosing AT commands communication");
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
