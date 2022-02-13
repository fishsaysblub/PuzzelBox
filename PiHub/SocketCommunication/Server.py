"""@package Socket Server
Socket IO server
"""
import json
import eventlet
import socketio
import ipaddress as ip

import ComConstant as s

# Create Socket.IO server
sio = socketio.Server()
# Wrap with WSGI app
app = socketio.WSGIApp(sio)

# Device list
connected_devices = {}
mac_sid_lookup = {}


#### Server connect ####
def start_server():
    """Start Socket server
    """
    eventlet.wsgi.server(eventlet.listen((s.SERVER_IP, s.SERVER_PORT)), app, log_output=__debug__)


### Handle connect / disconnect ####
@sio.event
def connect(sid, environ):
    """Server on connect method

    Args:
        sid (string): Client SID
        environ (Json): Client data
    """
    client_ip = environ['REMOTE_ADDR']

    if ip.ip_address(client_ip) in ip.ip_network(s.NETWORK_RANGE):
        print(f"\033[93m> New connection request from ({sid}) IP: {client_ip} \n Connecting...\033[97m")
        sio.emit("type_req", 0, to=sid);       # Request connected device data and type
    else:
        print('\033[91m> Unknown network range ', client_ip, '\033[97m')
        raise ConnectionRefusedError('out or ip range')


@sio.on("type_rep")
def on_type_response(sid, data):
    """Handle type respons

    Args:
        sid (string): Device sid
        data (json): Received type data
    """
    # Check for mac address in table
    for localsid, device in connected_devices.items():
        if data["mac_address"] == device["mac_address"]:
            connected_devices.pop(localsid)
            mac_sid_lookup.pop(device["mac_address"])
            break

    # Store device info
    connected_devices[sid] = data
    mac_sid_lookup[data["mac_address"]] = sid

    # Send user response
    print(f"\033[93m> Found device of type {s.type_list[data['type_id']]}\033[97m")
    if __debug__: 
        print(json.dumps(connected_devices, indent=4))
        print(json.dumps(mac_sid_lookup, indent=4))


@sio.event
def disconnect(sid):
    """Server on disconnect method

    Args:
        sid (string): Client SID
    """
    mac_sid_lookup.pop(connected_devices[sid]["mac_address"])
    connected_devices.pop(sid)

    print('\033[93m> Disconnect ', sid, '\033[97m')
    if __debug__: 
        print(json.dumps(connected_devices, indent=4))
        print(json.dumps(mac_sid_lookup, indent=4))


## Test start method
if __name__ == '__main__':
    start_server();