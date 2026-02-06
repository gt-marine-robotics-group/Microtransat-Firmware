import serial
from cobs import cobs
import message_pb2
import time

# Update with your Pico's COM port
ser = serial.Serial('COM12', 115200)

def send_position(r, p, y, surge, sway, heave):
    # 1. Create the specific message
    pos_msg = message_pb2.positionCommand()
    pos_msg.roll = r
    pos_msg.pitch = p
    pos_msg.yaw = y
    pos_msg.surge = surge
    pos_msg.sway = sway
    pos_msg.heave = heave

    # 2. Wrap it in the Envelope
    envelope = message_pb2.Envelope()
    envelope.pos.CopyFrom(pos_msg)

    # 3. Serialize and COBS encode
    serialized_data = envelope.SerializeToString()
    encoded_data = cobs.encode(serialized_data)

    # 4. Append the 0x00 delimiter and send
    ser.write(encoded_data + b'\x00')
    print(f"Sent: {r}, {p}, {y}, {surge}, {sway}, {heave}")

if __name__ == "__main__":
    while True:
        try:
            val = input("Enter 6 values (R P Y Surge Sway Heave) or 'q': ")
            if val.lower() == 'q': break
            
            nums = [int(x) for x in val.split()]
            if len(nums) == 6:
                send_position(*nums)
        except Exception as e:
            print(f"Error: {e}")