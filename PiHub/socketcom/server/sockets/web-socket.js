import 'dotenv/config'
import { Server, Socket } from 'socket.io';
import express from 'express';
import http from 'http';
import {connected_devices, get_device_list, get_link_list, mac_sid_lookup} from '../data/device.js';

// Handlers
import registerManagementHandler from '../handlers/webManagementHandler.js';
import { get_game_list } from '../data/game.js';

// Init server
const app = express();
const server = http.createServer(app);
const web_io = new Server(server, {
	cors: {
		origin: ["http://192.168.10.1:8080", "http://bombnet:8080", "http://localhost:8080","http://192.168.10.1", "http://bombnet", "http://localhost", "http://boxmaster.local"],
		methods: ["GET", "POST"]
	  }
});

// Make Socket avalible
export default web_io;

/**
 * Web connection method
 * 
 * Gets called when a new web client connects to the network
 * @param {Object} socket - Socket data object 
 */
web_io.on("connection", (socket) => {
	// Setup connection
	let sid = socket.id;
	console.log("Connected: " + sid);
	console.log("Webservice connected");

	// Supply webserver with device list
	get_device_list();
	get_link_list();
	socket.emit("game_list_res", get_game_list());

	/**
	 * Handle disconnect
	 */
	socket.on("disconnect", () => {
		console.log("Disconnected web: " + sid);
	})

	// Handlers
	registerManagementHandler(web_io, socket);
});

/**
 * Start socket server
 * @param {String} host Local listener IP address
 */
export function start_web_socket(host) {
	// Start server on hotspot interface
    server.listen(5001, host);
}
