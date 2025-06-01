import uasyncio as asyncio
from microdot_asyncio import Microdot, Response
from microdot_websocket import with_websocket
import json
import network
from machine import UART, Pin
import sys

# Load Wi-Fi credentials

# Start wifi access point
wlan = network.WLAN(network.AP_IF)
wlan.config(essid='PicoAP', password='legoman420')
wlan.active(True)

print("Access point created. connect to:", wlan.ifconfig())

# TX PIN 0
# RX PIN 1

# Set up UART (Pico GP0 -> Arduino RX)
uart0 = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
uart1 = UART(1, baudrate=9600, tx=Pin(4), rx=Pin(5))

# Set up Microdot WebSocket app
app = Microdot()
Response.default_content_type = 'application/json'

@app.route('/ws')
@with_websocket
async def websocket_handler(request, ws):
    print("WebSocket connected")

    try:
        while True:
            msg = await ws.receive()
            if msg is None:
                break

            try:
                data = json.loads(msg)
                lt = int(data.get('lt', 0))
                rt = int(data.get('rt', 0))
                a = int(data.get('a', 0))
                b = int(data.get('b', 0))
                # y = data.get('y', 0)
                # x = data.get('x', 0)
                lb = int(data.get('lb', 0))
                rb = int(data.get('rb', 0))
                # view = data.get('view', 0)
                # menu = data.get('menu', 0)

                print(lt, rt, a, b, lb, rb)
                # uart0.write(f"{lt},{rt},{a},{b},{lb},{rb}\n")
                # uart1.write(f"{lt},{rt},{a},{b},{lb},{rb}\n")

                if (lt == 1 and rt == 1 and a == 1 and b == 1 and lb == 1 and rb == 1):
                    sys.exit(0)
            except Exception as e:
                print("JSON parse error:", e)
    except Exception as e:
        print("WebSocket error:", e)

    print("WebSocket disconnected")
    return ''

# Start the server
async def main():
    print("Starting WebSocket server on port 80...")
    await app.start_server(host='0.0.0.0', port=8080)

asyncio.run(main())
