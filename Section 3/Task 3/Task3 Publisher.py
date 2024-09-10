import paho.mqtt.client as mqtt
import time
import random
import struct

# MQTT broker settings
broker_address = "localhost"
port = 1883
topic = "309247"  

# Create an MQTT client instance
client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

# Connect to the MQTT broker
client.connect(broker_address, port, 60)
client.on_connect = on_connect

client.loop_start()  

try:
    while True:
        # Generate a random temperature between 0.0°C and 20.0°C
        temp_c = random.randint(0, 200)  
       
        payload = bytearray([0x01, 0x67]) + struct.pack("!h", temp_c)
        client.publish(topic, payload)
        print(f"Published temperature: {temp_c/10:.1f}°C to {topic}")
        time.sleep(10)  # Send data every 10 seconds

except KeyboardInterrupt:
    print("Program terminated by user")

finally:
    client.loop_stop()
    client.disconnect()
