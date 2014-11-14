#ifndef _NAVDATA_H_
#define _NAVDATA_H_

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include "global.h"

/**********************************************************************************/
/* Constants													      			  */
/**********************************************************************************/


/**********************************************************************************/
/* Types													      				  */
/**********************************************************************************/
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

#endif //! _NAVDATA_H_