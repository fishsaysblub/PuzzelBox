import socket
import socketio
from getmac import get_mac_address

sio = socketio.Client()


@sio.event
def connect():
    print('connection established')

@sio.event
def my_message(data):
    print('message received with ', data)
    sio.emit('my response', {'response': 'my response'})

@sio.on("type_req")
def on_type_request(data):
    type_info = {
        "type_id": 1, 
        "mac_address": get_mac_address(), 
        "ip_address": socket.gethostbyname(socket.gethostname())
    }

    sio.emit("type_rep", type_info)

@sio.event
def disconnect():
    print('disconnected from server')

sio.connect('http://localhost:5000')
sio.wait()