import { device_status } from "../data/device.js";

export default (io, socket) => {
    /**
     * Handle device error
     * @param {Json} data Error data - code, text
     */
    function error_handler(data) {
        console.log("Error ", data);
    }

    /**
     * Handle device link request from the device.
     * @param {null} data 
     */
    function device_link_req(data) {
        console.log("Device: " + socket.id + " Requesting for link");
        //TODO Find link from stored links and emit link device back
        io.to(socket.id).emit("device_link_rep", 0);   //! NULL for now
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