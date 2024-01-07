#include <control.h>

static long last_control_loop_mc = 0;
static int position = 0;
static int last_error = 0;

static int speed = 0;

static float calc_correction(int error) {
  float p = PID_KP * error;
  float d = PID_KD * (error - last_error);
  last_error = error;
  return p + d;
}

void control_loop(long run_ms) {
  if (micros() - last_control_loop_mc > CONTROL_LOOP_MC || micros() < last_control_loop_mc) {
    position = get_sensor_position(position);
    int correction = calc_correction(position);
    if (millis() - get_last_line_detected_ms() > 250) {
      set_motors_speed(0, 0);
      set_fan_speed(0);
    }
    // if (correction >= 0) {
    //   set_motors_speed(BASE_SPEED, BASE_SPEED - correction);
    // } else {
    //   set_motors_speed(BASE_SPEED + correction, BASE_SPEED);
    // }

    speed = 60.0f * (run_ms / 1000.0f);
    if (speed > BASE_SPEED) {
      speed = BASE_SPEED;
    }
    // Serial.println(speed);

    set_motors_speed(speed + correction, speed - correction);
    // set_fan_speed(BASE_FAN_SPEED);

    last_control_loop_mc = micros();
  }
}