/**
 * @file MotorController.cpp
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Implementation of Motor Controller.
 *
 * This file allows you to initialize and control PWM outputs,
 * essentially acting as a motor controller.
 * 
 * @todo This was designed for the SparkFun H-Bridge Motor Driver, 
 * so this will need to be converted to work with ESCs, but the core 
 * concept of outputting PWMs remains. 
 * @see config.h for the hardware definitions like GPIO mapping
 */

 #ifdef HAS_MOTORS

#include "MotorController.h"

// Constructor
MotorController::MotorController() {
    // Initialize internal variables if needed

}

// TODO: instantiate variable amounts of PWM outputs (defined in config.h)
void MotorController::setup(){
    // pinMode(config::PWM_OUT, OUTPUT);
    // pinMode(config::AI1, OUTPUT);
    // pinMode(config::AI2, OUTPUT);

    motor1.attach(config::MOTOR_1);
    motor2.attach(config::MOTOR_2);
    motor3.attach(config::MOTOR_3);
    motor4.attach(config::MOTOR_4);
    motor5.attach(config::MOTOR_5);
    motor6.attach(config::MOTOR_6);
    motor7.attach(config::MOTOR_7);
    motor8.attach(config::MOTOR_8);
}

bool MotorController::estop(){
    digitalWrite(config::AI1, LOW);
    digitalWrite(config::AI2, LOW);
    analogWrite(config::PWM_OUT, 0);
    return true;
}

// If syntax here looks weird, my bad, I took some code from 4180 and vibed it to work
// Make return a bool or void cuz this was originally supposed to be feedback but not really necessary
uint16_t MotorController::spinMotor(uint8_t pin, int pot) {
    int32_t delta = static_cast<int32_t>(pot) - MotorController::ADC_CENTER;

    // Deadband that way you aren't driving the motors super slow, which isn't great
    if (abs(delta) < MotorController::DEADBAND) {
        digitalWrite(config::AI1, LOW);
        digitalWrite(config::AI2, LOW);
        analogWrite(config::PWM_OUT, 0);
        return 0;
    } else {        
        // Direction
        bool forward = (delta > 0);

        // Scale magnitude, converts difference from the pot center to a reasonable PWM value
        uint8_t pwm = (static_cast<uint32_t>(abs(delta)) * MotorController::PWM_MAX) / MotorController::ADC_CENTER;

        // Safety clamp
        if (pwm > MotorController::PWM_MAX) pwm = MotorController::PWM_MAX;

        // Drive H-bridge
        digitalWrite(config::AI1, forward ? HIGH : LOW);
        digitalWrite(config::AI2, forward ? LOW  : HIGH);
        analogWrite(config::PWM_OUT, pwm);
        return pwm;
    }
    return 0;
}

// TODO: Changes to consider
// Pull the PWMs from a defined list stored in private in this class
// Remove results, I wanted to use it to store returned values, but I don't think that matters here
// Independent dropper/arm control
void MotorController::spinMotors(uint8_t* pins, int* PWMs, uint16_t* results, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        results[i] = spinMotor(pins[i], PWMs[i]);
    }
}

void MotorController::spinMotors(int32_t* motor_commands) {
    motor1.writeMicroseconds(motor_commands[0]);
    motor2.writeMicroseconds(motor_commands[1]);
    motor3.writeMicroseconds(motor_commands[2]);
    motor4.writeMicroseconds(motor_commands[3]);
    motor5.writeMicroseconds(motor_commands[4]);
    motor6.writeMicroseconds(motor_commands[5]);
    motor7.writeMicroseconds(motor_commands[6]);
    motor8.writeMicroseconds(motor_commands[7]);
}

#endif
