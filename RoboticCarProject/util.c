#include "header/util.h"

/*Delay function*/
void Delay(uint32_t loop)
{
    volatile uint32_t i;
    for (i = 0 ; i < loop ; i++);
}

