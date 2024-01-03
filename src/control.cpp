#include <control.h>

static long last_control_loop_mc = 0;
static int position = 0;
static int last_error = 0;

static float calc_correction(int error) {
  float p = PID_KP * error;
  float d = PID_KD * (error - last_error);
  last_error = error;
  return p + d;
}

void control_loop() {
  if (micros() - last_control_loop_mc > CONTROL_LOOP_MC || micros() < last_control_loop_mc) {
    position = get_sensor_position(position);
    int correction = calc_correction(position);
    if (millis() - get_last_line_detected_ms() > 250) {
      set_motors_speed(0, 0);
    } else {
      set_motors_speed(BASE_SPEED + correction, BASE_SPEED - correction);
    }

    last_control_loop_mc = micros();
  }
}