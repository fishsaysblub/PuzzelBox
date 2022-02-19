import socket
import fcntl
import struct
import socketio
from getmac import get_mac_address

sio = socketio.Client()
connected = False
i_face = "eth0" # wlan0 on PI

@sio.event
def connect():
    print('Connection established')

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        return socket.inet_ntoa(fcntl.ioctl(
            s.fileno(),
            0x8915,  # SIOCGIFADDR
            struct.pack('256s', bytes(ifname[:15], 'utf-8'))
        )[20:24])
    except:
        print("GetIP Failed")


@sio.event
def my_message(data):
    print('Message received with ', data)
    sio.emit('my response', {'response': 'my response'})

@sio.on("type_req")
def on_type_request(data):
    type_info = {
        "type_id": 2, 
        "mac_address": get_mac_address(interface=i_face), 
        "ip_address": get_ip_address("bat0")
    }
    print("Sending type")
    sio.emit("type_rep", type_info)

@sio.event
def disconnect():
    print('Disconnected from server')


while not connected:
    try:
        sio.connect('http://localhost:5000/', auth={
            "token":"A123",
            "type_id": 2, 
            "mac_address": get_mac_address(interface=i_face), 
            "ip_address": get_ip_address("bat0")
        })
        connected = True
    except socketio.exceptions.ConnectionError:
        print(f"Connect failed")
        sio.sleep(5)

sio.wait()