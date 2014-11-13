
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

typedef union 
{
	int 	integer;
	float 	floating;
}word32bits;

typedef enum 
{  
	BLOCKING =0,
	NON_BLOCKING
} function_state;

typedef struct _navdata_demo_t 
{
	/* State */
	uint32_t    header;				/*!< Always set to NAVDATA_HEADER */
	uint32_t    ardrone_state;    	/*!< Bit mask built from def_ardrone_state_mask_t */
	uint32_t    sequence;         	/*!< Sequence number, incremented for each sent packet */
	uint32_t    vision_defined;

	/* Option */
    // Common part
    uint16_t    tag;
    uint16_t    size;

    // Specialize part
    uint32_t    ctrl_state;
    uint32_t    vbat_flying_percentage;
    float   	theta;
    float   	phi;
    float   	psi;
    int32_t     altitude;
    float   	vx;
    float   	vy;

    /* Checksum */
    uint16_t    cks_id;
    uint16_t    cks_size;
    uint32_t    cks_data;
  } navdata_demo_t;

/**********************************************************************************/
/* Constants														      		  */
/**********************************************************************************/
#define NB_MAX_BITS_COMMAND 264u
#define NB_MAX_UNION_ARG	8u
#define NB_MAX_STRING_ARG	3u
#define NB_MAX_CHAR			30u
#define NB_AT_COMMANDS		9u
#define NB_MAX_COMMANDS		20u
#define NB_ORDERS			19u
const char* commands[NB_AT_COMMANDS] 	= { "AT*REF", "AT*PCMD", "AT*PCMD_MAG", "AT*FTRIM", "AT*CONFIG", "AT*CONFIG_IDS", "AT*COMWDG", "AT*CALIB", "AT*CTRL" };
const char* orders[NB_ORDERS] 			= { "CALIBRATION", "TAKEOFF", "LANDING", "EMERGENCY", "HOVERING", "YAW_LEFT", "YAW_RIGHT", "PITCH_UP", "PITCH_DOWN", "VERTICAL_UP", "VERTICAL_DOWN",
											"CONFIGURATION_IDS", "INIT_NAVDATA", "LED_ANIMATION", "ACK_COMMAND", "NAVDATA_REQUEST", "RESET_WATCHDOG", "INIT_CONFIG", "CHANGE_SSID"};
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
#define EMERGENCY_COMMAND 	290717952

/* CONFIG command */
const char* session_id 		= "00000000";
const char* profile_id 		= "00000000";
const char* application_id 	= "00000000"; 

/* Temporisations */
#define BUFFER_TEMPO		(unsigned int)30000
#define WATCHDOG_TEMPO		(unsigned int)1000000
#define CONFIG_TEMPO		(unsigned int)200000

/* Keyboard */
#define UP_KEY			    0x41
#define DOWN_KEY			0x42
#define LEFT_KEY			68
#define RIGHT_KEY			67
#define ENTER_KEY			0x0D
#define SPACE_KEY			32		
#define CTRL_C_KEY			0x03
#define L_KEY    			108
#define BACKSPACE_KEY    	8
/* Colors */
#define WHITE_FONT			7
#define GREEN_FONT			2
#define RED_FONT			1
#define BLUE_FONT			4

/* Debug */
#define DEBUG_NAVDATA

#endif //! _GLOBAL_H_