#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Indica el modo de funcionamiento del robot
 *
 */
#define MODO_TEST 1
// #define MODO_RACE 2

/**
 * @brief Tiempo de espera para iniciar carrera después de pulsar el botón
 *
 */
#define MS_INICIO_TEST 3000
#define MS_INICIO_RACE 5000

#include <Arduino.h>
#include <pinout.h>

void init_components();
long get_ms_inicio();

#endif // CONFIG_H