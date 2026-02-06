#pragma once

/**
 * @file LEDPIO.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header for PIO-based variable blinking controller.
 *
 * This file allows you to initialize and manage a PIO State Machine
 * that controls variable blinking on a GPIO pin
 * @see config.h for the hardware definitions like GPIO mapping and 
 * tuned clock dividers.
 */

#ifdef HAS_INDICATOR_LED

#include <Arduino.h>
#include "config.h"
#include "blink_input.pio.h"

/**
 * @brief 
 * Acts as a higher-level C++ API for the Variable Blinking PIO assembly program.
 * This class manages initializing and updating the state machine. 
 * @note Only compiled if the HAS_INDICATOR_LED flag is defined in the build environment.
 */
class LEDPIO{
    public:

        /**
         * @brief Construct a new LEDPIO object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        LEDPIO();

        /**
         * @brief Set-up the new LEDPIO object.
         * @note Initializes hardware.
         */
        void setup();

        /**
         * @brief Emergency stop for the LEDPIO object.
         * @return Whether the e-stop attempt was successful.
         * @note Not implemented due to passive nature of LEDs
         */
        bool estop();

        /**
         * @brief Update the blinking rate for the LEDPIO object.
         * @param pio_delay the new delay value for the variable blinking
         * @note State machine will continue to run blinking in the background.
         */
        void updateBlink(uint8_t pio_delay);

    private:
        uint sm;                        ///< The assigned PIO State Machine index
        uint32_t last_pio_delay = 0;    ///< Cache of the last delay value sent to FIFO
};

#endif