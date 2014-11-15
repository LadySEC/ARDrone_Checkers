#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"
#include "communication.h"

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
#define NB_ORDERS			24u
/* Temporisations */
#define BUFFER_TEMPO		(unsigned int)30000
/* REF command */
#define TAKEOFF_COMMAND		290718208
#define LANDING_COMMAND		290717696
#define EMERGENCY_COMMAND 	290717952
/* Sockets */
#define AT_CLIENT_PORT		15213u
#define AT_SERVER_PORT		5556u
#define NAV_CLIENT_PORT		15214u
#define NAV_SERVER_PORT		5554u

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
}T_ATcommands;
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
	ROLL_LEFT,
	ROLL_RIGHT,
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
	REMOVE_CONFIGS,
	CHANGE_SESSION,
	CHANGE_PROFILE,
	CHANGE_APP,
	CHANGE_SSID
}T_ATorders;
/* Integer interpretation from floating value */
typedef union 
{
	int 	integer;
	float 	floating;
}T_word32bits;

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

  typedef enum 
  {
  	ALL_NAVDATA,
  	PROCESSED_NAVDATA
  }T_navdata_display;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
void ATcommand_initiate(void);
void ATcommand_close(void);
void ATcommand_process(T_ATorders I_order);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
void* ATcommand_thread_movements(void* arg);


#endif //! _AT_COMMAND_H_