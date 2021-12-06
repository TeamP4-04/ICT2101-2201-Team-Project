#include "header/updateTimer.h"

void initUpdateTimer(){

    const Timer_A_UpModeConfig updateTimerCFG =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            1000,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
    };


    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A3_BASE, &updateTimerCFG);

    /* Enabling interrupts and clearing the timer */
    Interrupt_enableInterrupt(INT_TA3_0);
    Timer_A_clearTimer(TIMER_A3_BASE);

}
