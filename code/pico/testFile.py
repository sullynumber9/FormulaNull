import time
import machine


time.sleep(3)

print("booted up!")

led = machine.Pin("LED", machine.Pin.OUT)

while True:
    led.toggle()      # Switch LED on/off
    time.sleep(0.5) 