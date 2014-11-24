/**
 * \file 	calcul_order.c
 * \brief 	Make the calculation for the next drone orders
 * \author 	Lady team
 * \version 1.0
 * \date 	23 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "calcul_order.h"

/**********************************************************************************/
/* Constants 															  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/

/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
/**
 * \fn 		void* calcul_order_thread(void* arg)
 * \brief 	Thread which receive the tag position and calcul the next orders
 * \param 	arg 	Input argument
 * \return  		Nothing
 *
 * This thread reads received datas from the image processing thread
 * And then calcul the next orders
 */
void* calcul_order_thread(void* arg)
{

    /* Make this thread periodic */
    struct periodic_info info;
    make_periodic (_CALCUL_PERIOD, &info);


    while(1)
    {

        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    printf("\n\rEnding calcul_order_thread");

    return(NULL);
}
