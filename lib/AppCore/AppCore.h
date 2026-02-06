#pragma once

/**
 * @file AppCore.h
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Header (and implementation) for AppCore.
 *
 * This file controls the logical flow of all board possibilities and the 
 * instantiation and function calls of different modules.
 * @see config.h for the hardware definitions like GPIO mapping 
 * and platform.ini for build flag definitions.
 */

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
 * @note Is the equivalent of the main.cpp in most applications, but is abstracted for modularity 
 * and customizability.
 */
class AppCore {
public:
    /**
     * @brief Set-up all of our modules and the Serial monitor.
     * @note Initializes all the modules just like setup() in Arduino
     * @todo Maybe consider a name change then lol
     */
    void begin() {
        Serial.begin(115200);
        
        // Only initializes what exists for this specific board
        #ifdef HAS_ESTOP // Might need to fix this later
            estop.setup();
        #endif

        #ifdef HAS_MOTORS
            motor.setup();
        #endif

        #ifdef HAS_INDICATOR_LED
            ledPIO.setup();
        #endif

        #ifdef HAS_LED_MUX
            ledMux.setup();
        #endif

        #ifdef HAS_SENSORS
            tempSensor.setup();
            imu.setup();
        #endif
    }

    /**
     * @brief Main loop for all of our modules.
     * @note Do all of your logic here just like loop() in Arduino.
     * @todo Okay might actually need to change these names
     */
    void update() {
        // CPU doesn't need to worry about the PIO running in the background
        #ifdef HAS_ESTOP // Might need to fix this later, but I think motors are the only thing E-stopped
            #ifdef HAS_MOTORS // if there is not an EStop consider using #else if (true) {
            if (!Estop::estopTriggered){
                pwm = motor.spinMotor(config::PWM_OUT, analogRead(config::POT_IN));
            } else {
                motor.estop();
            }
            #endif
        #endif

        #ifdef HAS_SENSORS
            temp = tempSensor.readData();
            imu.readData();
            Serial.println("\n\n");
            // Serial.println(temp);
        #endif
        
        // Transfer the sensor or output value to LED blink
        #ifdef HAS_INDICATOR_LED
            #ifdef HAS_MOTORS 
                pwm_input = pwm;
            #endif
            #ifdef HAS_SENSORS      // Check to see if #elifdef is supported
                pwm_input = temp;
            #endif
        #endif

        #ifdef HAS_INDICATOR_LED
            // Feed the PIO the new blinking value
            ledPIO.updateBlink(pwm_input);
        #endif

        #ifdef HAS_LED_MUX
            ledMux.updateLED(color);
            // color = static_cast<config::Color>((static_cast<int>(color) + 1) % (config::LED_BUS_SIZE + 1));
        #endif

        delay(500);
    }

private:
    // These objects are only "born" if the build flag is active
    #ifdef HAS_MOTORS
        MotorController motor; 
        uint16_t pwm;
    #endif

    #ifdef HAS_ESTOP
        Estop estop;
    #endif

    #ifdef HAS_INDICATOR_LED
        LEDPIO ledPIO;
        uint8_t pwm_input = 25;
    #endif

    #ifdef HAS_LED_MUX
        LEDMux ledMux;
        config::Color color = config::Color::Off;
    #endif

    #ifdef HAS_SENSORS
        TempSensor tempSensor;
        uint8_t temp = 25;
        DOFStick imu;
    #endif
};