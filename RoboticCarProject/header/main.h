#ifndef HEADER_MAIN_H
#define HEADER_MAIN_H

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include "myLib.h"
#include "wheelencoder.h"
#include "motordriver.h"
#include "ultrasonic.h"
#include "linesensor.h"

// interrupts methods
void TA0_0_IRQHandler(void);
void PORT1_IRQHandler(void);

#endif /* HEADER_MAIN_H */
