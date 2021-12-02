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

volatile uint32_t SR04IntTimes = 0;
volatile char carEngine = ENGINE_OFF;
volatile char carTransM = TRNASMANUAL;
volatile bool carState = STATE_CLEAR;

volatile uint32_t time_counter = 0;
volatile uint32_t timer_status = 0;
volatile uint32_t left_notch_counter = 0;
volatile uint32_t right_notch_counter = 0;

int main(void)
{
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    Initalise_HCSR04();
    initMotorDriver();
    initWheelEncoder();
    initLineSensor();
    initUARTUSB();

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_disableSleepOnIsrExit();
    Interrupt_enableMaster();


    while (1)
    {
        //Delay(3000);

        /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
        // if ((getHCSR04Distance() < MIN_DISTANCE))
        //     GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        // else
        //     GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // printObjectDistance();
        MAP_PCM_gotoLPM0();
    }
}

void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // button press on p1.1
//    if (status & GPIO_PIN1)
//    {
//    }

    Delay(150000);
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);


    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /*IF THE ENGINE IS OFF AND RECEIVE A SIGNAL TO TURN ON, CHANGE VAR TO ENGINE ON AND TRANSMISSION TO MANUAL*/
        if(carEngine == ENGINE_OFF && MAP_UART_receiveData(EUSCI_A0_BASE) == ENGINE_ON){
            carEngine = ENGINE_ON;
            carTransM = TRNASMANUAL;
        }

        /*IF THE ENGINE IS ON AND RECEIVE A SIGNAL TO TURN OFF, CHANGE VAR TO ENGINE OFF*/
        if(carEngine == ENGINE_ON && MAP_UART_receiveData(EUSCI_A0_BASE) == ENGINE_OFF){
            carEngine = ENGINE_OFF;
            printf("Executed\n");
        }

        /*IF THE ENGINE IS ON AND RECEIVE A SIGNAL TO CHANGE TRANSMISSION TO AUTO, ENGAGE THE ULTRASONIC AND TRACKER*/
        if(carEngine == ENGINE_ON && MAP_UART_receiveData(EUSCI_A0_BASE) == TRANSAUTO){
            //call Autodetecting and line tracking method.
        }


        if(MAP_UART_receiveData(EUSCI_A0_BASE) == INCREASE_POW){
            //call increase duty cycle
        }
        if(MAP_UART_receiveData(EUSCI_A0_BASE) == DECREASE_POW){
            //call decrease duty cycle
        }


        if(carEngine == ENGINE_ON && carTransM == TRNASMANUAL){manualControl();}


        MAP_UART_transmitData(EUSCI_A0_BASE, '/');
    }

}

void manualControl(){

    if(MAP_UART_receiveData(EUSCI_A0_BASE) == FORWARD){

        //sendBytes(forward);
        goForward();


    } else if (MAP_UART_receiveData(EUSCI_A0_BASE) == STOP){

        //sendBytes(stop);
        isStop();


    } else if (MAP_UART_receiveData(EUSCI_A0_BASE) == LEFT){

        //sendBytes(left);
        turnLeft();


    } else if (MAP_UART_receiveData(EUSCI_A0_BASE) == RIGHT){

        //sendBytes(right);
        turnRight();


    } else if (MAP_UART_receiveData(EUSCI_A0_BASE) == REVERSE){

        //sendBytes(reverse);
        isReverse();


    }

}



