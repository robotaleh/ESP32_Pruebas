#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <pinout.h>

#define PWM_MOTOR_RIGHT_A 0
#define PWM_MOTOR_RIGHT_B 1
#define PWM_MOTOR_LEFT_A 2
#define PWM_MOTOR_LEFT_B 3
#define PWM_MOTORS_MAX 4095
#define PWM_MOTORS_MIN 0
#define PWM_MOTORS_RESOLUTION 12
#define PWM_MOTORS_HZ 4000

void init_motors();
void set_motors_speed(float velI, float velD);

#endif // MOTORS_H