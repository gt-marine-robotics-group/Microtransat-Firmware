#pragma once

/**
 * @file PrestoJrBoard.h
 * @author Jason Hsiao
 * @date 1/17/2025
 * @version 1.0
 *
 * @brief Header (and implementation) for Presto Jr board.
 *
 * This file controls the logical flow of the board and the 
 * instantiation and function calls of different modules.
 * @note This implementation is an alternative to the current  
 * AppCore approach because I find the number of build flags 
 * unsightly.
 * @see config.h for the hardware definitions like GPIO mapping 
 * and platform.ini for build flag definitions.
 */

#ifdef BOARD_GAMMA

#include "config.h"
#include "ProtoSender.h"
#include "ProtoReceiver.h"
#include "LEDMux.h"

/**
 * @brief 
 * Acts as centralized logical flow for the PrestoJrBoard specifically.
 * This class is where we actually implement logic and use our modules. 
 * @note Is the equivalent of the main.cpp in most applications, but is abstracted for modularity 
 * and customizability.
 */
class PrestoJrBoard {
public:
    /**
     * @brief Set-up all of our modules and the Serial monitor.
     * @note Initializes all the modules just like setup() in Arduino
     * @todo Maybe consider a name change then lol
     */
    void begin() {
        Serial.begin(115200);
        // Only initializes what exists for this specific board
        protoSender.setup();        // Check if these are blocking because the code doesn't start until it connects
        protoReceiver.setup();      // Not that that is a bad thing
        motorController.setup();
        // ledMux.setup();

        // uint32_t seq = (0b1000 << 4) + (0b0100);
        // ledMux.updateLEDSequence(seq);
        pinMode(16, INPUT_PULLDOWN);
        
    }

    /**
     * @brief Main loop for all of our modules.
     * @note Do all of your logic here just like loop() in Arduino.
     * @todo Okay might actually need to change these names
     */
    void update() {
        // CPU doesn't need to worry about the PIO running in the background
        // // protoSender.sendData();
        // protoSender.sendStatus(true, false);        
        // delay(1000);
        // protoSender.sendStatus(false, true);
        // delay(1000);
        protoReceiver.receiveData();
        // if (ProtoReceiver::newMessage){
        //     digitalWrite(16, HIGH);
        //     // if (ProtoReceiver::global_position[0]){
        //     //     ledMux.updateLEDs(config::Colors::Blue | config::Colors::Green);
        //     // }
        //     // delay(500);
        //     // // if (ProtoReceiver::global_position[0]){
        //     // //     ledMux.updateLED(config::Color::Blue);
        //     // // }
        //     // // delay(500);
        //     uint32_t sequence = 0;
        //     if (ProtoReceiver::global_position[0]){
        //         sequence |= config::Colors::Blue << (4 * 0);
        //     }
        //     if (ProtoReceiver::global_position[1]){
        //         sequence |= config::Colors::Green << (4 * 1);
        //     }
        //     if (ProtoReceiver::global_position[2]){
        //         sequence |= config::Colors::Yellow << (4 * 2);
        //     }
        //     if (ProtoReceiver::global_position[3]){
        //         sequence |= config::Colors::Red << (4 * 3);
        //     }
        //     if (ProtoReceiver::global_position[4]){
        //         sequence |= config::Colors::Off << (4 * 4); // Setting only off doesn't work because it will assume null sequence, maybe have invisible 5th pin
        //                                                     // Only works to stop the blinking for individual LEDs
        //     }
        //     if (ProtoReceiver::global_position[5]){
        //         sequence |= config::Colors::On << (4 * 5);  // For some reason Red stays on a beat longer
        //     }
        //     ProtoReceiver::newMessage = false;
        //     ledMux.updateLEDSequence(sequence);
        //     delay(500);
        //     digitalWrite(16, LOW);
        // }
        if (ProtoReceiver::newMessage){
            digitalWrite(16, HIGH);
            motorController.spinMotors(ProtoReceiver::motor_commands);
            delay(1000);
            
            digitalWrite(16, LOW);
        }
        // int32_t motors[8] = {255, 255, 255, 255, 0, 0, 0, 0};
        // motorController.spinMotors(motors);
        delay(100);

    }

private:
    // Unlike AppCore's approach, we assume these objects exist due the platform.ini definitions
    ProtoSender protoSender;
    ProtoReceiver protoReceiver;
    MotorController motorController;
    // LEDMux ledMux;
    // config::Color color = config::Color::Off;
};

#endif