#pragma once

/**
 * @file config.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Definition of Global hardware mapping and configuration constants
 *
 * This file implements the hardware-level interaction with the RP2040.
 * This includes GPIO and other pin selection, clocking rates, etc. 
 * @note Use config:: preceding references to these constants
 * @see Platform.ini for the build flags per board configuation
 */

#include <Arduino.h>

/**
 * @namespace config
 * @brief Contains all hardware-specific constants like pin mappings and bus addresses.
 * @details Centralizing these values allows for easy porting between different board revisions.
 * @todo Consider only keeping pin definitions here and implementing true modularity by encapsulating 
 * object specific features
 */
namespace config {
    // Pinout (Pin Definitions)
    #ifdef HAS_MOTORS
        static constexpr uint8_t AI1 = 15;              ///< GPIO for Motor Direction Encoder 1
        static constexpr uint8_t AI2 = 14;              ///< GPIO for Motor Direction Encoder 1
        static constexpr uint8_t POT_IN = 26;           ///< GPIO for Potentiometer Analog Input
        static constexpr uint8_t PWM_OUT = 18;          ///< GPIO for Motor PWM output

        static constexpr uint8_t MOTOR_1 = 1;
        static constexpr uint8_t MOTOR_2 = 2;
        static constexpr uint8_t MOTOR_3 = 3;
        static constexpr uint8_t MOTOR_4 = 4;
        static constexpr uint8_t MOTOR_5 = 5;
        static constexpr uint8_t MOTOR_6 = 6;
        static constexpr uint8_t MOTOR_7 = 7;
        static constexpr uint8_t MOTOR_8 = 8;

    #endif

    #ifdef HAS_ESTOP
        static constexpr uint8_t ESTOP_PIN = 13;        ///< GPIO for Triggering E-Stop Interrupt
        static constexpr uint8_t ESTOP_LED = 12;        ///< GPIO for Indicating E-Stop Status
    #endif

    #ifdef HAS_INDICATOR_LED
        static constexpr float PIO_CLK = 62500.0f;      ///< Clock divider to set general blink speed 
        static constexpr uint8_t LED_PIN = 16;          ///< GPIO for variable blinking
        static constexpr uint8_t TRIGGER_PIN = 17;      ///< GPIO for pausing variable blinking
    #endif

    #ifdef HAS_LED_MUX
        static constexpr float MUX_PIO_CLK = 62500.0f;  ///< Clock divider to set state machine clocking speed
        static constexpr uint8_t PIN_BASE = 19;          ///< 1st pin of consecutive LED Mux pins - originally 2
        static constexpr uint8_t LED_BUS_SIZE = 4;      ///< Number of consecutive pins for LED Mux
        
        // Am placing the Color definitions here for centralized customizability, but will consider moving back to class for modularity
        enum class Color {                              ///< Normal Enum for use with updateLED()
            Red = 1, 
            Yellow = 2, 
            Green = 3, 
            Blue = 4, 
            Off = 0,
            On = 5
        };   
        // This enum is for setting multiple LEDs (still in development)
        enum Colors : uint8_t {                         ///< Test Enum for use with updateLEDs()
            Red = 1 << 0,                               ///< 0b0001
            Yellow = 1 << 1,                            ///< 0b0010
            Green = 1 << 2,                             ///< 0b0100
            Blue = 1 << 3,                              ///< 0b1000
            On = (1 << 5) - 1,                          ///< 0b1111
            Off = 0                                     ///< 0b0000 (no flag set)
        };  
    #endif

    #ifdef HAS_SENSORS
        static constexpr uint8_t TEMP_SDA = 10;         ///< Sensor I2C SDA pin
        static constexpr uint8_t TEMP_SCL = 11;         ///< Sensor I2C SCL pin
    #endif
}