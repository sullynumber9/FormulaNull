import asyncio
import json
import pygame
import websockets

# Setup pygame joystick
pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() == 0:
    print("No controller detected.")
    exit()

joystick = pygame.joystick.Joystick(0)
joystick.init()

with open("credentials.json") as f:
    config_data = json.load(f)

pico_ip = config_data["pico_ip"]
port = 8080
PICO_WS_URL = f"ws://{pico_ip}:{port}/ws"  # Add /ws route

def apply_deadzone(val, dz=0.05):
    return 0 if abs(val) < dz else val

async def send_controller_input():
    async with websockets.connect(PICO_WS_URL) as websocket:
        print("Connected to Pico websocket server")

        while True:
            pygame.event.pump()
            lt = (joystick.get_axis(4) + 1) / 2
            if (lt > 0.1):
                lt = 1
            else:
                 lt = 0
            rt = (joystick.get_axis(5) + 1) / 2
            if (rt > 0.1):
                rt = 1
            else:
                 rt = 0

            a = joystick.get_button(0)
            b = joystick.get_button(1)

            lb = joystick.get_button(4)
            rb = joystick.get_button(5)



            print(lt, rt, a, b, lb, rb)

            data = {
                "lt": int(lt),
                "rt": int(rt),
                "a": int(a),
                "b": int(b),
                "lb": int(lb),
                "rb": int(rb),
            }


            try:
                await websocket.send(json.dumps(data))
            except Exception as e:
                print("Send failed:", e)
                break

            await asyncio.sleep(0.05)

asyncio.run(send_controller_input())
