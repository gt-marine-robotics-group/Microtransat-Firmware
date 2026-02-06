#pragma once

/**
 * @file Estop.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header (and implementation) for E-Stop.
 *
 * Implementation is just initializing and handling an Interrupt
 * @see config.h for the hardware definitions like GPIO mapping
 */

#include <Arduino.h>
#include "config.h"


/**
 * @brief 
 * This class is the module that represents the E-stop subsystem.
 * @note Only compiled if the HAS_ESTOP flag is defined in the build environment.
 * @note If internal signal, just output to a pin tied to interrupt pin or manually throw flag.
 * @todo This E-Stop is tied to a GPIO pin since that's the easiest way to do it
 * in Arduino and would read a physical E-Stop switch, the next goals are implementing 
 * a watchdog timer for lost connection, and the ultimate goal is register-level interrupt.
 * You can rip the RC/ROS E-stop reading code from the old firmware then.
 */
class Estop{
    public:
        /**
         * @brief Construct a new Estop object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        Estop estop();

        /**
         * @brief Global Estop flag
         */
        static inline volatile bool estopTriggered = false;
        
        /**
         * @brief Estop handler
         * @note Interrupt is attached
         */
        static void handleEstop() {
            Serial.println("E-stop was triggered");
            estopTriggered = true;
            
            digitalWrite(config::ESTOP_LED, HIGH);
        }

        /**
         * @brief Set-up the new Estop object.
         * @note Initializes hardware.
         */
        void setup(){
            // Ensure the pin is configured correctly before attaching the interrupt
            pinMode(config::ESTOP_PIN, INPUT_PULLDOWN); 
            
            // Attach the interrupt to the pin
            // Syntax: attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
            attachInterrupt(digitalPinToInterrupt(config::ESTOP_PIN), handleEstop, FALLING);
            
            pinMode(config::ESTOP_LED, OUTPUT); 
            digitalWrite(config::ESTOP_LED, LOW);

        }

    private:
};