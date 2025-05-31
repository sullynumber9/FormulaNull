from microdot_asyncio import Microdot, Response
from microdot_websocket import with_websocket
import uasyncio as asyncio

app = Microdot()
Response.default_content_type = 'application/json'

@app.route('/')
async def index(request):
    return 'Hello from Pico!'

@app.route('/ws')
@with_websocket
async def websocket_handler(request, ws):
    print("WebSocket connected")
    try:
        while True:
            msg = await ws.receive()
            if msg is None:
                break
            print("Received:", msg)
            await ws.send("Echo: " + msg)
    except Exception as e:
        print("WebSocket error:", e)
    print("WebSocket disconnected")
    return ''

async def main():
    await app.start_server(host='0.0.0.0', port=8080)

asyncio.run(main())
