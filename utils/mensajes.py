# Simple ejemplo en Python para mostrar los mensajes enviados desde la App
# gsampallo.com
# @gsampallo

import paho.mqtt.client as mqtt
import time


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    client.subscribe("MENSAJES")
    

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(time.strftime("%d-%m-%Y %H:%M:%S", time.localtime())+" "+msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)

client.loop_forever()