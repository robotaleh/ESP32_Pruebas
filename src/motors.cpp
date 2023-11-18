#include <motors.h>

/**
 * @brief Inicializa el timer controlador de los motores
 *
 */
void init_motors() {
  // Configuración de los canales PWM del Timer
  ledcSetup(PWM_MOTOR_RIGHT_A, PWM_MOTORS_HZ, PWM_MOTORS_RESOLUTION);
  ledcSetup(PWM_MOTOR_RIGHT_B, PWM_MOTORS_HZ, PWM_MOTORS_RESOLUTION);
  ledcSetup(PWM_MOTOR_LEFT_A, PWM_MOTORS_HZ, PWM_MOTORS_RESOLUTION);
  ledcSetup(PWM_MOTOR_LEFT_B, PWM_MOTORS_HZ, PWM_MOTORS_RESOLUTION);

  // Asignación de los pines a los canales PWM
  ledcAttachPin(MOTOR_RIGHT_A, PWM_MOTOR_RIGHT_A);
  ledcAttachPin(MOTOR_RIGHT_B, PWM_MOTOR_RIGHT_B);
  ledcAttachPin(MOTOR_LEFT_A, PWM_MOTOR_LEFT_A);
  ledcAttachPin(MOTOR_LEFT_B, PWM_MOTOR_LEFT_B);

  // Establece el valor inicial de los canales PWM
  ledcWrite(PWM_MOTOR_RIGHT_A, PWM_MOTORS_MAX);
  ledcWrite(PWM_MOTOR_RIGHT_B, PWM_MOTORS_MAX);
  ledcWrite(PWM_MOTOR_LEFT_A, PWM_MOTORS_MAX);
  ledcWrite(PWM_MOTOR_LEFT_B, PWM_MOTORS_MAX);
}

/**
 * @brief Establece la velocidad de los motores
 *
 * @param velI Velocidad del motor izquierdo
 * @param velD Velocidad del motor derecho
 */
void set_motors_speed(float velI, float velD) {
  if (velI > 100) {
    velI = 100;
  } else if (velI < -100) {
    velI = -100;
  }

  if (velI > 0) {
    ledcWrite(PWM_MOTOR_LEFT_A, PWM_MOTORS_MAX);
    ledcWrite(PWM_MOTOR_LEFT_B, PWM_MOTORS_MAX - (PWM_MOTORS_MAX * velI / 100));
  } else {
    ledcWrite(PWM_MOTOR_LEFT_A, PWM_MOTORS_MAX - (PWM_MOTORS_MAX * abs(velI) / 100));
    ledcWrite(PWM_MOTOR_LEFT_B, PWM_MOTORS_MAX);
  }

  if (velD > 100) {
    velD = 100;
  } else if (velD < -100) {
    velD = -100;
  }

  if (velD > 0) {
    ledcWrite(PWM_MOTOR_RIGHT_A, PWM_MOTORS_MAX - (PWM_MOTORS_MAX * velD / 100));
    ledcWrite(PWM_MOTOR_RIGHT_B, PWM_MOTORS_MAX);
  } else {
    ledcWrite(PWM_MOTOR_RIGHT_A, PWM_MOTORS_MAX);
    ledcWrite(PWM_MOTOR_RIGHT_B, PWM_MOTORS_MAX - (PWM_MOTORS_MAX * abs(velD) / 100));
  }
}

/*
void set_speed(int velI, int velD) {
  if (velD > 100) {
    velD = 100;
  } else if (velD < -100) {
    velD = -100;
  }
  if (velI > 100) {
    velI = 100;
  } else if (velI < -100) {
    velI = -100;
  }

  if (velI >= 0) {
    analogWrite(MOTOR_DER_A, MAX_PWM - MAX_PWM * velI / 100);
    analogWrite(MOTOR_DER_B, MAX_PWM);
  } else {
    analogWrite(MOTOR_DER_A, MAX_PWM);
    analogWrite(MOTOR_DER_B, MAX_PWM - MAX_PWM * abs(velI) / 100);
  }

  if (velD >= 0) {
    analogWrite(MOTOR_IZQ_A, MAX_PWM - MAX_PWM * velD / 100);
    analogWrite(MOTOR_IZQ_B, MAX_PWM);
  } else {
    analogWrite(MOTOR_IZQ_A, MAX_PWM);
    analogWrite(MOTOR_IZQ_B, MAX_PWM - MAX_PWM * abs(velD) / 100);
  }
}


*/