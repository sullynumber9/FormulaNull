import network
import socket
import json
from machine import UART, Pin
import time

# Connect to Wi-Fi

with open("credentials.json") as f:
    config_data = json.load(f)


ssid = config_data["Name"]
password = config_data["Password"]

print(ssid)
print(password)