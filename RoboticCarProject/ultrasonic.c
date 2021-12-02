#include "header/ultrasonic.h"
#include "header/util.h"
#include "header/motordriver.h"
#include "header/main.h"

void Initalise_HCSR04(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig sonicConfig =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            TICKPERIOD,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
    };

    /* Configuring P3.6 as Output */
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);    // Trigger Pin (P3.6)
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P3, GPIO_PIN7); // Echo Pin (P3.7)


    /* Configuring Timer_A1 for Up Mode */
    Timer_A_configureUpMode(TIMER_A1_BASE, &sonicConfig);

    /* Enabling interrupts and starting the timer */
    Interrupt_enableInterrupt(INT_TA1_0);
    Timer_A_clearTimer(TIMER_A1_BASE);

    printf("Ultra-sonic initialised\n");

}

// Retrieve the Pulse time from Ultrasonic Sensor
uint32_t getHCSR04Time(void)
{
    uint32_t pulsetime = 0;

    /* Number of times the interrupt occurred (1 interrupt = 1000 ticks)    */
    pulsetime = SR04IntTimes * TICKPERIOD;

    /* Number of ticks (between 1 to 999) before the interrupt could occur */
    pulsetime += Timer_A_getCounterValue(TIMER_A1_BASE);

    /* Clear Timer */
    Timer_A_clearTimer(TIMER_A1_BASE);

    Delay(3000);

    return pulsetime;
}

// Calculate Object Distance from the Car
float getHCSR04Distance(void)
{
    uint32_t pulseDuration = 0;
    float calculatedDistance = 0;

    /* Generate 10us pulse at P3.6 */
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
    Delay(30);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);

    /* Wait for positive-edge */
    while(GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 0);

    /* Start Timer */
    SR04IntTimes = 0;
    //clear previous counter
    Timer_A_clearTimer(TIMER_A1_BASE);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    /* Detects negative-edge */
    while(GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 1);

    /* Stop Timer */
    Timer_A_stopTimer(TIMER_A1_BASE);

    /* Obtain Pulse Width in microseconds */
    pulseDuration = getHCSR04Time();

    /* Calculating distance in cm */
    calculatedDistance = (float)pulseDuration / 58.0f;

    return calculatedDistance;
}

// Display Object Distance Message
void validateObjectMessage(float objectDistance)
{
    //char message[100];

        objectDistance = getHCSR04Distance();

        /* if detected object and distance is less than 10cm, stop the car.
        if sensor reading is more than 10cm it will enable movement*/

        if (objectDistance < 15)
        {
            //call isStop() from Motor Driver
            if (carState == STATE_CLEAR)
            {
                isStop();
                carState = STATE_BLOCKED;
            }
            //strcpy(message, "Object detected!");
        }
        else
        {
            carState = STATE_CLEAR;
            goForward();
            //strcpy(message, "Clear of Obstacles.");
        }

        //printf("Message: %s \n", message);
}

// Print the Object distance
void printObjectDistance(void)
{
    float objectDistance = 0;

    objectDistance = getHCSR04Distance();
    validateObjectMessage(objectDistance);
    printf("Distance from an object is : %.2f cm \n", objectDistance);
}

// Interrupt for Ultrasonic Sensor
void TA1_0_IRQHandler(void)
{
    /* Increment global variable (count number of interrupt occurred) */
    SR04IntTimes++;

    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
