import serial
import time

# Establish serial connection
arduino = serial.Serial(
    port='COM3', 
    baudrate=115200, 
    timeout=1, 
    write_timeout=1
)

time.sleep(2)

# Send text to be displayed
try:
    while True:
        text_to_send = input("Send this text (or control-C to exit): ")
        if text_to_send.strip():
            arduino.write(("  " + text_to_send + '\n').encode('utf-8'))
            print(f"Sent: {text_to_send}")
        else:
            print("No text entered.")
except KeyboardInterrupt:
    print("\nExiting…")
    arduino.close()
