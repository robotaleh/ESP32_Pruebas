#include <Arduino.h>

#include <config.h>
#include <pinout.h>
#include <sensors.h>
#include <utils.h>

void setup() {
  init_components();
  calibrate_sensors();
}
int pos = 0;
void loop() {

  for (int sensor = 0; sensor < SENSORS_COUNT; sensor++) {
    Serial.print(get_sensor_calibrated(sensor));
    Serial.print(" ");
  }
  Serial.print(" => ");
  pos = get_sensor_position(pos);
  Serial.print(pos);
  Serial.println();
  delay(100);

  // if (!digitalRead(10)) {

  //   digitalWrite(20, HIGH);
  //   // digitalWrite(7, HIGH);

  //   digitalWrite(6, HIGH);
  //   digitalWrite(21, LOW);
  //   // digitalWrite(8, !digitalRead(10));
  //   // digitalWrite(9, digitalRead(10));
  // } else {
  //   digitalWrite(20, LOW);
  //   digitalWrite(7, LOW);

  //   digitalWrite(6, HIGH);
  //   digitalWrite(21, HIGH);
  //   digitalWrite(8, HIGH);
  //   digitalWrite(9, HIGH);
  // }

  // Serial.print(analogRead(0));
  // Serial.print(" ");
  // Serial.print(analogRead(1));
  // Serial.print(" ");
  // Serial.print(analogRead(2));
  // Serial.print(" ");
  // Serial.print(analogRead(3));
  // Serial.print(" ");
  // Serial.print(analogRead(4));
  // Serial.println();
  // delay(100);

  // digitalWrite(20, digitalRead(10));
  // digitalWrite(21, !digitalRead(10));
}
