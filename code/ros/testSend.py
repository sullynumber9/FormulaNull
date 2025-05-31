import asyncio
import websockets

async def test_ws():
    uri = "ws://192.168.87.27:8080/ws"
    async with websockets.connect(uri) as ws:
        await ws.send("Hello Pico!")
        response = await ws.recv()
        print("Received:", response)

asyncio.run(test_ws())
