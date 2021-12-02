#include "header/util.h"
#include "header/main.h"
#include "header/motordriver.h"

/*Delay function*/
void Delay(uint32_t loop)
{
    volatile uint32_t i;
    for (i = 0 ; i < loop ; i++);
}

void sendBytes(char arrays[]){

    int len = strlen(arrays);
    int i = 0;

    for(i = 0; i < len ; i++ ){
        MAP_UART_transmitData(EUSCI_A0_BASE, arrays[i]);
    }

}

void setCarMvtSate(char movementState)
{

    if (movementState == FORWARD)
    {
        //isStop();
        goForward();
        mvtState = FORWARD;
    }
    else if (movementState == LEFT)
    {
//        isStop();
        turnLeft();
        mvtState = LEFT;
    }
    else if (movementState == RIGHT)
    {
//        isStop();
        turnRight();
        mvtState = RIGHT;
    }
    else if (movementState == REVERSE)
    {
//        isStop();
        isReverse();
        mvtState = REVERSE;
    }
    else if (movementState == STOP)
    {
        isStop();
        mvtState = STOP;
    } else {

        isStop();
        mvtState = STOP;

    }
}

