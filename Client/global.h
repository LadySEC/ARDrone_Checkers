
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
	SERVER,
	CLIENT
} role;

typedef enum
{
	REF = 0,
	PCMD,
	PCMD_MAG,
	FTRIM,
	CONFIG,
	CONFIG_IDS,
	COMWDG,
	CALIB,
	CTRL
}ATcommands;

typedef enum
{
	TAKEOFF = 0,
	LANDING,
	YAW_LEFT,
	YAW_RIGHT,
	PITCH_UP,
	PITCH_DOWN,
	VERTICAL_UP,
	VERTICAL_DOWN,
	CONFIGURATION_IDS,
	INIT_NAVDATA,
	LED_ANIMATION,
	ACK_COMMAND,
	EMPTY_PACKET
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
#define NB_MAX_CHAR			30u
#define NB_AT_COMMANDS		9u
#define NB_MAX_COMMANDS		20u
#define NB_ORDERS			13u
const char* commands[NB_AT_COMMANDS] 	= { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB", "AT*CTRL" };
const char* orders[NB_ORDERS] 			= { "TAKEOFF", "LANDING", "YAW_LEFT", "YAW_RIGHT", "PITCH_UP", "PITCH_DOWN", "VERTICAL_UP", "VERTICAL_DOWN",
											"CONFIGURATION_IDS", "INIT_NAVDATA", "LED_ANIMATION", "ACK_COMMAND", "EMPTY_PACKET" };
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
/* CONFIG command */
const char* session_id 		= "\"01234567\"";
const char* profile_id 		= "\"ladyTeam\"";
const char* application_id 	= "\"Sprint1\""; 

/* Demo */
#define CYCLE_TEMPO			(unsigned int)30000

/* Keyboard */
#define UP_KEY			    0x41
#define DOWN_KEY			0x42
#define LEFT_KEY			68
#define RIGHT_KEY			67
#define ENTER_KEY			0x0D
#define SPACE_KEY			32		
#define CTRL_C_KEY			0x03
#define L_KEY    		108
#define BACKSPACE_KEY    	8
/* Colors */
#define WHITE_FONT			7
#define GREEN_FONT			2
#define RED_FONT			1
#define BLUE_FONT			4


#endif //! _GLOBAL_H_