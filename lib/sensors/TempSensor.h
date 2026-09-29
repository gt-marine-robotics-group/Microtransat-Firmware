#pragma once

/**
 * @file TempSensor.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header for Temperature and Humidity sensor.
 *
 * This file allows you to initialize and manage a temperature  
 * and humidity sensor breakout board via I2C.
 * @see config.h for the hardware definitions like GPIO mapping.
 */

#ifdef HAS_SENSORS

#include <Arduino.h>
#include "config.h"
#include <Wire.h>
#include "SparkFun_Si7021_Breakout_Library.h"

/**
 * @brief 
 * Acts as a wrapper for the SparkFun sensor library.
 * This class manages initializing and updating the sensor object. 
 * @note Only compiled if the HAS_SENSORS flag is defined in the build environment.
 * Also is tied to the same I2C bus as the DOFStick object.
 */
class TempSensor{
    public:
        /**
         * @brief Construct a new TempSensor object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        TempSensor();

        /**
         * @brief Set-up the new TempSensor object.
         * @note Initializes hardware.
         */
        void setup();

        /**
         * @brief Emergency stop for the TempSensor object.
         * @return Whether the e-stop attempt was successful.
         * @note Not implemented due to passive nature of sensors
         */
        bool estop();
        
        /**
         * @brief Read and print the current sensor data
         * @return the current sensor data (currently just a placeholder)
         * @todo Make a struct for the sensor data or just directly load the protobuf envelope
         * @see included library for information on sensor operation and usage
         */
        uint16_t readData();

    private:
        /// Si7021 sensor object, created here so no other class can mess with it (OOP concept)
        SI7021 sensor;
        
};

#endif