#include "stepper_driver.h"

#include <AccelStepper.h>

#define MOTOR_INTERFACE_TYPE 1

#define STEPPER_INITIAL_SPEED 500
#define STEPPER_MAX_SPEED 1000
#define STEPPER_ACCELERATION 500


AccelStepper stepper_motor(MOTOR_INTERFACE_TYPE, RUDDER_STEP_PIN, RUDDER_DIR_PIN);


void stepper_driver_open() {
    stepper_motor.setMaxSpeed(STEPPER_MAX_SPEED);
    stepper_motor.setAcceleration(STEPPER_ACCELERATION);

    stepper_motor.setSpeed(STEPPER_INITIAL_SPEED);
}

void stepper_driver_close() { }

int stepper_driver_read() {
    return stepper_motor.distanceToGo();
}

void stepper_driver_write(int num_steps) {
    stepper_motor.moveTo(num_steps);
}

void stepper_driver_update() {
    if (stepper_motor.distanceToGo() != 0) {
        stepper_motor.run();
    }
}
