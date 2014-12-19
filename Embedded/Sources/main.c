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

    /* Initialize the logs */
    if (argc == 2) 
    { 
        logLevel = atoi(argv[1]); 
    }
    else
    {
        logLevel = LOG_DEBUG;
    }
    LOG_Init("log.log", logLevel);
    LOG_WriteLevel(LOG_INFO, "main : TOP A LA VACHETTE!");

    /* Initialize RT signals to enable threads to be periodic */
    RTsignals_init();
    LOG_WriteLevel(LOG_INFO, "main : real-time signals initialized");

    /* Initialize the communication with the Parrot server */
    LOG_WriteLevel(LOG_INFO, "main : initiating communication with the Parrot server ...");
    if(ATcommand_initiate() == NO_ERROR)
    {
        /* Initialize the movements thread */
        pthread_create (&th_ATcommand, NULL, ATcommand_thread_movements, NULL);
        LOG_WriteLevel(LOG_INFO, "main : th_ATcommand created");

#ifdef ENABLE_KEYBOARD
        /* Initialize the keyboard thread */
        pthread_create (&th_keyboard, NULL, kbd_thread_drone_controller, NULL);
        LOG_WriteLevel(LOG_INFO, "main : th_keyboard created");
#endif

#ifdef ENABLE_CALCUL_ORDER 
    	/* Initialize the mission thread */
    	pthread_create (&th_calcul_order, NULL, calcul_order_thread, NULL);
        LOG_WriteLevel(LOG_INFO, "main : th_calcul_order created");
#endif

#ifdef ENABLE_SUPERVISOR
        do
        {
            /* Initialize the supervisor thread (blocking function) */
            LOG_WriteLevel(LOG_INFO, "main : initiating communication with the supervisor ...");
            /* Blocking function */
            if(supervisor_initiate() == NO_ERROR)
            {
                pthread_create(&th_supervisor, NULL, supervisor_thread_interact, NULL);
                LOG_WriteLevel(LOG_INFO, "main : th_supervisor created");
                
                /* Waiting the end of supervisor thread */
                pthread_join(th_supervisor, NULL);
                LOG_WriteLevel(LOG_INFO, "main : th_supervisor closed");

                /* Emergency landing = Security */
                if(ATcommand_FlyingState() == TRUE)
                {
                    /* Inform the emergency landing */
                    LOG_WriteLevel(LOG_WARN, "main : emergency landing");
                    /* Landing */
                    ATcommand_process(LANDING);
                    /* Wait the landing state */
                    while(ATcommand_FlyingState() != FALSE);
                }
            }
            else
            {
                LOG_WriteLevel(LOG_ERROR, "main : connection to the supervisor failed");
            }  
        }
        while(supervisor_commLost() == TRUE);
        
    #ifdef ENABLE_KEYBOARD
        /* Cancel the keyboard management */ 
        pthread_cancel(th_keyboard);
        LOG_WriteLevel(LOG_INFO, "main : th_keyboard canceled");
    #endif
#else
    #ifdef ENABLE_KEYBOARD
        /* Waiting the end of keyboard thread */
        pthread_join(th_keyboard, NULL);
        LOG_WriteLevel(LOG_INFO, "main : th_keyboard closed");
    #endif
#endif

#ifdef ENABLE_CALCUL_ORDER       
        pthread_cancel(th_calcul_order);
        LOG_WriteLevel(LOG_INFO, "main : th_calcul_order canceled");
#endif

        pthread_cancel(th_ATcommand);
        LOG_WriteLevel(LOG_INFO, "main : th_ATcommand canceled");
        ATcommand_close();
    }
    else
    {
        LOG_WriteLevel(LOG_ERROR, "main : connection to the Parrot server failed");
    }


    LOG_WriteLevel(LOG_INFO, "main : end");
    /* Disable the raw mode */
    keyboard_rawMode(FALSE);

    /* Stop the logs */
    LOG_End();
    return(0);
}
