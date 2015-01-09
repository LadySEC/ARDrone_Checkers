/**
 * \file 	calcul_distance.c
 * \brief 	Make the calculation for the drone distance
 * \author 	Lady team
 * \version 1.0
 * \date 	25 decembre 2014
 *
 */
/**********************************************************************************/
/* Libraries									*/
/**********************************************************************************/
#include "calcul_distance.h"
#include "at_command.h"
#include "detect_tag.h"
#include "../../Common/log.h"

/**********************************************************************************/
/* Constants 							  		  */
/**********************************************************************************/

/**********************************************************************************/
/* Global variables 								*/
/**********************************************************************************/

/**********************************************************************************/
/* Procedures									*/
/**********************************************************************************/

/**
 * \fn 		Position drone_pos(int RAZ,int Period)
 * \brief 	Calcul from speed the position of the drone
 * \param 	RAZ : Reset the position, Period : period of function call
 * \return      Position : calculated position
 *
 *  This function use the navdata informations
 *
 */
T_Position drone_pos(int RAZ,int Period){

    T_navdata_demo *navdata;

    static T_Position     O_position_new = {0,0,0};
    static T_Position     position_old = {0,0,0};
    static float          f_vx = 0.0;
    static float          f_vy = 0.0;
    static float          f_vx_old = 0.0;
    static float          f_vy_old = 0.0;
    static int            i_stateCnt = 0;

    // Get the last navdata infos to get the speed
    navdata = ATcommand_navdata();
    f_vx = navdata->vx;
    f_vy = navdata->vy;

    // TODO : ajouter la RAZ
    if(RAZ == 1){
        //O_position_new = {0,0,0};
        //position_old = {0,0,0};
    }

    if(i_stateCnt < 10){
        f_vx += round(f_vx/10);
        f_vy += round(f_vy/10);
        i_stateCnt ++;
    }
    else{
        f_vx /= 10;
        f_vy /= 10;

        // Calculation of the derivative (trapeze way)
        O_position_new.abs = position_old.abs + 0.5*(f_vx+f_vx_old)*1000*Period;
        O_position_new.ord = position_old.ord + 0.5*(f_vy+f_vy_old)*1000*Period;

        // Save the old values
        position_old = O_position_new;
        f_vx_old = f_vx;
        f_vy_old = f_vy;

        // Reset of current speed
        f_vx = 0.0;
        f_vy = 0.0;

        // Reset counter
        i_stateCnt = 0.0;
    }

    return O_position_new;
}

/**
 * \fn 		int float2int(float flt, float resolution)
 * \brief 	transcode a float into int
 * \param 	float number, resolution => 100.0 for example
 * \return      transcoded int
 */
int float2int(float flt, float resolution){
    int result;
    flt = flt*resolution;
    result = (int) flt;
    return result;
}
