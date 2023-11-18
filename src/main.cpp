#include <Arduino.h>

#include <config.h>
#include <pinout.h>

void setup() {
  init_components();
}

void loop() {
  if (!digitalRead(10)) {

    digitalWrite(20, HIGH);
    // digitalWrite(7, HIGH);

    digitalWrite(6, HIGH);
    digitalWrite(21, LOW);
    // digitalWrite(8, !digitalRead(10));
    // digitalWrite(9, digitalRead(10));
  } else {
    digitalWrite(20, LOW);
    digitalWrite(7, LOW);

    digitalWrite(6, HIGH);
    digitalWrite(21, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }

  Serial.print(analogRead(0));
  Serial.print(" ");
  Serial.print(analogRead(1));
  Serial.print(" ");
  Serial.print(analogRead(2));
  Serial.print(" ");
  Serial.print(analogRead(3));
  Serial.print(" ");
  Serial.print(analogRead(4));
  Serial.println();
  delay(100);

  // digitalWrite(20, digitalRead(10));
  // digitalWrite(21, !digitalRead(10));
}