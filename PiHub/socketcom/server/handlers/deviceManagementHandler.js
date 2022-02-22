import { device_status, get_device_link, mac_sid_lookup } from "../data/device.js";

export default (io, socket) => {
    /**
     * Handle device error
     * @param {Json} data Error data - code, text
     */
    function error_handler(data) {
        console.log("Error ", data);
    }

    /**
     * Handle link request from the device.
     * @param {null} data 
     */
    function device_link_req(data) {
        console.log("Device: " + socket.id + " Requesting for link");
        io.to(socket.id).emit("device_link_res", get_device_link(mac_sid_lookup[socket.id]));
    }

    /**
     * Receive new state from device
     * @param {Int} data 
     */
    function state_change(data) {
        device_status[socket.id] = parseInt(data);
    }

    // Socket calls
    socket.on("device_error", error_handler);
    socket.on("device_link_req", device_link_req);
    socket.on("device_state_change", state_change);
}