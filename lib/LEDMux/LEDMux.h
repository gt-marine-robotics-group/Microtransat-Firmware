#pragma once

/**
 * @file LEDMux.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header for PIO-based LED Multiplexer controller.
 *
 * This file allows you to initialize and manage a PIO State Machine
 * that selectively enables you to turn on individual LEDs on rows
 * of consecutive pins
 * @see config.h for the hardware definitions like GPIO mapping and 
 * tuned clock dividers.
 */

#ifdef HAS_LED_MUX

#include <Arduino.h>
#include "config.h"
#include "led_mux.pio.h"

/**
 * @brief 
 * Acts as a higher-level C++ API for the LED Mux Interface PIO assembly program.
 * This class manages initializing and updating the state machine. 
 * @note Only compiled if the HAS_LED_MUX flag is defined in the build environment.
 */
class LEDMux{
    public:

        /**
         * @brief Construct a new LEDMux object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        LEDMux();
        
        /**
         * @brief Set-up the new LEDMux object.
         * @note Initializes hardware.
         */
        void setup();

        /**
         * @brief Emergency stop for the LEDMux object.
         * @return Whether the e-stop attempt was successful.
         * @note Not implemented due to passive nature of LEDs
         */
        bool estop();

        /**
         * @brief Update the selected pin for the LEDMux object.
         * @param color the new selected color corresponding to a GPIO pin
         * @note State machine will continue to run blinking in the background.
         * @see config.h for definition of the colors under enum Color
         */
        void updateLED(config::Color color);

        /**
         * @brief New method to select multiple pins for the LEDMux object. Intended usage: 
         * 
         * updateLEDs(config::Colors::Red | config::Colors::Green);
         * to set both Red and Green
         * @param colors 8 bit value where the lower values correspond to desired bit mask.
         * @note State machine will continue to run blinking in the background. 
         * @see config.h for the definition of the colors under enum Colors
         * @todo Actually run this and make sure it works, updateLED() is confirmed to work though
         */
        void updateLEDs(uint8_t colors);

        void updateLEDSequence(uint32_t sequence);
        
        private:
            PIO pio;                ///< PIO instance allocated by the driver
            uint sm;                ///< State Machine instance allocated by the driver
        
};

#endif