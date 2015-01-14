/**
 * \file 	at_command.h
 * \brief 	Manages all AT commands compatible with the AR-Drone firmware
 * \author 	Lady team
 * \version 1.0
 * \date 	9 January 2015
 *
 */
#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"												/*!< Retrieve all common tools */
#include <malloc.h>												/*!< Allow the use of dynamic allocations */
#include "communication.h"										/*!< Access to high-level UDP/TCP sockets functions */
#include "periodic.h"											/*!< Enables the thread to become periodic */

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/
/* AT command configuration */
#define NB_MAX_BYTES_COMMAND 	264u							/*!< Maximum lenght of an AT command string */
#define NB_MAX_UNION_ARG		8u								/*!< Maximum number of arguments to give progressive commands */
#define NB_MAX_STRING_ARG		3u 								/*!< Maximum number of string arguments to configure the drone */
#define NB_MAX_CHAR				30u								/*!< Maximum lenght of a string argument */
#define NB_AT_COMMANDS			9u								/*!< Number of different AT commands */
#define NB_MAX_COMMANDS			20u								/*!< Size of the commands buffer */
#define NB_ORDERS				33u 							/*!< Number of high-level orders available */
/* Temporisations */
#define BUFFER_TEMPO			(unsigned int)30000				/*!< at_command thread temporisation in us */
#define DEFAULT_DELAY 		 	3*BUFFER_TEMPO					/*!< default delay for a basic move */
/* REF command */
#define TAKEOFF_COMMAND			290718208 						/*!< Argument for performing a takeoff */
#define LANDING_COMMAND			290717696 						/*!< Argument for performing a landing */
#define EMERGENCY_COMMAND 		290717952 						/*!< Argument for shutting-down all motors */
/* Sockets */
#define AT_CLIENT_PORT			15213u 							/*!< UDP client port for sending AT commands */
#define AT_SERVER_PORT			5556u 							/*!< UDP server port */
#define NAV_CLIENT_PORT			15214u 							/*!< UDP client port for starting navdata emission */
#define NAV_SERVER_PORT			5554u							/*!< UDP server port for reading navdata */
/* Dynamic parameters */
#define NB_DYNAMIC_PARAMETERS	5u 								/*!< Number of dynamic parameters */
#define YAW_ANGLE_INIT			0.06f 							/*!< Initial value of the left/right yaw angle parameter */
#define PITCH_ANGLE_INIT		0.08f 							/*!< Initial value of the up/down pitch angle parameter */
#define ROLL_ANGLE_INIT			0.1f 							/*!< Initial value of the left/right roll angle parameter */
#define VERTICAL_THRUST_INIT	0.05f 							/*!< Initial value of the up/down vertical thrust parameter */
#define MOVE_TEMPO_INIT			800000.0f 						/*!< Initial value of the move temporisation parameter */
#define ANGLE_DEFAULT_INC		0.02f							/*!< Default incrementation for angle parameters (not used) */
#define TEMPO_DEFAUL_INC		50000.0f 						/*!< Default incrementation for temporisation parameters (not used) */
/* Other */
#define LOW_BATTERY_LEVEL		15u 							/*!< Lowest battery level allowed to takeoff */

/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
 /**
 * \struct 	T_ATcommands
 * \brief 	Defines all AT commands available
 */
typedef enum
{
	REF = 0,													/*!< Controls the basic behaviour of the drone (take-off/landing, emergency stop/reset) */
	PCMD,														/*!< Send progressive commands - makes the drone move (translate/rotate) */
	PCMD_MAG,													/*!< Send progressive commands with magnetometer */
	FTRIM,														/*!< Flat trims - Tells the drone it is lying horizontally */
	CONFIG,														/*!< Sets an configurable option on the drone */
	CONFIG_IDS,													/*!< Identifiers for the next AT*CONFIG command */
	COMWDG,														/*!< Reset communication watchdog */
	CALIB,														/*!< Magnetometer calibration - Tells the drone to calibrate its magnetometer */
	CTRL 														/*!< Unspecified/illegal command (not used) */
}T_ATcommands;

 /**
 * \struct 	T_ATorders
 * \brief 	Defines all available high-level orders
 */
typedef enum
{
	TRIM =0,													/*!< Perform a flat trim */
	TAKEOFF,													/*!< Perform a takeoff */
	LANDING,													/*!< Perform a landing */
	EMERGENCY,													/*!< Enable or disable the emergency */
	HOVERING,													/*!< Enable the drone to hover above its current position */
	HOVERING_BUFF,												/*!< Same order as above but buffered (not used)*/
	YAW_LEFT,													/*!< Basic yaw left move - buffered */
	YAW_RIGHT,													/*!< Basic yaw right move - buffered */
	ROLL_LEFT,													/*!< Basic roll left move - buffered */
	ROLL_RIGHT,													/*!< Basic roll right move - buffered*/
	PITCH_UP,													/*!< Basic pitch up move - buffered */
	PITCH_DOWN,													/*!< Basic pitch down move - buffered */
	VERTICAL_UP,												/*!< Basic vertical up thrust move - buffered */
	VERTICAL_DOWN,												/*!< Basic vertical down thrust move - buffered */
	PITCH_DOWN_ROLL_RIGHT,										/*!< Diagonal move (pitch down + roll right) - buffered */
	PITCH_DOWN_ROLL_LEFT,										/*!< Diagonal move (pitch down + roll left) - buffered */
	PITCH_UP_ROLL_RIGHT,										/*!< Diagonal move (pitch up + roll right) - buffered */
	PITCH_UP_ROLL_LEFT,											/*!< Diagonal move (pitch up + roll left) - buffered */
	CONFIGURATION_IDS,											/*!< Load a configuration profile */
	INIT_NAVDATA,												/*!< Initialise navdata */
	LED_ANIMATION,												/*!< Blink demonstration */
	ACK_COMMAND,												/*!< Accept the communication */
	NAVDATA_REQUEST,											/*!< Request for navdata emission */
	RESET_WATCHDOG,												/*!< Reset the watchdog timer */
	REMOVE_CONFIGS,												/*!< Remove all configuration profiles */
	CHANGE_SESSION,												/*!< Change the session ID */
	CHANGE_PROFILE,												/*!< Change the profile ID */
	CHANGE_APP,													/*!< Change the application ID */
	CHANGE_SSID,												/*!< Change the WiFi SSID */
	ENABLE_VIDEO,												/*!< Enable the video camera */
	DISABLE_VIDEO,												/*!< Disable the video camera */
	ENABLE_VISION,												/*!< Enable the video position control */
	DISABLE_VISION												/*!< Disable the video position control */
}T_ATorders;

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
	uint32_t    header;											/*!< Always set to NAVDATA_HEADER */
	uint32_t    ardrone_state;    								/*!< Bit mask built from def_ardrone_state_mask_t */
	uint32_t    sequence;         								/*!< Sequence number, incremented for each sent packet */
	uint32_t    vision_defined;									/*!<  */
	/* Option */
    // Common part
    uint16_t    tag; 											/*!<  */
    uint16_t    size; 											/*!< Data size */
    // Specialize part
    uint32_t    ctrl_state;										/*!< Drone state data */
    uint32_t    vbat_flying_percentage; 						/*!< Battery level percentage */
    float   	theta; 											/*!< Theta Euler angle */
    float   	phi; 											/*!< Phi Euler angle */
    float   	psi;											/*!< Psi Euler angle */
    int32_t     altitude; 										/*!< Altitude of the drone */
    float   	vx;												/*!< Horizontal speed of the drone */
    float   	vy;												/*!< Vertical speed of the drone */
    /* Checksum */
    uint16_t    cks_id; 										/*!< Checksum ID */
    uint16_t    cks_size;										/*!< Checksum size */
    uint32_t    cks_data;										/*!< Checksum data */
  } T_navdata_demo;

 /**
 * \struct 	struct T_packet
 * \brief 	Defines a packet for the FIFO buffer
 */
struct T_packet    	
{
	T_ATorders			order;									/*!< Order information */
    char* 				data;									/*!< Parrot command */
    struct T_packet* 	next;									/*!< Pointer to the next packet adress */
    struct T_packet* 	previous;								/*!< Pointer to the previous packet adress */
};

 /**
 * \struct 	T_packetBuffer
 * \brief 	Defines a buffer (chain list)
 */
typedef struct         	
{
    unsigned int 		nb_packets;								/*!< Number of packets stored */
    struct T_packet* 	first;									/*!< Pointer to the first packet address */
    struct T_packet* 	last;									/*!< Pointer to the last packet address */
}T_packetBuffer;

 /**
 * \struct 	T_bufferState
 * \brief 	Defines different states for the buffer
 */
typedef enum         	
{
    BUFFER_EMPTY = 0u,											/*!< The FIFO buffer is empty */
    BUFFER_FULL,												/*!< The FIFO buffer is full */
}T_bufferState;

 /**
 * \struct 	T_angle_param
 * \brief 	Defines all dynamic parameters
 */
typedef enum 
{
	PITCH_ANGLE = 0u,											/*!< Up/down pitch angle parameter */	
	ROLL_ANGLE,													/*!< Left/right roll angle parameter */
	YAW_ANGLE,													/*!< Left/right yaw angle parameter */
	VERTICAL_THRUST,											/*!< Up/down vertical thrust parameter */
	MOVE_TEMPO 													/*!< Move temporisation (not used) */
}T_angle_param;

/**********************************************************************************/
/* Prototypes													      			  */
/**********************************************************************************/
/**
 * \fn 		T_error ATcommand_initiate(void)
 * \brief 	Establishes a communication between this application and the Parrot server
 *
 * \return 	ERROR: Something went wrong during the process, NO_ERROR: Success
 * 
 *  Tasks:
 * 		- Open all UDP sockets
 *		- Initialise the configuration
 * 		- Initialise navdata emission
 */
T_error 		ATcommand_initiate(void);

/**
 * \fn 		void ATcommand_close(void)
 * \brief 	Closes all communications
 */
void 			ATcommand_close(void);

/**
 * \fn 		void ATcommand_process(T_ATorders I_order)
 * \brief 	Processes high-level orders 
 *
 * \param 	I_order		Choosen order 
 *
 *  Tasks:
 *      - Analyse the order
 *      - Obtain the correct string
 *      - Send it directly through TCP or synchronise it by means of a FIFO buffer 
 */
void 			ATcommand_process(T_ATorders I_order);

/**
 * \fn 		void ATcommand_moveDelay(T_ATorders I_order, int I_us)
 * \brief 	Fills the buffer with the same order for a specified duration
 */
void 			ATcommand_moveDelay(T_ATorders I_order, int I_us);

/**********************************************************************************/
/* Getters														     		  	  */
/**********************************************************************************/
/**
 * \fn 		T_bool ATcommand_FlyingState(void)
 * \brief 	Informs if the drone is flying or not
 *
 * \return 	TRUE: The drone is flying, FALSE: the drone is on the ground
 */
T_bool 			ATcommand_FlyingState(void);

/**
 * \fn 		T_bool ATcommand_enoughBattery(void)
 * \brief 	Informs if there is enough battery level to perform a takeoff
 *
 * \return 	TRUE: There is enough power, FALSE: Not enough battery level
 */
T_bool 			ATcommand_enoughBattery(void);

/**
 * \fn 		T_bool ATcommand_navdataError(void)
 * \brief 	Informs if the watchdog expired
 *
 * \return 	TRUE: Watchdog expired, FALSE: Ok
 */
T_bool 			ATcommand_navdataError(void);

/**
 * \fn 		T_navdata_demo* ATcommand_navdata(void)
 * \brief 	Returns the current navdata
 *
 * \Return 	All navdata received
 */
T_navdata_demo* ATcommand_navdata(void);

/**
 * \fn 		float getDynamicParameter(T_angle_param I_param);
 * \brief 	Returns the desired dynamic parameter
 *
 * \Return 	The dynamic parameter requested
 */
float 			getDynamicParameter(T_angle_param I_param);

/**********************************************************************************/
/* Setters														     		  	  */
/**********************************************************************************/
/**
 * \fn 		void incDynamicParameter(T_angle_param I_param, float I_incrementation);
 * \brief 	Increments the desired dynamic parameter by a given value
 */
void 			incDynamicParameter(T_angle_param I_param, float I_incrementation);

/**********************************************************************************/
/* Threads														     		  	  */
/**********************************************************************************/
/**
 * \fn 		void* ATcommand_thread_movements(void* arg)
 * \brief 	Thread which manages the drone movements and updates navdata
 *
 * \param 	arg 	Input argument 
 * \return  		Nothing
 * 
 *  Tasks:
 *      - Initialise the thread as periodic
 *      - Empty the FIFO buffer which loads the Parrot commands to be sent synchronously
 *      - Read and store the received navdata 
 */
void* 			ATcommand_thread_movements(void* arg);


#endif //! _AT_COMMAND_H_
