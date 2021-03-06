#include "header/motordriver.h"

Timer_A_PWMConfig pwmConfigLeft =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_24,
        10000,
        TIMER_A_CAPTURECOMPARE_REGISTER_2,
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

    /*Right Motor GPIO */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1); //IN1
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2); //IN2
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);

    /*Left Motor GPIO */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3); //IN3
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4); //IN4
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);

    /*Setting PWM port */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); //Right Motor[ENA]
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); //Left Motor[ENB]

    /* Configuring Timer_A to have a period of approximately 80ms and an initial duty cycle of 10% of that (1000 ticks)  */
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor


    printf("Motordriver initialised\n");

};

void goForward(){
/* Both PWM at 50% */

    //Set right motor to forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    //pwmConfigRight.dutyCycle = 1100 * 2.2;
    pwmConfigRight.dutyCycle = 3500 * 2.2;

    //Set left motor to move forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    //pwmConfigLeft.dutyCycle = 1300 * 2.2;
    pwmConfigLeft.dutyCycle = 3600 * 2.2;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor

};

void turnLeft(){
/*Left slow, Right fast*/

    //Set Right motor to move forward
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigRight.dutyCycle = 2600 * 1.7;

    //Set Left motor to move backward
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigLeft.dutyCycle = 0;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor

};

void turnRight(){
/*Left fast, Right slow*/

    //Set Left motor to forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigRight.dutyCycle = 0;

    //Set Right motor to move forward at 50%.
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigLeft.dutyCycle = 2600 * 1.7;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor

};

void isStop(){
/*Turn all GPIO to Low */

    //brake right motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigRight.dutyCycle = 0;

    //brake left motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigLeft.dutyCycle = 0;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor

};

void isReverse(){
/*Turn all GPIO to Low */

    //brake right motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
    pwmConfigRight.dutyCycle = 3500 * 2.2;;

    //brake left motor and set 0%
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
    pwmConfigLeft.dutyCycle = 3400 * 2.2;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight); //Right Motor
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft); //Left Motor

};
