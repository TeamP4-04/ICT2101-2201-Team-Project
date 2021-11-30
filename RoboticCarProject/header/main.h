#include "lib.h"

#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#define MIN_DISTANCE    15.0f
#define MOV_FORWARD     10
#define MOV_LEFT        11
#define MOV_RIGHT       12
#define MOV_BACK        13
#define MOV_STOP        14
#define ENGINE_START    20
#define ENGINE_STOP     21

volatile uint32_t SR04IntTimes;
bool stoppedStatus ;
int stateCounter ;


#endif 

