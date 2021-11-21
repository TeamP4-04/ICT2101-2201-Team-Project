#ifndef HEADER_ULTRASONIC_H
#define HEADER_ULTRASONIC_H

#define MIN_DISTANCE 15.0f
#define TICKPERIOD 1000

void Initalise_HCSR04(void);
static uint32_t getHCSR04Time(void);
float getHCSR04Distance(void);
float printobjectDistance(void);
float isObjectDetected(float objectDistance);

extern volatile uint32_t SR04IntTimes;
bool stoppedStatus;

#endif /* HEADER_ULTRASONIC_H */