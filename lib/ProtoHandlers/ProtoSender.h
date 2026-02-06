#pragma once

/**
 * @file ProtoSender.h
 * @author Jason Hsiao
 * @date 1/16/2026
 * @version 1.0
 *
 * @brief Header for Handling Protobuf Sender
 *
 * This file allows you to initialize and send messages over Protobuf
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
class ProtoSender{
    public:
        /**
         * @brief Construct a new ProtoSender object.
         * @note Does not initialize hardware. Use setup() for GPIO/PIO setup 
         * to ensure the hardware is ready after the system clock stabilizes.
         */
        ProtoSender();

        /**
         * @brief Set-up the new ProtoSender object.
         * @note Initializes hardware.
         */
        void setup();

        /**
         * @brief Emergency stop for the ProtoSender object.
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
        uint16_t sendData();

        /**
         * @brief Read and print the current sensor data
         * @return the current sensor data (currently just a placeholder)
         * @todo Make a struct for the sensor data or just directly load the protobuf envelope
         * @see included library for information on sensor operation and usage
         */
        void sendStatus(bool estop, bool manual);

    private:
        PacketSerial myPacketSerial;
        
        MyMessage msg;
        operationStatus status;
        positionCommand command;

        uint8_t buffer[128];
        pb_ostream_t stream;
        
};

#endif