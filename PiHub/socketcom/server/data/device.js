import web_io from "../sockets/web-socket.js";
import fs from "fs";
import path from "path";
import { fileURLToPath } from 'url';
import { dirname } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

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
	get_device_list();

	console.log("Found device of type " + type_list[data.type_id]);
	console.log(connected_devices);
}

/**
 * Remove device from connected_devices
 * 
 * @param {String} sid Device ID to remove
 */
export function remove_device(sid) {
	if (sid in connected_devices) {
		delete mac_sid_lookup[connected_devices[sid].mac_address];
		delete connected_devices[sid];
	}
	// Update web clients of new device
	get_device_list();

	console.log("Disconnected: " + sid);
	console.log(connected_devices);
}

/**
 * Get formatted device list and send to web
 * 
 * @returns Formatted device list for web
 */
export function get_device_list() {
	let return_data = {};

	for (const [sid, data] of Object.entries(connected_devices)) {
		return_data[sid] = {
			'device_name': type_list[data.type_id],
			'sid': sid,
			'device_status': status_list[device_status[sid]],
			'mac_address': data.mac_address,
			'ip_address': data.ip_address,
			'link': get_device_link(data.mac_address)
		};
	}
	web_io.emit("device_list_res", return_data);
	return return_data;
}

/**
 * Write made device link to file
 * @param {String} bomb_mac Bomb mac address to link
 * @param {String} box_mac Box mac address to link
 */
export function create_device_link(bomb_mac, box_mac) {
	if (bomb_mac != null && box_mac != null) {
		let data_entry = {}
		let output = null;
		data_entry[bomb_mac] = {
			link: box_mac,
			type: "bomb-box",
			time_stamp: Date.now()
		};
		data_entry[box_mac] = {
			link: bomb_mac,
			type: "box-bomb",
			time_stamp: Date.now()
		};
		data_entry = JSON.stringify(data_entry);

		fs.readFile(path.resolve(__dirname, "device_links.json"), "utf-8", (err, json_data) => {
			if (err) {
				console.log("File error: ", err);
				return;
			}
			try {
				let base = JSON.parse(json_data);
				let addon = JSON.parse(data_entry);
				output = { ...base, ...addon };
				fs.writeFile(path.resolve(__dirname, "device_links.json"), JSON.stringify(output), 'utf8', (err) => {
					if (err) {
						console.log("File error: ", err);
					}
					console.log("Device link added");

					// Update web clients of new link
					get_device_list();
				});
			} catch {
				console.log("Can't open file");
			}
		})
	}
}

/**
 * Remove link from table file
 * @param {String} mac Single side of link
 */
export function remove_device_link(mac) {
	fs.readFile(path.resolve(__dirname, "device_links.json"), "utf-8", (err, json_data) => {
		if (err) {
			console.log("File error: ", err);
			return;
		}
		try {
			let data = JSON.parse(json_data);
			if (mac in data) {
				let link_mac = data[mac].link;
				delete data[mac];
				delete data[link_mac];

				fs.writeFileSync(path.resolve(__dirname, "device_links.json"), JSON.stringify(data), 'utf8');
				console.log("Device link removed");

				// Update web clients of updated link
				get_device_list();
			}
		} catch {
			console.log("Can't open file");
		}
	})
}

/**
 * Get linked device entry
 * @param {String} mac Mac lookup in device link list
 * @returns Device link entry
 */
export function get_device_link(mac) {
	let data = {};
	try {
		data = fs.readFileSync(path.resolve(__dirname, "device_links.json"), "utf-8");
		data = JSON.parse(data);
		if (mac in data) {
			return data[mac];
		}
	} catch {
		console.log("File error");
	}
	
	return {};
}