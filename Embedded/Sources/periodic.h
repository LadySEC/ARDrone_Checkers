#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#ifndef _PERIODIC_H
#define _PERIODIC_H
struct periodic_info
{
    int sig;
    sigset_t alarm_sig;
};



/**
 * \fn static int make_periodic(int unsigned period, struct periodic_info *info);
 * \brief Fonction de création de timer pour rendre un thread POSIX périodique
 *
 * \param period : periodre en ms, structure periodic_info 
 * \return état de la création du timer
 */
int make_periodic (int unsigned period, struct periodic_info *info);


/**
 * \fn static void wait_period(struct periodic_info *info);
 * \brief Fonction d'attente pour reboucler la prochaine fois après la période (à mettre dans la while(1) du thread)
 *
 * \param period : structure periodic_info 
 * 
 */
void wait_period (struct periodic_info *info);

#endif
