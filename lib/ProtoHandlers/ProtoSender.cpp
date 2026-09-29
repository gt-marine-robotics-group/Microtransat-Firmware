/**
 * @file ProtoSender.cpp
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

#include "protoSender.h"

// Constructor
ProtoSender::ProtoSender() {
    // Initialize internal variables if needed

}

void ProtoSender::setup(){
    myPacketSerial.begin(115200);

    msg = MyMessage_init_zero;
    status = operationStatus_init_zero;


    // Create a stream that writes to our buffer
    stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
}

uint16_t ProtoSender::sendData(){
    msg.id = 42;
    strcpy(msg.content, "Hello World");

    // Encode the message
    if (!pb_encode(&stream, MyMessage_fields, &msg)) {
        // Handle error
        // Serial.println("Failed to encode!!");
    }
    myPacketSerial.send(buffer, stream.bytes_written);

    status.estop = !status.estop;
    pb_encode(&stream, operationStatus_fields, &status);
    command.roll = 25;
    pb_encode(&stream, positionCommand_fields, &command);
    myPacketSerial.send(buffer, stream.bytes_written);

    return 0;
}

void ProtoSender::sendStatus(bool estop, bool manual) {
    uint8_t buffer[128];
    Envelope env = Envelope_init_zero;
    
    // Set the tag so the receiver knows which one it is
    env.which_payload = Envelope_status_tag;
    env.payload.status.estop = estop;
    env.payload.status.manual = manual;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (pb_encode(&stream, Envelope_fields, &env)) {
        myPacketSerial.send(buffer, stream.bytes_written);
    }
}

#endif