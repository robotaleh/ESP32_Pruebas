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

  pinMode(MOTOR_DER_A, OUTPUT);
  pinMode(MOTOR_DER_B, OUTPUT);
  pinMode(MOTOR_IZQ_A, OUTPUT);
  pinMode(MOTOR_DER_B, OUTPUT);
  digitalWrite(MOTOR_DER_A, HIGH);
  digitalWrite(MOTOR_DER_B, HIGH);
  digitalWrite(MOTOR_IZQ_A, HIGH);
  digitalWrite(MOTOR_DER_B, HIGH);
}

/**
 * @brief Obtiene el tiempo de espera para iniciar carrera después de pulsar el botón
 *
 * @return long
 */
long get_ms_inicio() {
#ifdef MODO_RACE
  return MS_INICIO_RACE
#else
  return MS_INICIO_TEST;
#endif
}