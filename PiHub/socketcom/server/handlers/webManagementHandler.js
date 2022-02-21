import { get_device_list } from '../data/device.js';
import deviceSocket from '../sockets/device-socket.js'

export default (io, socket) => {
    /**
     * Link devices for communication
     * @param {Json} data Bomb MAC and Box MAC for link
     */
    function device_link(data) {
        console.log("Linking:  ", data);
        //TODO Save link to file and send to devices
    }

    /**
     * Web device list request response
     * @param {null} data 
     */
    function ret_device_list(data) {
        console.log("Returning device list");
        io.to(socket.id).emit("device_list_rep", get_device_list())
    }

    // Socket calls
    socket.on("device_link_req", device_link);
    socket.on("device_list_req", ret_device_list);
}