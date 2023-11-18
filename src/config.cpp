#include <config.h>

/**
 * @brief Inicializa los componentes del robot
 *
 */
void init_components() {
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BTN_1, INPUT_PULLUP);

  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);
  pinMode(SENSOR_5, INPUT);

  pinMode(MOTOR_RIGHT_A, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);
  pinMode(MOTOR_LEFT_A, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  digitalWrite(MOTOR_RIGHT_A, HIGH);
  digitalWrite(MOTOR_RIGHT_B, HIGH);
  digitalWrite(MOTOR_LEFT_A, HIGH);
  digitalWrite(MOTOR_LEFT_B, HIGH);
  init_motors();
}

/**
 * @brief Obtiene el tiempo de espera para iniciar carrera después de pulsar el botón
 *
 * @return long
 */
long get_ms_start() {
#ifdef MODO_RACE
  return MS_START_RACE
#else
  return MS_START_TEST;
#endif
}