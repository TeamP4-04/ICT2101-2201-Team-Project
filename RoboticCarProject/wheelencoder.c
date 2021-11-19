#include "myLib.h"
#include "wheelencoder.h"

/*Wheel Encoder Global Variables*/
volatile uint32_t notches_counter;
volatile uint32_t rotations;
volatile uint32_t totalNoOfRotations;
volatile float totalDistanceTravelled;
volatile float circumferenceOfWheel;
volatile float calculatedSpeed;

void initWheelEncoder(void)
{
    notches_counter = 0;
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5); // Configure pin P2.5 as input (with pull up resistor)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Configure pin P1.0 as output
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /** Interrupt GPIO Setting **/
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5); //  Clear the interrupt flag for pin P2.5
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5); // Enable interrupt for pin P2.5
    Interrupt_enableInterrupt(INT_PORT2);    // Enable interrupt for Port 2
    Interrupt_enableMaster(); // Enable master interrupt

    // while (1)
    // {
    //     calculateDistanceTravelled();
    //     PCM_gotoLPM3(); // Forever loop that puts the device to low power mode 3 state.
    // }

}


// void PORT2_IRQHandler(void)
// {
//     uint_fast16_t status; // local integer variable

//     status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2); //Interrupt status for Port 2 and store it into the local variable

//     /* Increment global variable (count the number of notches on the wheel encoder) */
//     notches_counter++;

//     /*  Check if the global variable is equal to 20 (20 notches = 1 wheel rotation) */
//     if (notches_counter == 20)
//     {
//         MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); // Toggle pin P1.0

//         /* Reset notch counter after each 1 wheel rotation */
//         notches_counter = 0;
//     }

//     /* Clear interrupt flag for Port 2*/
//     MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
// }

/*
 Calculation for Wheel Encoder:
 Circumference of Wheel = 21.7 cm

 no of pulse / 20  = no of rotation
 total distance = no of rotation x 21.7


 Pulse when 20 = 1 rotation
 Distance travelled for 1 pulse = (6.5/20) cm
 Total distance travelled by each wheel = Number of Pulses * Distance travelled for 1 pulse
 = Number of Pulses * (6.5/20) cm
 */
static uint32_t getNumberOfRotation(void)
{
    rotations = 0;

    /*  Check if the global variable is equal to 20 (20 notches = 1 wheel rotation) */
    if (notches_counter == 20)
    {
        rotations += 1;
        /* Reset notch counter after each 1 wheel rotation */
        notches_counter = 0;
    }

    printf("Total number of rotations : %zu \n", rotations);
    return rotations;

}

// Calculate distance traveled
float calculateDistanceTravelled()
{

    circumferenceOfWheel = 21.7;
    totalNoOfRotations = 5;
//    totalNoOfRotations = getNumberOfRotation();

    if (totalNoOfRotations > 0)
    {
        totalDistanceTravelled = (totalNoOfRotations * circumferenceOfWheel);
    }

    printf("Total distance traveled by wheel : %.1f \n", totalDistanceTravelled);
    return totalDistanceTravelled;
}

float calculateSpeed()
{
 // calculatedSpeed = (totalDistanceTravelled / time)
}
