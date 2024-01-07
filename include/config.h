#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <pinout.h>
#include <motors.h>

/**
 * @brief Indica el modo de funcionamiento del robot
 *
 */
#define MODE_TEST 1
// #define MODE_RACE 2

/**
 * @brief Tiempo de espera para iniciar carrera después de pulsar el botón
 *
 */
#define MS_START_TEST 10000
#define MS_START_RACE 5000


void init_components();
long get_ms_start();

#endif // CONFIG_H