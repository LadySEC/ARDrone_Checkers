
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
typedef enum 
{
	TCP,
	UDP
} protocol;

typedef enum
{
	REF = 0,
	PCMD,
	PCMD_MAG,
	FTRIM,
	CONFIG,
	CONFIG_IDS,
	COMWDG,
	CALIB
}ATcommands;

typedef enum
{
	TAKEOFF = 0,
	LANDING,
	HOVERING
}ATorders;

typedef union 
{
	int 	integer;
	float 	floating;
}word32bits;

/**********************************************************************************/
/* Constants														      		  */
/**********************************************************************************/
#define NB_MAX_BITS_COMMAND 264u
#define NB_MAX_UNION_ARG	8u
#define NB_MAX_STRING_ARG	3u
#define NB_MAX_CHAR			20u
#define NB_AT_COMMANDS		8u
const char* commands[NB_AT_COMMANDS] = { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB" };
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
/* CONFIG command */
#define ARDRONE_SESSION_ID      "01234567" 
#define ARDRONE_PROFILE_ID      "89abcdef" 
#define ARDRONE_APPLOCATION_ID  "00000000" 

/* Demo */
#define NB_CYCLES			12u
#define CYCLE_TEMPO			(unsigned int)500000


#endif //! _GLOBAL_H_