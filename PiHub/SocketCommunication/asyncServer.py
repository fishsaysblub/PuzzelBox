"""@package Socket Server
Socket IO server
"""
import json
import socketio
from aiohttp import web
import ipaddress as ip

import ComConstant as s

# Create Socket.IO server
sio = socketio.AsyncServer()
# Wrap with WSGI app
app = web.Application()
sio.attach(app)

# Device list
connected_devices = {}
mac_sid_lookup = {}


#### Server connect ####
def start_server():
    """Start Socket server
    """
    web.run_app(app, host=s.SERVER_IP, port=s.SERVER_PORT)


### Handle connect / disconnect ####
@sio.event
async def connect(sid, environ):
    """Server on connect method

    Args:
        sid (string): Client SID
        environ (Json): Client data
    """
    print(f"\033[93m> New connection request from ({sid})  \n Connecting...\033[97m")
    await sio.emit("type_req", 0, to=sid);       # Request connected device data and type


@sio.on("type_rep")
async def on_type_response(sid, data):
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
    if sid in connected_devices:
        mac_sid_lookup.pop(connected_devices[sid]["mac_address"])
        connected_devices.pop(sid)

    print('\033[93m> Disconnect ', sid, '\033[97m')
    if __debug__: 
        print(json.dumps(connected_devices, indent=4))
        print(json.dumps(mac_sid_lookup, indent=4))


## Test start method
if __name__ == '__main__':
    start_server();