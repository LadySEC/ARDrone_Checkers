
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
	HOVERING,
	CONFIGURATION_IDS,
	LED_ANIMATION
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
#define NB_MAX_COMMANDS		20u
const char* commands[NB_AT_COMMANDS] = { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB" };
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
/* CONFIG command */
const char* session_id 		= "\"01234567\"";
const char* profile_id 		= "\"ladyTeam\"";
const char* application_id 	= "\"sprint1\""; 

/* Demo */
#define NB_CYCLES			250u
#define CYCLE_TEMPO			(unsigned int)500000

/* Keyboard */
#define UP_KEY			    0x41
#define DOWN_KEY			0x42
#define ENTER_KEY			0x0D
#define CTRL_C_KEY			0x03


#endif //! _GLOBAL_H_