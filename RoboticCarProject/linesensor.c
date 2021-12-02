#include "header/linesensor.h"
#include "header/motordriver.h"
#include "header/util.h"
#include "header/main.h"

void initLineSensor()
{

    // SETTING PINS AS INPUT
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN7); // LEFT LINESENSOR
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN3); // RIGHT LINESENSOR

    printf("Line sensor initialised\n");
}

void trackLine()
{

    /*LINE TRACKER BOTH ON LOW AND TRANSMISSION SHOULD BE AUTO, MOVE FORWARD*/
    if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == 0 &&
        GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3) == 0)
    {

        if (mvtState != FORWARD)
        {
            setCarMvtSate(FORWARD);
        }
    }

    /*LINE TRACKER LEFT HIGH, TURN LEFT*/
    if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == 1 &&
        GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3) == 0)
    {
        if (mvtState != LEFT)
        {
            setCarMvtSate(LEFT);
        }
    }
    /*LINE TRACKER RIGHT HIGH, TURN RIGHT*/
    if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == 0 &&
        GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3) == 1)
    {
        if (mvtState != RIGHT)
        {
            setCarMvtSate(RIGHT);
        }
    }

    /*LINE TRACKER BOTH HIGH, STOP*/
    if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == 1 &&
        GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3) == 1)
    {
        if (mvtState != STOP)
        {
            setCarMvtSate(STOP);
        }
    }
}
