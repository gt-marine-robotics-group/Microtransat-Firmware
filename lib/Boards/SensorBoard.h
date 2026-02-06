#pragma once

/**
 * @file SensorBoard.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header (and implementation) for Sensor board.
 *
 * This file controls the logical flow of the board and the 
 * instantiation and function calls of different modules.
 * @see config.h for the hardware definitions like GPIO mapping 
 * and platform.ini for build flag definitions.
 */

 
#ifdef BOARD_BETA

#include "config.h"
#include "MotorController.h"
#include "LEDPIO.h"
#include "Estop.h"
#include "TempSensor.h"
#include "DOFStick.h"
#include "LEDMux.h"

/**
 * @brief 
 * Acts as centralized logical flow for the application.
 * This class is where we actually implement logic and use our modules. 
 * @note This implementation is an alternative to the current  
 * AppCore approach because I find the number of build flags 
 * unsightly.
 * @note Is the equivalent of the main.cpp in most applications, 
 * but is abstracted for modularity and customizability.
 */
class SensorBoard {
public:
    /**
     * @brief Set-up all of our modules and the Serial monitor.
     * @note Initializes all the modules just like setup() in Arduino
     * @todo Maybe consider a name change then lol
     */
    void begin() {
        Serial.begin(115200);
        
        // Only initializes what exists for this specific board
        estop.setup();
        ledPIO.setup();
        tempSensor.setup();
        imu.setup();
    }

    /**
     * @brief Main loop for all of our modules.
     * @note Do all of your logic here just like loop() in Arduino.
     * @todo Okay might actually need to change these names
     */
    void update() {
        // CPU doesn't need to worry about the PIO running in the background
        temp = tempSensor.readData();
        imu.readData();
        Serial.println("\n\n");
        // Serial.println(temp);
        pwm_input = temp;
        
        // Feed the PIO the new blinking value
        ledPIO.updateBlink(pwm_input);
        
        delay(500);
    }

private:
    // These objects are only "born" if the build flag is active
    Estop estop;
    LEDPIO ledPIO;
    uint8_t pwm_input = 25;
    TempSensor tempSensor;
    uint8_t temp = 25;
    DOFStick imu;
};

#endif