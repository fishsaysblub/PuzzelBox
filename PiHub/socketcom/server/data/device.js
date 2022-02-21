import web_io from "../sockets/web-socket.js";

export default null;

// Constants
export const type_list = ["Web", "Bomb", "PuzzleBox"]
export const status_list = ["Idle", "InGame"]

// Data objects
export let connected_devices = {}
export let mac_sid_lookup = {}
export let device_status = {}

/**
 * Write device info to storage objects
 * 
 * @param {String} sid - Device ID
 * @param {Object} data - Returned type data from client
 */
 export function set_device_info(sid, data) {
	for (const [local_sid, local_data] of Object.entries(connected_devices)) {
		if (data.mac_address == local_data.mac_address) {
			delete connected_devices[local_sid];
			delete mac_sid_lookup[local_data.mac_address];
			console.log("Device updated information");
		}
	}
	connected_devices[sid] = data;
	mac_sid_lookup[data["mac_address"]] = sid;
	device_status[sid] = 0;

	// Update web clients of new device
	web_io.emit("device_list_rep", get_device_list());

	console.log("Found device of type " + type_list[data.type_id]);
	console.log(connected_devices);
}

export function remove_device(sid) {
	if (sid in connected_devices) {
		delete mac_sid_lookup[connected_devices[sid].mac_address];
		delete connected_devices[sid];
	}
	// Update web clients of new device
	web_io.emit("device_list_rep", get_device_list());

	console.log("Disconnected: " + sid);
	console.log(connected_devices);
}

export function get_device_list() {
	let return_data = {};

	for (const [sid, data] of Object.entries(connected_devices)) {
		return_data[sid] = {
			'device_name': type_list[data.type_id],
			'sid': sid,
			'device_status': status_list[device_status[sid]],
			'mac_address': data.mac_address,
			'ip_address': data.ip_address
		};
	}
	return return_data;
}