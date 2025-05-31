try:
    import uasyncio
    print("uasyncio is available!")
except ImportError:
    print("uasyncio is NOT available.")