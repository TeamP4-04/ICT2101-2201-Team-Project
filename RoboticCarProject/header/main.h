#include "lib.h"

#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#define MIN_DISTANCE    15.0f

#define TRANSAUTO       'u'
#define TRANSMANUAL     'm'
#define FORWARD         'w'
#define LEFT            'a'
#define RIGHT           'd'
#define REVERSE         'r'
#define STOP            's'
#define ENGINE_ON       'o'
#define ENGINE_OFF      'p'
#define INCREASE_POW    '+'
#define DECREASE_POW    '-'
#define STATE_BLOCKED   true
#define STATE_CLEAR     false

int stateCounter ;
extern volatile char mvtState;

void EUSCIA0_IRQHandler(void);


#endif 

