#include "lib.h"

#ifndef WHEEL_EN_H
#define WHEEL_EN_H

#define TICKPERIOD      1000
#define WHEEL_DIA       21.7
#define MINUTE          60
#define FULL_ROTATE     20

void initWheelEncoder(void);

extern volatile uint32_t time_counter;
extern volatile uint32_t timer_status;
extern volatile uint32_t left_notch_counter;
extern volatile uint32_t right_notch_counter;

#endif

