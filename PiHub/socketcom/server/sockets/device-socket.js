import 'dotenv/config'
import { Server, Socket } from 'socket.io';
import express from 'express';
import http from 'http';
import {remove_device, set_device_info} from '../data/device.js';

// Handlers
import registerTypeHandler from '../handlers/typeHandler.js';
import registerManagementHandler from '../handlers/deviceManagementHandler.js'

// Init server
const app = express();
const server = http.createServer(app);
const device_io = new Server(server, {
	// options
});

// Make Socket avalible
export default device_io;

/**
 * Device connection method
 * 
 * Gets called when a new device connects to the network
 * @param {Object} socket - Socket data object 
 */
device_io.on("connection", (socket) => {
	console.log("Connected: " + socket.id + socket.handshake.query.test);

	// Handle type information
	let auth = socket.handshake.auth;
	let data = {
		type_id: parseInt(auth.type_id),
		mac_address: auth.mac_address,
		ip_address: auth.ip_address
	}
	if (data.type_id == 1 || data.type_id == 2) {
		set_device_info(socket.id, data);
	} else {
		console.log("Unknown device connected")
	}

	// Send typecheck to older non JavaScript clients
	if (socket.handshake.query.client != "JavaScript") {
		console.log("Non JavaScript client");
		device_io.to(socket.id).emit("type_req", 0);
	}

	/**
	 * Handle disconnect
	 */
	socket.on("disconnect", () => {
		remove_device(socket.id);
	})

	// Handlers
	registerTypeHandler(device_io, socket);
	registerManagementHandler(device_io, socket);

});

/**
 * Start socket server
 * @param {String} host Local listener IP address
 */
export function start_device_socket(host) {
	// Start server
	server.listen(5000, host);
}
