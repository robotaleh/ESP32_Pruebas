#include <utils.h>

static bool toggle_led_state[2] = {false, false};
static int blink_led_ms[2] = {0, 0};

static int btn_pressed_ms = 0;
static int btn_last_pressed_ms = 0;

/**
 * @brief Establece el estado de un LED
 *
 * @param led LED a modificar
 * @param state Estado del LED
 */
void set_led(int led, bool state) {
  digitalWrite(led, state);
  switch (led) {
    case LED_1:
      toggle_led_state[0] = state;
      blink_led_ms[0] = millis();
      break;
    case LED_2:
      toggle_led_state[1] = state;
      blink_led_ms[1] = millis();
      break;
  }
}

/**
 * @brief Parpadea un LED a una frecuencia determinada
 *
 * @param led LED a parpadear
 * @param ms Frecuencia de parpadeo
 */
void blink_led(int led, int ms) {
  switch (led) {
    case LED_1:
      if (millis() - blink_led_ms[0] >= ms) {
        set_led(led, !toggle_led_state[0]);
      }
      break;
    case LED_2:
      if (millis() - blink_led_ms[1] >= ms) {
        set_led(led, !toggle_led_state[1]);
      }
      break;
  }
}

/**
 * @brief Obtiene el estado del botón pulsado
 *
 * @return enum BTN_STATES
 */
enum BTN_STATES get_btn_pressed_state() {
  if (millis() - btn_last_pressed_ms < 50) {
    return BTN_RELEASED;
  }
  if (digitalRead(BTN_1)) {
    // Serial.print("RELEASE ");
    // Serial.println(btn_pressed_ms);
    if (btn_pressed_ms == 0) {
      return BTN_RELEASED;
    } else {
      if (millis() - btn_pressed_ms >= 250) {
        btn_pressed_ms = 0;
        btn_last_pressed_ms = millis();
        return BTN_LONG_PRESSED;
      } else if (millis() - btn_pressed_ms <= 250) {
        btn_pressed_ms = 0;
        if (millis() - btn_pressed_ms < 25) {
          return BTN_RELEASED;
        } else {
          btn_last_pressed_ms = millis();
          return BTN_PRESSED;
        }
      } else {
        return BTN_RELEASED;
      }
    }
  } else {
    // Serial.println("PRESSING");
    if (btn_pressed_ms == 0) {
      btn_pressed_ms = millis();
    }
    return BTN_PRESSING;
  }
}