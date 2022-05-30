import { create_device_link, get_device_list, mac_sid_lookup, remove_device_link } from '../data/device.js';
import deviceSocket from '../sockets/device-socket.js'

export default (io, socket) => {
    /**
     * Link devices for communication
     * @param {Json} data Bomb MAC and Box MAC for link
     */
    function device_link(data) {
        console.log("Linking:  ", data);
        if ("bomb_mac" in data && "box_mac" in data) {
            create_device_link(data.bomb_mac, data.box_mac);
        }
    }

    /**
     * Remove device link
     * @param {Json} data Bomb MAC and Box MAC for unlink
     */
    function device_unlink_req(data) {
        console.log("Unlinking:  ", data);
        remove_device_link(data.mac);
    }

    /**
     * Web device list request response
     * @param {null} data 
     */
    function ret_device_list(data) {
        console.log("Returning device list");
        get_device_list();
    }

    /**
     * Web device identify request
     * @param {Json} data mac : mac address
     */
    function device_ident_req(data) {
        if ("mac" in data)
            console.log("Send blink req to device " + data.mac + mac_sid_lookup[data.mac]);
            deviceSocket.to(mac_sid_lookup[data.mac]).emit("device_ident_req", {});
    }

    /**
     * Return settings from bomb, requested by settings page
     * @param {Json} data mac : mac address
     */
    function bomb_settings_req(data) {
        if ("mac" in data) {
            console.log("Send settings res to device " + data.mac);

            //! Temp test emit, should be live settings from bomb.
            socket.emit("bomb_settings_res", {
                "countdown_len": "01:20",
                "code_count": 9,
                "wire_cuts": ['w3'],
                "wire_links": [
                    {
                        "id": 1,
                        "data": "B"
                    },
                    {
                        "id": 2,
                        "data": "C"
                    },
                    {
                        "id": 3,
                        "data": "D"
                    },
                    {
                        "id": 4,
                        "data": "E"
                    },
                    {
                        "id": 5,
                        "data": "F"
                    },
                    {
                        "id": 6,
                        "data": "G"
                    },
                    {
                        "id": 7,
                        "data": "H"
                    },
                    {
                        "id": 0,
                        "data": "A"
                    },
                ]
            })
        }
    }

    /**
     * Send updated settings to bomb
     * @param {Json} data mac : mac address, settings : Bomb settings
     */
    function bomb_settings_save(data) {
        if ("mac" in data && "settings" in data) {
            console.log("Send settings to", data.mac, data.settings);
        }
    }

    // Socket calls
    socket.on("device_link_req", device_link);
    socket.on("device_unlink_req", device_unlink_req);
    socket.on("device_list_req", ret_device_list);
    socket.on("device_ident_req", device_ident_req);
    socket.on("bomb_settings_req", bomb_settings_req);
    socket.on("bomb_settings_save", bomb_settings_save);
}