#include "header/linesensor.h"
#include "header/motordriver.h"

void initLineSensor(){

    //SETTING PINS AS INPUT
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7); //LEFT LINESENSOR
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN3); //RIGHT LINESENSOR

    //CLEAR AND ENABLE INTERRUPT FOR BOTH SENSOR
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN3);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN3);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN3);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN3);


    Interrupt_enableInterrupt(INT_PORT2);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();

}

void PORT2_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

    if (status & GPIO_PIN3){

        turnRight();
        //printf("Move Right\n");

    }

    if (status & GPIO_PIN7){

        //printf("Move LEFT\n");

    }

}