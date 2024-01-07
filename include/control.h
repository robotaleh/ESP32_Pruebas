#ifndef CONTROL_H
#define CONTROL_H

#include <motors.h>
#include <sensors.h>

#define CONTROL_LOOP_MC 1000

#define BASE_SPEED 35
#define BASE_FAN_SPEED 50

#define PID_KP 0.15
#define PID_KD 0.70

void control_loop(long start_ms);

#endif