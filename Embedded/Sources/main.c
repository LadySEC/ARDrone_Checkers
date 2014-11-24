/**
 * \file    main.c
 * \brief   Main program of the AR-drone embedded client
 * \author  Lady team
 * \version 1.0
 * \date    18 november 2014
 *
 */
/**********************************************************************************/
/* Libraries                                                                      */
/**********************************************************************************/
#include "global.h"
#include "keyboard.h"
#include "supervisor.h"

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
    /* Thread */
    pthread_t       th_ATcommand;
    pthread_t       th_keyboard;
#ifdef ENABLE_SUPERVISOR
    pthread_t       th_supervisor;
#endif


    printf("Start\n\r");
#ifdef ENABLE_SIGWAIT
    printf("\n\rInitializing RT signals");
    RTsignals_init();
#endif

#ifdef ENABLE_SUPERVISOR
    /* Initialize the supervisor thread (blocking function) */
    printf("\n\rInitiating communication with the supervisor");
    if(supervisor_initiate() == NO_ERROR)
    {
        pthread_create (&th_supervisor, NULL, supervisor_thread_interact, NULL);
    }
    else
    {
        printf("\n\rUnable to connect the supervisor");
    }
#endif

    /* Initialize the communication with the Parrot server */
    printf("\n\rInitiating communication with the Parrot server");
    if(ATcommand_initiate() == NO_ERROR)
    {
        /* Initialize the movements thread */
        pthread_create (&th_ATcommand, NULL, ATcommand_thread_movements, NULL);
        /* Initialize the keyboard thread */
        pthread_create (&th_keyboard, NULL, kbd_thread_drone_controller, NULL);

        /* Waiting the end of keyboard thread */
        pthread_join(th_keyboard, NULL);
        printf("\n\rClosing communications");
        /* Close current threads */
        pthread_cancel(th_ATcommand);
        /* Close all communications */
        ATcommand_close();

#ifdef ENABLE_SUPERVISOR        
        pthread_cancel(th_supervisor);
        supervisor_close();
#endif
    }

    return(0);
}
