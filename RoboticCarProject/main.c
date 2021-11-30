/*
 * main.c
 *
 *  Created on: 29 Nov 2021
 *      Author: guancong
 */
#include "header/main.h"
#include "header/util.h"
#include "header/motordriver.h"
#include "header/ultrasonic.h"
#include "header/wheelencode.h"
#include "header/linesensor.h"

bool stoppedStatus = false;
volatile uint32_t SR04IntTimes = 0;
int carEngine = ENGINE_STOP;
int carState = MOV_STOP;

volatile uint32_t time_counter = 0;
volatile uint32_t timer_status = 0;
volatile uint32_t left_notch_counter = 0;
volatile uint32_t right_notch_counter = 0;

int main(void)
{
    Initalise_HCSR04();
    initMotorDriver();
    initWheelEncoder();
    initLineSensor();

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_disableSleepOnIsrExit();
    Interrupt_enableMaster();

    /* Configure P1.0 and set it to LOW */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    while (1)
    {
        Delay(3000);

        /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
        if ((getHCSR04Distance() < MIN_DISTANCE))
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        else
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        printObjectDistance();
    }
}

void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN1)
    {
        if (carState != MOV_STOP)
        {
            carState += 1;
        }
        else
        {
            carState = MOV_FORWARD;
        }

        if (carState == MOV_FORWARD){
            goForward();
        }
        else if (carState == MOV_LEFT)
        {
            turnLeft();
        }
        else if (carState == MOV_RIGHT)
        {
            turnRight();
        }
        else
        {
            isStop();
            carState = MOV_STOP;
        }
    }

    Delay(150000);
}
