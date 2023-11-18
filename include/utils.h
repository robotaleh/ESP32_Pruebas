#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <pinout.h>

void set_led(int led, bool state);
void blink_led(int led, int ms);

enum BTN_STATES {
  BTN_RELEASED,
  BTN_PRESSED,
  BTN_LONG_PRESSED,
};

enum BTN_STATES get_btn_pressed_state();

#endif // UTILS_H