/**
 * @file ProtoReceiver.cpp
 * @author Jason Hsiao
 * @date 1/16/2025
 * @version 1.0
 *
 * @brief Implementation of Protobuf sender.
 *
 * This file holds the functions for instantiating, setting up, 
 * and sending data over ProtoBuf.
 * 
 * @see config.h for the hardware definitions like GPIO mapping
 */

#ifdef HAS_PROTO

#include "ProtoReceiver.h"

// Constructor
ProtoReceiver::ProtoReceiver() {
    // Initialize internal variables if needed

}

// Initialize the list globally
int32_t ProtoReceiver::global_position[6] = {0, 0, 0, 0, 0, 0};
int32_t ProtoReceiver::motor_commands[8] = {0, 0, 0, 0, 0, 0, 0, 0};

bool ProtoReceiver::newMessage = false;

// This function runs whenever a full COBS packet is received
void ProtoReceiver::onPacketReceived(const uint8_t* buffer, size_t size) {
    Envelope env = Envelope_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(buffer, size);

    if (pb_decode(&stream, Envelope_fields, &env)) {
        // Check if the received envelope contains a position command
        if (env.which_payload == Envelope_pos_tag) {
            global_position[0] = env.payload.pos.roll;
            global_position[1] = env.payload.pos.pitch;
            global_position[2] = env.payload.pos.yaw;
            global_position[3] = env.payload.pos.surge;
            global_position[4] = env.payload.pos.sway;
            global_position[5] = env.payload.pos.heave;
            
            newMessage = true;
            Serial.println("Position updated!");
        }
        if (env.which_payload == Envelope_pos_tag) {
            motor_commands[0] = env.payload.motor_msg.motor1;
            motor_commands[1] = env.payload.motor_msg.motor2;
            motor_commands[2] = env.payload.motor_msg.motor3;
            motor_commands[3] = env.payload.motor_msg.motor4;
            motor_commands[4] = env.payload.motor_msg.motor5;
            motor_commands[5] = env.payload.motor_msg.motor6;
            motor_commands[6] = env.payload.motor_msg.motor7;
            motor_commands[7] = env.payload.motor_msg.motor8;
            newMessage = true;
            Serial.println("Motors updated!");
        }
    }
}

void ProtoReceiver::setup(){
    myPacketSerial.begin(115200);
    // Link the callback function
    myPacketSerial.setPacketHandler(&ProtoReceiver::onPacketReceived);
}

uint16_t ProtoReceiver::receiveData(){
    myPacketSerial.update();
    return 0;
}

#endif