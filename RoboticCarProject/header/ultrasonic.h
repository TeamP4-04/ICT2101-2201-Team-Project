#include "lib.h"

#ifndef ULTRA_H
#define ULTRA_H

#define TICKPERIOD 1000

void Initalise_HCSR04(void);
uint32_t getHCSR04Time(void);
float getHCSR04Distance(void);
void validateObjectMessage(float objectDistance);
void printObjectDistance(void);

extern bool stoppedStatus;
extern volatile uint32_t SR04IntTimes;

#endif

