
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include <stdio.h>			// Standard C ANSI
#include <stdlib.h>
#include <unistd.h>			// usleep
#include <pthread.h>		// POSIX library for thread management

/**********************************************************************************/
/* Constants														      		  */
/**********************************************************************************/
/* Debug */
#define DEBUG_NAVDATA
#define ENABLE_HOVERING

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
typedef enum 
{
	FALSE 	= 0u,
	TRUE  	= 1u  
}T_bool;

typedef enum 
{
	NO_ERROR = 0u,
	ERROR 	 = 1u  
}T_error;

#endif //! _GLOBAL_H_