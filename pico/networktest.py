import network
import time

ssid = 'name'
password = 'pass'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

# Wait for connection
max_wait = 10
while max_wait > 0:
    if wlan.isconnected():
        break
    print('Connecting...')
    time.sleep(1)
    max_wait -= 1

if wlan.isconnected():
    print('Connected. IP Address:', wlan.ifconfig()[0])
else:
    print('Failed to connect.')