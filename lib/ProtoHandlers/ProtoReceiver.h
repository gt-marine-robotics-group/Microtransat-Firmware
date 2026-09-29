#pragma once

/**
 * @file ProtoReceiver.h
 * @author Jason Hsiao
 * @date 1/16/2026
 * @version 1.0
 *
 * @brief Header for Handling Protobuf Receiver
 *
 * This file allows you to initialize and receive messages over Protobuf
 * @see config.h for the hardware definitions like GPIO mapping.
 */

#ifdef HAS_PROTO

#include <Arduino.h>
#include "config.h"
#include <Wire.h>

#include <PacketSerial.h>
#include "pb_encode.h"
#include "pb_decode.h"

#include "message.pb.h"

/**
 * @brief 
 * Acts as a wrapper for the SparkFun sensor library.
 * This class manages initializing and updating the sensor object. 
 * @note Only compiled if the HAS_PROT flag is defined in the build environment.
 * Also is tied to the same I2C bus as the DOFStick object.
 */
class ProtoReceiver{
    public:
        /**
         * @brief Construct a new protoReceiver object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        ProtoReceiver();

        /**
         * @brief Set-up the new protoReceiver object.
         * @note Initializes hardware.
         */
        void setup();

        /**
         * @brief Emergency stop for the protoReceiver object.
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
        uint16_t receiveData();

        static void onPacketReceived(const uint8_t* buffer, size_t size);
        
        static int32_t global_position[6];
        static int32_t motor_commands[8];

        static bool newMessage;
    private:
        PacketSerial myPacketSerial;
        // int32_t global_position[6] = {0, 0, 0, 0, 0, 0};
        
};

#endif