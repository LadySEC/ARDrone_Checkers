/**
 * \file 	detect_tag.c
 * \brief 	Make the image processing for a tag
 * \author 	Lady team
 * \version 1.0
 * \date 	23 november 2014
 *
 */
/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "calcul_tag.h"

/**********************************************************************************/
/* Constants 															  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 															  */
/**********************************************************************************/

Position position_tag;
/**********************************************************************************/
/* Procedures														      		  */
/**********************************************************************************/

/**********************************************************************************/
/* Threads														      		      */
/**********************************************************************************/
/**
 * \fn 		void* detect_tag_thread(void* arg)
 * \brief 	Thread which receive the image and process the position of a tag
 * \param 	arg 	Input argument
 * \return  		Nothing
 *
 * This thread reads a frame from the camera and process it trying to find a tag, then 
 * send the position of the tag
 */
void* calcul_tag_thread(void* arg)
{

    /* Make this thread periodic */
    struct periodic_info info;
    make_periodic (_IMG_PERIOD, &info);

	printf("THREAD VIDEO - Demarrage\n");
    while(1)
    {
	
        position_tag = detect_wrapper("c","c");
        /* Wait until the next period is achieved */
        wait_period (&info);
    }

    printf("\n\rEnding calcul_order_thread");

    return(NULL);
}
