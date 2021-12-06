# Overview
This guide provdies an overview on how to wire your robotic car to successfully work with web application

## Requirements
___
- MSP432 Microcontroller
- Ultrasonic sensor HSC04
- 2x Wheel Encoder
- MH-Sensor Series (IR sensor)
- Batteries 4x AA or 1x 9V
- DC Motors and motor driver
- 2M or longer MicroUSB cable

## Specifications
___
**Motor Driver:**
- ENA : P2.4 R 
- ENB : P5.6 L
- IN 1 : P4.1 R
- IN 2 : P4.2 R
- IN 3 : P4.3 L
- IN 4 : P4.4 L
- GROUND : GND

**Ultra Sonic Sensor**
- GROUND : GND
- ECHO : P3.7
- TRIGGER : P3.6
- VCC : 3.3V

**LEFT Wheel encoder**
- OUT : P5.2
- VCC :  3.3V
- GND :  GND 

**RIGHT WHEEL ENCODER**
- OUT : P5.1
- VCC : 3.3V
- GND : GND

**RIGHT LINE SENSOR**
- D0 : P2.3
- GND : GND
- VCC : 3.3V

**LEFT LINE SENSOR**
- D0 : P2.7
- GND : GND
- VCC : 3.3V