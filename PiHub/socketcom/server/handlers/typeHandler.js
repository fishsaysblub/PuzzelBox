import {set_device_info} from '../data/device.js';

export default (io, socket) => {
    /**
	 * Handle type request response
	 * 
	 * Only used if connected to Python socket client
	 * @param {Object} data - Returned type data from client
	 */
    function type_request(data) {
        console.log("Received type data.")
        set_device_info(socket.id, data);
    }

    // Socket calls
    socket.on("type_rep", type_request);
}