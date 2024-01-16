#include <Arduino.h>

#include <config.h>
#include <control.h>
#include <pinout.h>
#include <sensors.h>
#include <utils.h>

bool race_started = false;
long race_started_ms = 0;

void setup() {
  init_components();
  calibrate_sensors();
}

void loop() {
  BTN_STATES btn_state = get_btn_pressed_state();
  while (btn_state == BTN_PRESSING) {
    blink_led(LED_1, 75);
    set_led(LED_2, false);
    btn_state = get_btn_pressed_state();
  }
  if (btn_state == BTN_LONG_PRESSED) {
    race_started = !race_started;
    if (race_started) {
      long starting_ms = millis();
      set_led(LED_1, true);
      set_led(LED_2, true);
      while (millis() - starting_ms < get_ms_start()) {
        if ((starting_ms + get_ms_start()) - millis() <= 1000) {
          set_led(LED_1, false);
          set_led(LED_2, true);
          if (BASE_FAN_SPEED > 0) {
            set_fan_speed(BASE_FAN_SPEED * 0.25);
          }
        } else {
          blink_led(LED_1, 500);
          blink_led(LED_2, 500);
        }
      }
      set_led(LED_1, true);
      set_led(LED_2, false);
      race_started_ms = millis();
    }
  }

  if (race_started && (millis() - race_started_ms) < 10000) {
    blink_led(LED_1, 500);
    blink_led(LED_2, 500);
    control_loop(millis() - race_started_ms);
    // set_fan_speed(100);
    // set_motors_speed(20, 20);
    // if(millis() - race_started_ms < 1000){
    //   set_fan_speed(30);
    // }else{
    //   set_fan_speed(50);
    // }
  } else {
    race_started = false;
    set_fan_speed(0);
    set_motors_speed(0, 0);
    set_led(LED_1, true);
    set_led(LED_2, false);
  }
}
