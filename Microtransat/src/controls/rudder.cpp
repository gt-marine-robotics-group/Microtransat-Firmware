#include "rudder.h"

#define STEPS_PER_REVOLUTION 200
#define DEGREE_PER_STEP 360.0 / STEPS_PER_REVOLUTION

float rudder_angle_degrees;

void rudder_controller_open() {
    // TODO how should we set initial rudder position on startup?
    stepper_driver_open();
    rudder_angle_degrees = 0;
}

void rudder_controller_close() {
    stepper_driver_close();
}

float rudder_controller_read() {
    return rudder_angle_degrees;
}

void rudder_controller_write(float target_angle_degrees) {
    float delta_angle = rudder_angle_degrees - target_angle_degrees;
    int num_steps = (int) (delta_angle / DEGREE_PER_STEP + 0.5f);
    stepper_driver_write(num_steps);
}

void rudder_controller_update() {
    int prev_steps_to_go = stepper_driver_read();

    if (prev_steps_to_go == 0) {
        return;
    }

    stepper_driver_update();
    rudder_angle_degrees += (stepper_driver_read() - prev_steps_to_go) * STEPS_PER_REVOLUTION;
}
