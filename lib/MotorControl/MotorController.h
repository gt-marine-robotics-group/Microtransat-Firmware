#pragma once

/**
 * @file MotorController.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header for Motor Controller.
 *
 * This file allows you to initialize and control PWM outputs,
 * essentially acting as a motor controller.
 * @see config.h for the hardware definitions like GPIO mapping
 */

#ifdef HAS_MOTORS

#include <Arduino.h>
#include <Servo.h>
#include "config.h"

/**
 * @brief Controls the physical H-Bridge hardware.
 * * This class manages PWM generation and direction pins. It is only
 * compiled if the HAS_MOTORS flag is defined in the build environment.
 */
class MotorController{
    public:
        /**
         * @brief Construct a new MotorController object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        MotorController();

        /**
         * @brief Set-up the new MotorController object.
         * @note Initializes hardware.
         * @see config.h for the GPIO mapping.
         */
        void setup();

        /**
         * @brief Emergency stop for the MotorController object. 
         * Turns off all the motors
         * @return Whether the e-stop attempt was successful.
         */
        bool estop();

        /**
         * @brief Sets the motor speed and direction.
         * @param PWM The PWM duty cycle (0-255).
         * @param pin GPIO pin you desire to write to
         * @return The actual PWM value applied after safety clamping.
         */
        uint16_t spinMotor(uint8_t pin, int PWM);

        /**
         * @brief New method to set multiple motor speeds
         * @param PWMs The PWM duty cycles for each motor (0-255).
         * @param pins GPIO pins you desire to write to
         * @param results Returned values from each spinMotors() call
         * @param count Number of motors you wish to run
         * @see config.h for the definition of the actual pins to use
         * @todo Actually implement this for our use case, currently just runs spinMotors() a bunch. 
         * Also not really tested that effectively (I only have 2 motors and even less wires)
         */
        void spinMotors(uint8_t* pins, int* PWMs, uint16_t* results, uint8_t count);
        void spinMotors(int32_t* motor_commands);
        
    private:
        // Alternatively consider putting these in config.h for more centralization but I prefer modularity
        static constexpr int ADC_MAX    = 1023;     ///< The max value of the ADC for reading throttle
        static constexpr int ADC_CENTER = 512;      ///< The middle value of the ADC for flipping direction
        static constexpr int PWM_MAX    = 255;      ///< Max value of a PWM, low-key this should be a global constant but idk where to put this
        static constexpr int DEADBAND   = 50;       ///< Don't operate the motor at too low of a PWM, adjust to remove jitter

        Servo motor1;
        Servo motor2;
        Servo motor3;
        Servo motor4;
        Servo motor5;
        Servo motor6;
        Servo motor7;
        Servo motor8;
};

#endif