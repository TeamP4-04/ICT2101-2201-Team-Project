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
#include "header/UARTusb.h"
#include "header/updateTimer.h"

void manualControl();
void resetCar();
/*variables modified by ISR must be declared volatile*/
volatile uint32_t SR04IntTimes = 0;
volatile uint32_t update_time_counter = 0;
volatile char carEngine = ENGINE_OFF;
volatile char carTransM = TRANSMANUAL;
volatile bool carState = STATE_CLEAR;
volatile char mvtState = STOP;
volatile uint32_t time_counter = 0;
volatile uint32_t timer_status = 0;
volatile uint32_t left_notch_counter = 0;
volatile uint32_t right_notch_counter = 0;
volatile float object_distance = 0;
char myArr[20];

int main(void)
{

    /*Initialising all the module on the car*/
    Initalise_HCSR04();
    initMotorDriver();
    initWheelEncoder();
    initLineSensor();
    initUARTUSB();
    initUpdateTimer();

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
        /* CHECK IF PATH INFRONT CAR IS CLEAR OR NOT*/
        object_distance = getHCSR04Distance();

        /*START UPDATE TIMER FOR DATA TO BE SEND*/
//        Timer_A_clearTimer(TIMER_A3_BASE);
//        Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);

        if ((object_distance < MIN_DISTANCE)){
            carState = STATE_BLOCKED;
        }
        else {
            carState = STATE_CLEAR;
        }

        //printf("the car state is : %d\n", carState);
        printf("object dist: %.1f\n", object_distance);

        /*IF TRANSMISSION IS MANUAL, GO TO SLEEP AND WAIT FOR INTERRUPTS, ELSE IF AUTO, USE ULTRASONIC AND LINESENSOR*/
        if (carTransM == TRANSMANUAL)
        {
            //MAP_PCM_gotoLPM0();
        }

        /*IF TRANSMISSION IS AUTO, ONLY ALLOW MOVEMENT WHEN PATH IS CLEAR*/
        if (carTransM == TRANSAUTO && carState == STATE_CLEAR) {
            trackLine();
        } else if (carState == STATE_BLOCKED) {
            setCarMvtSate(STOP);
        }
    }
}

// TIMER INTERRUPT TO SEND UPDATE EVERY 1s
void TA3_0_IRQHandler(void)
{
    update_time_counter++;

    if( update_time_counter == 1000 ){

        update_time_counter = 0;
        sprintf(myArr, "%.1f", object_distance);
        sendBytes(myArr);
        printf("%.1f\n ", object_distance);

    }
    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}


void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /*IF THE ENGINE IS OFF AND RECEIVE A SIGNAL TO TURN ON, CHANGE VAR TO ENGINE ON AND TRANSMISSION TO MANUAL*/
        if (carEngine == ENGINE_OFF && MAP_UART_receiveData(EUSCI_A0_BASE) == ENGINE_ON)
        {
            carEngine = ENGINE_ON;
            carTransM = TRANSMANUAL;
        }

        /*IF THE ENGINE IS ON AND RECEIVE A SIGNAL TO TURN OFF, CHANGE VAR TO ENGINE OFF*/
        if (carEngine == ENGINE_ON && MAP_UART_receiveData(EUSCI_A0_BASE) == ENGINE_OFF)
        {
            carEngine = ENGINE_OFF;
            setCarMvtSate(STOP);

        }

        /*IF THE ENGINE IS ON AND RECEIVE A SIGNAL TO CHANGE TRANSMISSION TO AUTO, ENGAGE THE ULTRASONIC AND TRACKER*/
        if (carEngine == ENGINE_ON && MAP_UART_receiveData(EUSCI_A0_BASE) == TRANSAUTO)
        {
            carTransM = TRANSAUTO;
            trackLine();
        }

        /*Changing to manual*/
        if (carEngine == ENGINE_ON && MAP_UART_receiveData(EUSCI_A0_BASE) == TRANSMANUAL)
        {
            carTransM = TRANSMANUAL;
            setCarMvtSate(STOP);
        }

        if (MAP_UART_receiveData(EUSCI_A0_BASE) == INCREASE_POW)
        {
            // call increase duty cycle
        }
        if (MAP_UART_receiveData(EUSCI_A0_BASE) == DECREASE_POW)
        {
            // call decrease duty cycle
        }

        if (carEngine == ENGINE_ON && carTransM == TRANSMANUAL)
        {
            manualControl();
        }

        MAP_UART_transmitData(EUSCI_A0_BASE, '/');
    }
}

void manualControl()
{

    if (MAP_UART_receiveData(EUSCI_A0_BASE) == FORWARD)
    {

        // sendBytes(forward);
        goForward();
    }
    else if (MAP_UART_receiveData(EUSCI_A0_BASE) == STOP)
    {

        // sendBytes(stop);
        isStop();
    }
    else if (MAP_UART_receiveData(EUSCI_A0_BASE) == LEFT)
    {

        // sendBytes(left);
        turnLeft();
    }
    else if (MAP_UART_receiveData(EUSCI_A0_BASE) == RIGHT)
    {

        // sendBytes(right);
        turnRight();
    }
    else if (MAP_UART_receiveData(EUSCI_A0_BASE) == REVERSE)
    {

        // sendBytes(reverse);
        isReverse();
    }
}

void resetCar(){

    carEngine = ENGINE_OFF;
    carTransM = TRANSMANUAL;
    carState = STATE_CLEAR;
    mvtState = STOP;
    
}
