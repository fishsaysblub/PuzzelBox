//import createServer from "express";
import 'dotenv/config'
import { Server, Socket } from 'socket.io';
import express from 'express';
import http from 'http';

// Init server
const app = express();
const server = http.createServer(app);
const io = new Server(server, {
	// Settings
});

// Constants
const type_list = ["Hub", "Bomb", "PuzzleBox"]

// Data objects
let connected_devices = {}
let mac_sid_lookup = {}

/**
 * Device connection method
 * 
 * Gets called when a new device connects to the network
 * @param {Object} socket - Socket data object 
 */
io.on("connection", (socket) => {
	// Setup connection
	let sid = socket.id;
	console.log("Connected: " + sid);
	if (socket.handshake.auth.token === process.env.SERVER_TOKEN) {
		let qu = socket.handshake.query;
		let data = {
			type_id: parseInt(qu.type_id),
			mac_address: qu.mac_address,
			ip_address: qu.ip_address
		}
		store_device_info(sid, data);
	} else {
		io.to(socket.id).emit("type_req", 0);
	}

	/**
	 * Handle type request response
	 * 
	 * Only used if connected to Python socket client
	 * @param {Object} data - Returned type data from client
	 */
	socket.on("type_rep", (data) => {
		store_device_info(sid, data);
	})

	/**
	 * Handle disconnect
	 */
	socket.on("disconnect", () => {
		if (sid in connected_devices) {
			delete mac_sid_lookup[connected_devices[sid].mac_address];
			delete connected_devices[sid];
		}

		console.log("Disconnected: " + sid);
		console.log(connected_devices);
	})
});

/**
 * Write device info to storage objects
 * 
 * @param {String} sid - Device ID
 * @param {Object} data - Returned type data from client
 */
function store_device_info(sid, data) {
	for (const [local_sid, local_data] of Object.entries(connected_devices)) {
		if (data.mac_address == local_data.mac_address) {
			delete connected_devices[local_sid];
			delete mac_sid_lookup[local_data.mac_address];
		}
	}
	connected_devices[sid] = data;
	mac_sid_lookup[data["mac_address"]] = sid

	console.log("Found device of type " + type_list[data.type_id]);
	console.log(connected_devices);
}

// Start server
server.listen(5000, "127.0.0.1");