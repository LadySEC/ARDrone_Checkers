/**
 * \file 	global.h
 * \brief 	Common declarations required for the whole project
 * \author 	Lady team
 * \version 1.0
 * \date 	18 november 2014
 *
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include <stdio.h>			// Standard C ANSI
#include <stdlib.h>
#include <unistd.h>			// usleep
#include <pthread.h>	    // POSIX library for thread management
#include <signal.h>

/**********************************************************************************/
/* Constants														      		  */
/**********************************************************************************/
/* Debug */
#define DEBUG_NAVDATA
#define ENABLE_HOVERING
//#define ENABLE_SUPERVISOR
#define ENABLE_KBD_CONTROL
#define ENABLE_SIGWAIT
//#define CONFIG_VIDEO
#define ENABLE_CALCUL_ORDER 

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
/**
 * \struct 	T_bool
 * \brief 	Defines a boolean state
 */
typedef enum 
{
	FALSE 	= 0u,	/*!< FALSE state */
	TRUE  	= 1u  	/*!< TRUE state */
}T_bool;

/**
 * \struct 	T_error
 * \brief 	Defines an error state
 */
typedef enum 
{
	NO_ERROR = 0u,	/*!< Everything works */
	ERROR 	 = 1u  	/*!< An error has occured */
}T_error;

#endif //! _GLOBAL_H_
