/**
 * \file 	main.c
 * \brief 	Main program of the AR-drone embedded client
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include "keyboard.h"
#include "supervisor.h"
#include "calcul_order.h"
/**********************************************************************************/
/* Global variables 															  */
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
/* Main program													      			  */
/**********************************************************************************/
/**
 * \fn 		int main (int argc, char *argv[])
 * \brief 	Program entry
 *
 * \param 	argc 	Input argument
 * \param 	argv  	Input arguments
 * \return 			Program output
 */
int main (int argc, char *argv[])
{
    /* Signal */
    int sig_switch_off = 0;

    /* Thread */
    pthread_t 		th_ATcommand;

    // For the orders calculation
    pthread_t 		th_calcul_order;
    
    // For the image processing
    pthread_t           th_detect_tag;
#ifdef ENABLE_SUPERVISOR
    pthread_t 		th_supervisor;
#endif

#ifdef ENABLE_KBD_CONTROL
    pthread_t           th_kbd_control;
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

#ifdef ENABLE_KBD_CONTROL
    /* Initialize the keyboard control thread (blocking function) */
    printf("\n\rInitiating the keyboard control interface");
    pthread_create (&th_kbd_control, NULL, kbd_thread_drone_controller, NULL);
#endif


    /* Initialize the communication with the Parrot server */
    printf("\n\rInitiating communication with the Parrot server");
    if(ATcommand_initiate() == NO_ERROR)
    {
        /* Initialize the movements thread */
        pthread_create (&th_ATcommand, NULL, ATcommand_thread_movements, NULL);
        /* Launch thread for the autonomous flight*/
        pthread_create (&th_calcul_order, NULL, calcul_order_thread, NULL);
        pthread_create (&th_detect_tag, NULL, detect_tag_thread, NULL);

        // TODO : Find a condition on stop threads

        /* Close current threads */
        //pthread_cancel(th_ATcommand);
        /* Close all communications */
        //ATcommand_close();
        //
        //#ifdef ENABLE_SUPERVISOR
        //        pthread_cancel(th_supervisor);
        //        supervisor_close();
        //#endifi
        pthread_join(th_ATcommand,NULL);
        pthread_join(th_calcul_order,NULL);
        pthread_join(th_detect_tag,NULL);
#ifdef ENABLE_SUPERVISOE
        pthread_join(th_supervisor,NULL);
#endif
#ifdef ENABLE_KBD_CONTROL
        pthread_join(th_kbd_control,NULL);
#endif
    }
    else
    {
        printf("\n\rUnable to initiate the communication with the Parrot server ! ");
    }


    return(0);
}


