#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

enum LED(
    LED_1,
    LED_2
)

enum BTN_STATE(
    BTN_PRESS,
    BTN_LONG_PRESS,
)

void set_led(LED led, bool state);


#endif // UTILS_H