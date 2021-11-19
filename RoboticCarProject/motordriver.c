#include "motordriver.h"

/*PWM TIMER CONFIG
 *
 * Duty cycle calculation:
 *
 * dutycycle = pulse-width / total period of signal
 *
 * Max dutyCycle = 9000
 *
 *
 * */


Timer_A_PWMConfig pwmConfigLeft =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_24,
        10000,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        1000
};

Timer_A_PWMConfig pwmConfigRight =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_24,
        10000,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        1000
};

/*To include utility delay function*/
static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0 ; i < loop ; i++);
}


void initMotorDriver(){

    /*
    PIN Settings for Motor Driver Movement
    LeftMotor: ENA, IN1, IN2
    RightMotor: ENB, IN3, IN4
    Input: IN1/3 , IN2/4
    Input: 0,0 [Stopped]
    Input: 1,0 [Forward]
    Input: 0,1 [Backward]
    Input: 1,1 [Stopped]
    */

    /*Left Motor GPIO */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1); //IN1
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2); //IN2
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);

    /*Right Motor GPIO */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3); //IN3
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4); //IN4
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);

    /*Setting PWM port */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); //Left Motor[ENA]
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); //Right Motor[ENB]

    /* Configuring Timer_A to have a period of approximately 80ms and an initial duty cycle of 10% of that (1000 ticks)  */
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRight); //Right Motor

    printf("Init-ed the motor\n");

};

void turnLeft(){
/*Left slow, Right fast*/

    //Set Left motor to move backward at 50%.
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigLeft.dutyCycle = 4500;

    //Set Right motor to move forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigRight.dutyCycle = 4500;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRight); //Right Motor

    printf("Turning Left\n");

};

void turnRight(){
/*Left fast, Right fast*/

    //Set Left motor to forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigLeft.dutyCycle = 4500;

    //Set Right motor to move forward at 50%.
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigRight.dutyCycle = 4500;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRight); //Right Motor

    printf("Turning Right\n");


};

void goForward(){
/* Both PWM at 50% */

    //Set Left motor to forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigLeft.dutyCycle = 4500;

    //Set Right motor to move forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigRight.dutyCycle = 4500;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRight); //Right Motor

    printf("Moving Forward\n");

};

void isStop(){
/*Turn all GPIO to Low */

    //brake left motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigLeft.dutyCycle = 0;

    //brake right motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigLeft.dutyCycle = 0;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRight); //Right Motor

    printf("Is stopped\n");
};

/* working tested code for interrupt
 *
 * int stateCounter = 0;
 *
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    printf("StateCounter before Increment %d\n", stateCounter);
    if (status & GPIO_PIN1)
    {

        stateCounter += 1;


        if (stateCounter == 1) {
            goForward();
        }
        else if (stateCounter == 2) {
            turnLeft();
        }
        else if (stateCounter == 3) {
            turnRight();
        }
        else {
            isStop();
            stateCounter = 0;
        }

    }
    printf("StateCounter after increment %d\n", stateCounter);

    Delay(150000);
}

*/
