//import createServer from "express";
import 'dotenv/config'
import { Server, Socket } from 'socket.io';
import express from 'express';
import http from 'http';
import {connected_devices, mac_sid_lookup} from './data/device.js';

// Init server
const app = express();
const server = http.createServer(app);
const io = new Server(server, {
	cors: {
		origin: ["http://192.168.10.1:8080", "http://bombnet:8080"],
		methods: ["GET", "POST"]
	  }
});

/**
 * Web connection method
 * 
 * Gets called when a new web client connects to the network
 * @param {Object} socket - Socket data object 
 */
io.on("connection", (socket) => {
	// Setup connection
	let sid = socket.id;
	console.log("Connected: " + sid);
	console.log("Webservice connected");
    console.log(connected_devices);
    console.log(mac_sid_lookup);

	/**
	 * Handle disconnect
	 */
	socket.on("disconnect", () => {
		console.log("Disconnected: " + sid);
	})
});

export function start_web_socket() {
	// Start server on hotspot interface
    server.listen(5000, "192.168.10.1");
}
