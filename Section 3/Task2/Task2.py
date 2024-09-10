import paho.mqtt.client as mqtt

sender_id = "309247"
broker_address = "localhost"
port = 1883

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

while True:
    # User input in the format <student_id_receiver>:<msg>
    user_input = input("Enter receiver ID and message (student_id_receiver:msg): ")
    student_id_receiver, msg = user_input.split(':', 1)
    topic = f"IP4IoT/lab5/{student_id_receiver}"
    message = {"sender": sender_id, "msg": msg}
    
    # Publish the message
    client.publish(topic, payload=str(message))
    print(f"Message sent to {student_id_receiver}: {msg}")


