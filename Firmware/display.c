//******************************************************************************
// File Name:   commands.c
// Description: Serial Command Parser. Processes incoming data packets from
//              the IoT module and maps them to specific robot behaviors.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"


void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}



