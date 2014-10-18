/**
 * @file take_off.c
 * @author Pierre-Louis TILAK
 * @date 16/10/2014
 * @brief Minimal program with one thread, connect and take off the drone
 */
#include"take_off.h"

/**
  * @fn DEFINE_THREAD_ROUTINE
  * @brief Fonction de test des primitives de décollage
  * 
  * @param data 
  */
DEFINE_THREAD_ROUTINE(take_off, data)
{
        // Code de la function
   printf("salut");



  //  ardrone_tool_set_progressive_cmd( enable,
  //       /*roll*/(float)(stick1LR-center_x1)/32767.0f,
  //       /*pitch*/(float)(stick1UD-center_y1)/32767.0f,
  //        /*gaz*/-(float)(stick2UD-center_x2)/32767.0f,
  //         /*yaw*/(float)(stick2LR-center_y2)/32767.0f,
  //                  /*psi*/0.0,
  //          /*psi_accuracy*/0.0); 
ardrone_tool_set_ui_pad_start(1);
sleep(7);
ardrone_tool_set_ui_pad_start(0);

    //Return (THREAD_RET) 0;
}
