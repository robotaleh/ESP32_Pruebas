#ifndef CONTROL_H
#define CONTROL_H

#include <motors.h>
#include <sensors.h>

#define CONTROL_LOOP_MC 1000

#define BASE_SPEED 20

#define PID_KP 0.08
#define PID_KD 0.45

void control_loop();

#endif