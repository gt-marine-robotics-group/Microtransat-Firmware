import serial
from cobs import cobs
import message_pb2
import sys

# Setup Serial - Replace 'COM4' with your actual port
try:
    ser = serial.Serial('COM7', 115200, timeout=1)
except Exception as e:
    print(f"Error opening port: {e}")
    sys.exit(1)

raw_buffer = bytearray()
print("Listening for Protobuf Envelopes (COBS)...")

while True:
    char = ser.read(1)
    if not char: continue
    
    if char == b'\x00':  # End of COBS frame
        if raw_buffer:
            try:
                # 1. COBS Decode
                decoded = cobs.decode(raw_buffer)
                
                # 2. Parse as the Top-Level Envelope
                envelope = message_pb2.Envelope()
                envelope.ParseFromString(decoded)
                
                # 3. Determine message type using 'WhichOneof'
                msg_type = envelope.WhichOneof("payload")
                
                if msg_type == "status":
                    print(f"[STATUS] E-Stop: {envelope.status.estop}, Manual: {envelope.status.manual}")
                elif msg_type == "pos":
                    p = envelope.pos
                    print(f"[POS] R: {p.roll}, P: {p.pitch}, Y: {p.yaw}")
                elif msg_type == "debug":
                    print(f"[DEBUG] ID: {envelope.debug.id}, Msg: {envelope.debug.content}")
                else:
                    print("Unknown message type received.")

            except Exception as e:
                print(f"Failed to decode: {e}")
            
            raw_buffer = bytearray()
    else:
        raw_buffer.extend(char)