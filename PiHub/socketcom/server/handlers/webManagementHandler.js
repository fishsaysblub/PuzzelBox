import { create_device_link, get_device_list, remove_device_link } from '../data/device.js';
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

    // Socket calls
    socket.on("device_link_req", device_link);
    socket.on("device_unlink_req", device_unlink_req);
    socket.on("device_list_req", ret_device_list);
}