#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <pinout.h>
#include <utils.h>

#define SENSORS_COUNT 5

#define CALIBRATION_MS 3000
#define SENSORS_MAX 4095
#define SENSORS_MIN 0

#define SENSORS_POSITION_MAX 255

void calibrate_sensors();
int get_sensor_raw(int sensor);
int get_sensor_calibrated(int sensor);
int get_sensor_position(int last_position);
long get_last_line_detected_ms();

#endif // SENSORS_H