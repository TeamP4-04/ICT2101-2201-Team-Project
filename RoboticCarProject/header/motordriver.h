#ifndef HEADER_MOTORDRIVER
#define HEADER_MOTORDRIVER

void initMotorDriver(void);
void turnLeft(void);
void turnRight(void);
void goForward(void);
void isStop(void);

Timer_A_PWMConfig pwmConfigLeft();
Timer_A_PWMConfig pwmConfigRight();

#endif