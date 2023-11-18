#include <sensors.h>

static int sensors_pins[SENSORS_COUNT] = {SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5};
static int sensors_raw[SENSORS_COUNT];
static long sensors_refresh_mc = 0;

static int sensors_max[SENSORS_COUNT] = {SENSORS_MIN, SENSORS_MIN, SENSORS_MIN, SENSORS_MIN, SENSORS_MIN};
static int sensors_min[SENSORS_COUNT] = {SENSORS_MAX, SENSORS_MAX, SENSORS_MAX, SENSORS_MAX, SENSORS_MAX};
static int sensors_umb[SENSORS_COUNT] = {0, 0, 0, 0, 0};

/**
 * @brief Actualiza los valores de los sensores
 *
 */
static void refresh_sensors() {
  if (micros() - sensors_refresh_mc >= 1000 || micros() < sensors_refresh_mc) {
    for (int sensor = 0; sensor < SENSORS_COUNT; sensor++) {
      sensors_raw[sensor] = analogRead(sensors_pins[sensor]);
    }
    sensors_refresh_mc = micros();
  }
}

static void print_calibrations() {
  Serial.println("Calibrations: ");
  for (int sensor = 0; sensor < SENSORS_COUNT; sensor++) {
    Serial.print(sensors_min[sensor]);
    Serial.print(" ");
    Serial.print(sensors_max[sensor]);
    Serial.print(" ");
    Serial.print(sensors_umb[sensor]);
    Serial.print(" ");
  }
  Serial.println();
}

/**
 * @brief Calibra los sensores obteniendo los valores máximos y mínimos para calcular el umbral a partir del cual se considera que un sensor está detectando la línea
 *
 */
void calibrate_sensors() {
  set_led(LED_1, true);
  set_led(LED_2, false);
  while (get_btn_pressed_state() != BTN_LONG_PRESSED) {
    blink_led(LED_2, 350);
  }
  set_led(LED_1, true);
  set_led(LED_2, false);
  int calibration_start_ms = millis();
  do {
    blink_led(LED_1, 50);
    blink_led(LED_2, 100);
    for (int sensor = 0; sensor < SENSORS_COUNT; sensor++) {
      int sensor_value = get_sensor_raw(sensor);
      if (sensor_value > sensors_max[sensor]) {
        sensors_max[sensor] = sensor_value;
      }
      if (sensor_value < sensors_min[sensor]) {
        sensors_min[sensor] = sensor_value;
      }
      sensors_umb[sensor] = sensors_min[sensor] + ((sensors_max[sensor] - sensors_min[sensor]) * 2 / 3);
    }
  } while (millis() - calibration_start_ms < CALIBRATION_MS);
  set_led(LED_1, false);
  set_led(LED_2, false);
  print_calibrations();
}

/**
 * @brief Obtiene el valor sin procesar de un sensor
 *
 * @param sensor Sensor a leer
 * @return int Valor sin procesar del sensor
 */
int get_sensor_raw(int sensor) {
  if (sensor >= 0 && sensor < SENSORS_COUNT) {
    refresh_sensors();
    return sensors_raw[sensor];
  } else {
    return -1;
  }
}

/**
 * @brief Obtiene el valor calibrado de un sensor
 *
 * @param sensor Sensor a leer
 * @return int Valor calibrado del sensor
 */
int get_sensor_calibrated(int sensor) {
  if (sensor >= 0 && sensor < SENSORS_COUNT) {
    refresh_sensors();
    return sensors_raw[sensor] >= sensors_umb[sensor] ? SENSORS_MAX : SENSORS_MIN;
  } else {
    return -1;
  }
}

/**
 * @brief Obtiene la posición del robot en la pista
 *
 * @param last_position Última posición conocida del robot
 * @return int Posición del robot en la pista
 */
int get_sensor_position(int last_position) {
  long sum_sensors_weight = 0;
  long sum_sensors = 0;
  int count_sensors_detecting = 0;
  for (int sensor = 0; sensor < SENSORS_COUNT; sensor++) {
    int sensor_value = get_sensor_calibrated(sensor);
    if (sensor_value >= sensors_umb[sensor]) {
      count_sensors_detecting++;
    }
    sum_sensors_weight += (sensor + 1) * sensor_value * 1000;
    sum_sensors += sensor_value;
  }

  int position_max = ((1000 * (SENSORS_COUNT + 1)) / 2);
  int position = 0;
  if (count_sensors_detecting > 0) {
    position = (sum_sensors_weight / sum_sensors) - position_max;
  } else {
    position = last_position >= 0 ? position_max : -position_max;
  }
  return map(position, -position_max, position_max, -SENSORS_POSITION_MAX, SENSORS_POSITION_MAX);
}
