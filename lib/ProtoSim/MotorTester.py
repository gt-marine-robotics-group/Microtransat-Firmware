import serial
from cobs import cobs
import message_pb2
import sys

# Setup Serial - adjust COM port as needed
try:
    ser = serial.Serial('COM7', 115200, timeout=1)
except Exception as e:
    print(f"Error: {e}")
    sys.exit(1)

def send_motors(pwm_list):
    """
    Takes a list of 8 integers (0-255) and sends them as a motorCommand envelope.
    """
    if len(pwm_list) != 8:
        print("Error: Need exactly 8 PWM values.")
        return

    # 1. Create the motor message
    motor_msg = message_pb2.motorCommand()
    motor_msg.motor1 = pwm_list[0]
    motor_msg.motor2 = pwm_list[1]
    motor_msg.motor3 = pwm_list[2]
    motor_msg.motor4 = pwm_list[3]
    motor_msg.motor5 = pwm_list[4]
    motor_msg.motor6 = pwm_list[5]
    motor_msg.motor7 = pwm_list[6]
    motor_msg.motor8 = pwm_list[7]

    # 2. Wrap in Envelope
    # Note: Ensure 'motors' matches the name in your Envelope oneof
    envelope = message_pb2.Envelope()
    envelope.motor_msg.CopyFrom(motor_msg) 

    # 3. Serialize, COBS encode, and Terminate
    serialized = envelope.SerializeToString()
    encoded = cobs.encode(serialized)
    ser.write(encoded + b'\x00')
    
    print(f"Sent PWMs: {pwm_list}")

if __name__ == "__main__":
    print("Enter 8 PWM values (0-255) separated by spaces, or 'q' to quit.")
    while True:
        try:
            inp = input(">> ")
            if inp.lower() == 'q': break
            
            # Map input to integers
            vals = [int(x) for x in inp.split()]
            
            # Basic validation
            if any(v < 0 or v > 255 for v in vals):
                print("Warning: PWM values should be between 0 and 255.")
            
            send_motors(vals)
        except ValueError:
            print("Invalid input. Please enter numbers.")
        except Exception as e:
            print(f"Error: {e}")