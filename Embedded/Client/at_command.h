#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/
/* AT command configuration */
#define NB_MAX_BITS_COMMAND 264u
#define NB_MAX_UNION_ARG	8u
#define NB_MAX_STRING_ARG	3u
#define NB_MAX_CHAR			30u
#define NB_AT_COMMANDS		9u
#define NB_MAX_COMMANDS		20u
#define NB_ORDERS			19u
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
#define EMERGENCY_COMMAND 	290717952
/* CONFIG_IDS arguments */
const char* session_id 		= "00000000";
const char* profile_id 		= "00000000";
const char* application_id 	= "00000000"; 
/* Arrays */
const char* commands[NB_AT_COMMANDS] 	= { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB", "AT*CTRL" };
const char* orders[NB_ORDERS] 			= { "CALIBRATION", "TAKEOFF", "LANDING", "EMERGENCY", "HOVERING", "YAW_LEFT", "YAW_RIGHT", "PITCH_UP", "PITCH_DOWN", "VERTICAL_UP", "VERTICAL_DOWN",
											"CONFIGURATION_IDS", "INIT_NAVDATA", "LED_ANIMATION", "ACK_COMMAND", "NAVDATA_REQUEST", "RESET_WATCHDOG", "INIT_CONFIG", "CHANGE_SSID"};

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
/* List of available commands */
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
/* List of available orders */
typedef enum
{
	CALIBRATION =0,
	TAKEOFF,
	LANDING,
	EMERGENCY,
	HOVERING,
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
	NAVDATA_REQUEST,
	RESET_WATCHDOG,
	INIT_CONFIG,
	CHANGE_SSID
}ATorders;
/* Integer interpretation from floating value */
typedef union 
{
	int 	integer;
	float 	floating;
}word32bits;

#endif //! _AT_COMMAND_H_