/**
 * \file 	at_command.h
 * \brief 	Manages all AT commands compatible with the AR-Drone firmware
 * \author 	Lady team
 * \version 1.0
 * \date 	4 December 2014
 *
 */
#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include <malloc.h>
#include "communication.h"
#include "periodic.h"

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/
/* AT command configuration */
#define NB_MAX_BYTES_COMMAND 264u													/*!< Maximum lenght of an AT command string */
#define NB_MAX_UNION_ARG	8u														/*!< Maximum number of arguments to give progressive commands */
#define NB_MAX_STRING_ARG	3u 														/*!< Maximum number of string arguments to configure the drone */
#define NB_MAX_CHAR			30u														/*!< Maximum lenght of a string argument */
#define NB_AT_COMMANDS		9u														/*!< Number of different AT commands */
#define NB_MAX_COMMANDS		20u														/*!< Size of the commands buffer */
#define NB_ORDERS			33u 													/*!< Number of high-level orders available */
/* Temporisations */
#define BUFFER_TEMPO		(unsigned int)30000										/*!< at_command thread temporisation */
#define DEFAULT_DELAY		(unsigned int)3*BUFFER_TEMPO
/* REF command */
#define TAKEOFF_COMMAND		290718208 												/*!< Argument for performing a takeoff */
#define LANDING_COMMAND		290717696 												/*!< Argument for performing a landing */
#define EMERGENCY_COMMAND 	290717952 												/*!< Argument for shutting-down all motors */
/* Sockets */
#define AT_CLIENT_PORT		15213u 													/*!< UDP client port for sending AT commands */
#define AT_SERVER_PORT		5556u 													/*!< UDP server port */
#define NAV_CLIENT_PORT		15214u 													/*!< UDP client port for starting navdata emission */
#define NAV_SERVER_PORT		5554u 													/*!< UDP server port for reading navdata */
/* Dynamic parameters */
#define NB_DYNAMIC_PARAMETERS	5u
#define YAW_ANGLE_INIT			0.06f
#define PITCH_ANGLE_INIT		0.08f
#define ROLL_ANGLE_INIT			0.1f
#define VERTICAL_THRUST_INIT	0.05f
#define MOVE_TEMPO_INIT			800000.0f
#define ANGLE_DEFAULT_INC		0.02f	
#define TEMPO_DEFAUL_INC		50000.0f
/* Other */
#define LOW_BATTERY_LEVEL		15u

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
 /**
 * \struct 	T_ATcommands
 * \brief 	Defines all AT commands available
 */
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
}T_ATcommands;

 /**
 * \struct 	T_ATorders
 * \brief 	Defines all high-level orders available
 */
typedef enum
{
	TRIM =0,
	TAKEOFF,
	LANDING,
	EMERGENCY,
	HOVERING,
	HOVERING_BUFF,
	YAW_LEFT,
	YAW_RIGHT,
	ROLL_LEFT,
	ROLL_RIGHT,
	PITCH_UP,
	PITCH_DOWN,
	VERTICAL_UP,
	VERTICAL_DOWN,
	PITCH_DOWN_ROLL_RIGHT,
	PITCH_DOWN_ROLL_LEFT,
	PITCH_UP_ROLL_RIGHT,
	PITCH_UP_ROLL_LEFT,
	CONFIGURATION_IDS,
	INIT_NAVDATA,
	LED_ANIMATION,
	ACK_COMMAND,
	NAVDATA_REQUEST,
	RESET_WATCHDOG,
	REMOVE_CONFIGS,
	CHANGE_SESSION,
	CHANGE_PROFILE,
	CHANGE_APP,
	CHANGE_SSID,
	ENABLE_VIDEO,
	DISABLE_VIDEO,
	ENABLE_VISION,
	DISABLE_VISION
}T_ATorders;

 /**
 * \struct 	T_navdata_display
 * \brief 	Defines navdata display formats
 */
typedef enum 
{
	ALL_NAVDATA,
	PROCESSED_NAVDATA
}T_navdata_display;

 /**
 * \struct 	T_word32bits
 * \brief 	Integer interpretation from floating value
 */
typedef union 
{
	int 	integer;
	float 	floating;
}T_word32bits;

 /**
 * \struct 	T_navdata_demo
 * \brief 	Data structure of the expected navdata
 */
typedef struct 
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
  } T_navdata_demo;

 /**
 * \struct 	struct T_packet
 * \brief 	Defines a packet for the buffer
 */
struct T_packet    	
{
	T_ATorders			order;
    char* 				data;
    struct T_packet* 	next;
    struct T_packet* 	previous;
};

 /**
 * \struct 	T_packetBuffer
 * \brief 	Defines a buffer (chain list)
 */
typedef struct         	
{
    unsigned int 		nb_packets;
    struct T_packet* 	first;
    struct T_packet* 	last;
}T_packetBuffer;

 /**
 * \struct 	T_bufferState
 * \brief 	Defines differents state for the buffer
 */
typedef enum         	
{
    BUFFER_EMPTY = 0u,
    BUFFER_FULL,
}T_bufferState;

typedef enum 
{
	PITCH_ANGLE = 0u,
	ROLL_ANGLE,
	YAW_ANGLE,
	VERTICAL_THRUST,
	MOVE_TEMPO
}T_angle_param;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
T_error 		ATcommand_initiate(void);
void 			ATcommand_close(void);
void 			ATcommand_process(T_ATorders I_order);
void 			ATcommand_moveDelay(T_ATorders I_order, int I_us);

/* Getters */
T_bool 			ATcommand_FlyingState(void);
T_bool 			ATcommand_enoughBattery(void);
T_bool 			ATcommand_navdataError(void);
T_navdata_demo* ATcommand_navdata(void);
float 			getDynamicParameter(T_angle_param I_param);

/* Setters */
void 			incDynamicParameter(T_angle_param I_param, float I_incrementation);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
void* 			ATcommand_thread_movements(void* arg);


#endif //! _AT_COMMAND_H_
