import paho.mqtt.client as mqtt
import struct

# MQTT broker settings
broker_address = "localhost"
port = 1883
topic = "309247"

# Define the callback for when the client receives a CONNACK response from the server
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe(topic)

# Define the callback for when a PUBLISH message is received from the server
def on_message(client, userdata, msg):
    # Decode the CayenneLPP message
    if len(msg.payload) >= 4:
        channel = msg.payload[0]
        type = msg.payload[1]
        msb = msg.payload[2]
        lsb = msg.payload[3]

        if channel == 0x01 and type == 0x67:
            temperature_raw = (msb << 8) | lsb  # Combine the two bytes
            temperature = temperature_raw / 10.0  # Convert to temperature with one decimal place
            print(f"Received temperature: {temperature}°C")
        else:
            print("Received message with unexpected format.")
    else:
        print("Received message with insufficient length.")

# Create an MQTT client instance
client = mqtt.Client()

# Assign the callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect(broker_address, port, 60)

# Blocking call that processes network traffic, dispatches callbacks, and handles reconnecting
client.loop_forever()
