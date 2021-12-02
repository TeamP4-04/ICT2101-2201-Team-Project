#include "header/util.h"

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

