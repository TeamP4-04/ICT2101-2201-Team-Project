#include "myLib.h"
#include "ultrasonic.h"

/*Ultrasonic Global Variables*/
volatile uint32_t SR04IntTimes;

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0 ; i < loop ; i++);
}

// Intialise Ultrasonic Sensor
void Initalise_HCSR04(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig upConfig =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            TICKPERIOD,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
    };

    int a = CS_getSMCLK();

    /* Configuring P3.6 as Output */
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);    // Trigger Pin (P3.6)
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P3, GPIO_PIN7); // Echo Pin (P3.7)


    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    /* Enabling interrupts and starting the timer */
    Interrupt_enableInterrupt(INT_TA0_0);
    //Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    //Timer_A_stopTimer(TIMER_A0_BASE);
    Timer_A_clearTimer(TIMER_A0_BASE);

}

// Interrupt for Ultrasonic Sensor
void TA0_0_IRQHandler(void)
{
    /* Increment global variable (count number of interrupt occurred) */
    SR04IntTimes++;

    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
} 

// Retrieve the Pulse time from Ultrasonic Sensor
static uint32_t getHCSR04Time(void)
{
    uint32_t pulsetime = 0;

    /* Number of times the interrupt occurred (1 interrupt = 1000 ticks)    */
    pulsetime = SR04IntTimes * TICKPERIOD;

    /* Number of ticks (between 1 to 999) before the interrupt could occur */
    pulsetime += Timer_A_getCounterValue(TIMER_A0_BASE);

    /* Clear Timer */
    Timer_A_clearTimer(TIMER_A0_BASE);

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
    Timer_A_clearTimer(TIMER_A0_BASE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Detects negative-edge */
    while(GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 1);

    /* Stop Timer */
    Timer_A_stopTimer(TIMER_A0_BASE);

    /* Obtain Pulse Width in microseconds */
    pulseDuration = getHCSR04Time();

    /* Calculating distance in cm */
    calculatedDistance = (float)pulseDuration / 58.0f;

    return calculatedDistance;
}

// Display Object Distance Message
float validateObjectMessage(float objectDistance)
{
    char message[100];

    objectDistance = getHCSR04Distance();
    if (objectDistance < 10) {
        //TODO:   Method to call isStop() from Motor Driver
        strcpy(message,"Object Distance reached below min distance! Car stopped moving!");
    }
    else if (objectDistance >= 400) {
        //TODO:   Method to call isStop() from Motor Driver
        strcpy(message,"Object Distance reached below max distance! Car has hit an obstacle and stopped moving!");
    }
    else{
        strcpy(message,"Object Distance is within the appropriate range. Car is moving!");
    }

    printf("Message: %s \n", message);
}

// Print the Object distance
float printobjectDistance(void)
{
    float objectDistance = 0;

    objectDistance = getHCSR04Distance();
    validateObjectMessage(objectDistance);
    printf("Distance from an object is : %.2f cm \n", objectDistance);
}