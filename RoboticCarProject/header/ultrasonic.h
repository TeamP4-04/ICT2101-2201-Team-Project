#ifndef HEADER_ULTRASONIC_H
#define HEADER_ULTRASONIC_H

#define MIN_DISTANCE    15.0f
#define TICKPERIOD      1000

static void Delay(uint32_t loop);
void Initalise_HCSR04(void);
void TA0_0_IRQHandler(void);
static uint32_t getHCSR04Time(void);
float getHCSR04Distance(void);
float printobjectDistance(void);
float validateObjectMessage(float objectDistance);

#endif /* HEADER_ULTRASONIC_H */