
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/* Types */
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

typedef union 
{
	int 	integer;
	float 	floating;
}word32bits;

/* Constants */
#define NB_MAX_BITS_COMMAND 264u
#define NB_MAX_UNION_ARG	8u
#define NB_MAX_STRING_ARG	3u
#define NB_MAX_CHAR			20u
#define NB_AT_COMMANDS		8u
const char* commands[NB_AT_COMMANDS] = { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB" };
/* REF command */
#define TAKEOFF_COMMAND		290718208//(unsigned int)0x200
#define LAND_COMMAND		(unsigned int)0x0
#define EMERGENCY_COMMAND	(unsigned int)0x100
/* CONFIG command */
#define ARDRONE_SESSION_ID      "01234567" 
#define ARDRONE_PROFILE_ID      "89abcdef" 
#define ARDRONE_APPLOCATION_ID  "00000000" 


#endif //! _GLOBAL_H_