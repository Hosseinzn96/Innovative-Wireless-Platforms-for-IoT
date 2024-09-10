import paho.mqtt.client as mqtt
import json

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected successfully.")
        client.subscribe("IP4IoT/lab5/309247")  
    else:
        print(f"Connection failed with code {rc}")

def on_message(client, userdata, msg):
    try:
        message_data = json.loads(msg.payload.decode('utf-8'))
        print(f"Message from {message_data['sender']}: {message_data['msg']}")
    except json.JSONDecodeError:
       print("Received a message that is not valid JSON")
    except KeyError:
        print("Received a message that does not conform to the expected schema")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect("localhost", 1883, 60)
except Exception as e:
    print(f"Failed to connect to the broker: {e}")

client.loop_forever()
