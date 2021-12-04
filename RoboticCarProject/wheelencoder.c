#include "header/wheelencode.h"
#include "header/UARTusb.h"
volatile char leftval[10];

// Initialize Wheel Encoder
void initWheelEncoder(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig encoderConfig =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            TICKPERIOD,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
    };

    //LEFT WHEEL ENCODER
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN2);
    
    //RIGHT WHEEL ENCODER
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);

    /** Interrupt GPIO Setting **/
    //  Clear and Enable interrupt flag for pin P5.2 + P5.1

    //LEFT WHEEL ENCODER
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN2); 
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN2);
    //RIGHT WHEEL ENCODER
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN1); 
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

    Interrupt_enableInterrupt(INT_PORT5);     // Enable interrupt for Port 2
    Interrupt_enableMaster(); // Enable master interrupt

    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A2_BASE, &encoderConfig);

    /* Enabling interrupts and clearing the timer */
    Interrupt_enableInterrupt(INT_TA2_0);
    Timer_A_clearTimer(TIMER_A2_BASE);

    printf("Wheel Encoder Initialised\n");

}

// Timer interrupt for wheel encoder
void TA2_0_IRQHandler(void)
{
    /* Increment global variable (count number of interrupt occurred) */
    time_counter++;

    //After 1second, see how many notches counted and reset.
    if(time_counter == 1000){

        Timer_A_stopTimer(TIMER_A2_BASE);
        Timer_A_clearTimer(TIMER_A2_BASE);
        timer_status = false;

        int left_notch_per_min = left_notch_counter * MINUTE;
        float left_rotation_per_min = left_notch_per_min / FULL_ROTATE;
        float left_speed = (left_rotation_per_min * WHEEL_DIA) / 100;

        int right_notch_per_min = right_notch_counter * MINUTE;
        float right_rotation_per_min = right_notch_per_min / FULL_ROTATE;
        float right_speed = (right_rotation_per_min * WHEEL_DIA) / 100;

        printf("LEFT WHEEL RPM   : %.1f RPM \n", left_rotation_per_min);
        printf("LEFT WHEEL SPEED : %.1f m/Min \n", left_speed);

        printf("RIGHT WHEEL RPM   : %.1f RPM \n", right_rotation_per_min);
        printf("RIGHT WHEEL SPEED : %.1f m/Min \n", right_speed);
        
        //sending the data to the web portal
        sprintf(leftval, "%.1f", left_rotation_per_min);
        sendBytes(leftval);

//        sprintf(leftval, "%.1f", left_speed);
//        sendBytes(leftval);

        left_notch_counter = 0;
        right_notch_counter = 0;

        time_counter = 0;
    }

    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

/* Interrupt for the wheel encoder */
void PORT5_IRQHandler(void)
{
    // local integer variable
    uint_fast16_t status;

    //Interrupt status for Port 5
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    /*
    Left wheel encoder will be use as MASTER for starting the timer.
    check if timer is started, if not started, start timer and count number of notches for rotation.
    
    Right wheel encoder will be the SLAVE, meaning left wheel start timer, right wheel will also measure 
    the amount of notches made in 1second.
    */

    // LEFT WHEEL ENCODER
    if (status & GPIO_PIN2){
        if(timer_status == false ){
            // Set timer to true, clear Timer and start timer
            timer_status = true;
            Timer_A_clearTimer(TIMER_A2_BASE);
            Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

            /* Increment global variable (count the number of notches on the wheel encoder) */
            left_notch_counter++;

        } else {

            //if timer already started, just count the notches.
            left_notch_counter++;

        }

    }
    // RIGHT WHEEL ENCODER
    if (status & GPIO_PIN1){
        //Right wheel can only start counting when MASTER start counting
        if(timer_status == true ){
            
            right_notch_counter++;

        }
    }
    
    /* Clear interrupt flag for Port 2*/
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
}

