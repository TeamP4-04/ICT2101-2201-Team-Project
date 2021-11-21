#ifndef HEADER_WHEELENCODER_H
#define HEADER_WHEELENCODER_H

void initWheelEncoder(void);
void PORT2_IRQHandler(void);
void changeMotorSpeed();
float calculateDistanceTravelled();

#endif /* HEADER_WHEELENCODER_H */