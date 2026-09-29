#pragma once

/**
 * @file PrestoBoard.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header (and implementation) for Presto board.
 *
 * This file controls the logical flow of the board and the 
 * instantiation and function calls of different modules.
 * @note This implementation is an alternative to the current  
 * AppCore approach because I find the number of build flags 
 * unsightly.
 * @see config.h for the hardware definitions like GPIO mapping 
 * and platform.ini for build flag definitions.
 */

#ifdef BOARD_ALPHA

#include "config.h"
#include "MotorController.h"
#include "LEDPIO.h"
#include "Estop.h"
#include "TempSensor.h"
#include "DOFStick.h"
#include "LEDMux.h"

/**
 * @brief 
 * Acts as centralized logical flow for the PrestoBoard specifically.
 * This class is where we actually implement logic and use our modules. 
 * @note Is the equivalent of the main.cpp in most applications, but is abstracted for modularity 
 * and customizability.
 */
class PrestoBoard {
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
    
        motor.setup();
    
        ledPIO.setup();
    
        ledMux.setup();
        
    }

    /**
     * @brief Main loop for all of our modules.
     * @note Do all of your logic here just like loop() in Arduino.
     * @todo Okay might actually need to change these names
     */
    void update() {
        // CPU doesn't need to worry about the PIO running in the background
        if (!Estop::estopTriggered){
            pwm = motor.spinMotor(config::PWM_OUT, analogRead(config::POT_IN));
        } else {
            motor.estop();
        }
        
        // Transfer the sensor or output value to LED blink
        pwm_input = pwm;
        
        // Feed the PIO the new blinking value
        ledPIO.updateBlink(pwm_input);
        ledMux.updateLED(color);
        ledMux.updateLED(config::Color::Blue);
        delay(500);
        ledMux.updateLED(config::Color::Green);
        delay(500);
        ledMux.updateLED(config::Color::Yellow);
        delay(500);
        ledMux.updateLED(config::Color::Red);
        delay(500);
        ledMux.updateLED(config::Color::Off);
        delay(500);
        ledMux.updateLED(config::Color::On);
        // color = static_cast<config::Color>((static_cast<int>(color) + 1) % (config::LED_BUS_SIZE + 1));
    
        delay(500);
    }

private:
    // Unlike AppCore's approach, we assume these objects exist due the platform.ini definitions
    MotorController motor; 
    uint16_t pwm;

    Estop estop;

    LEDPIO ledPIO;
    uint8_t pwm_input = 25;

    LEDMux ledMux;
    config::Color color = config::Color::Off;


};

#endif