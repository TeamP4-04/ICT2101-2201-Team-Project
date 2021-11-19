#include "myLib.h"
#include "wheelencoder.h"

int counter;
void initWheelEncoder(void)
{

    counter = 0;
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5); // Configure pin P2.5 as input (with pull up resistor)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);  // Configure pin P1.0 as output
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /** Interrupt GPIO Setting **/
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);   //  Clear the interrupt flag for pin P2.5
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);  // Enable interrupt for pin P2.5
    Interrupt_enableInterrupt(INT_PORT2);    // Enable interrupt for Port 2
    Interrupt_enableMaster(); // Enable master interrupt

    // while(1){
    //   PCM_gotoLPM3();  // Forever loop that puts the device to low power mode 3 state.
    // }

}

// Interrupt for Wheel Encoder
void PORT2_IRQHandler(void){
    uint_fast16_t status; // local integer variable

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);  //Interrupt status for Port 2 and store it into the local variable

    counter++; // Implement counter

    if(counter == 20){  // Check if the global variable is equal to 20 (number of notches on the wheel encoder).
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); // Toggle pin P1.0 and reset the local variable

        counter = 0;
    }
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status); // Clear the interrupt flag for Port 2
}

// Change speed function
void changeMotorSpeed()
{
    

}

// Calculate distance travelled
float calculateDistanceTravelled()
{

}