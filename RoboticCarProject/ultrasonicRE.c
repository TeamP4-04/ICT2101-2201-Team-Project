#include "myLib.h"
#include "ultrasonicRE.h"

//Initialise Sensor
void initUltraSonic(uint32_t loop){
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

    int a = CS_getSMCLK(); //what is cd_getclock for?

    /* Configuring P3.6 as Output(triggers the pulse)*/
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);    // Trigger Pin (P3.6) (trigger pulse)
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P3, GPIO_PIN7); // Echo Pin (P3.7) (recieve the pulse)

    /*setting sensor to dont send any pulse yet*/
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6); //Low means dont send, High is send pulse.

    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A0_BASE, &sonicConfig);

    /* Enabling interrupts and clearing the timer */
    Interrupt_enableInterrupt(INT_TA0_0);
    Timer_A_clearTimer(TIMER_A0_BASE);

};

// Retrieve the Pulse time from Ultrasonic Sensor
static uint32_t getUltraSonicTime(void)
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