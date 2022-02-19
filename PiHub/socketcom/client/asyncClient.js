import 'dotenv/config'
import { execSync } from "child_process"
import { io } from "socket.io-client";

const socket = io("http://localhost:5000", {
	auth: {
		token: process.env.SERVER_TOKEN,
		type_id: 2,
		mac_address: getmac("eth0"),
		ip_address: getip("eth0")
	},
	query: {
		client: "JavaScript"
	}
});

/**
 * Get Mac address of interface
 * 
 * @param {String} iface Interface
 * @returns Mac address of interface
 */
function getmac(iface) {
	try	{
		return execSync("../localcmd/getmac.sh " + iface, { encoding: "utf8" }).replace(/\r?\n|\r/g, "");
	} catch {
		console.log("GetMac Failed");
	}
}

/**
 * Get IP address of interface
 * 
 * @param {String} iface Interface
 * @returns IP address of interface
 */
function getip(iface) {
	try	{
		return execSync("../localcmd/getip.sh " + iface, { encoding: "utf8" }).replace(/\r?\n|\r/g, "");
	} catch {
		console.log("GetIP Failed");
	}
}

/**
 * Device connect method
 * 
 * Gets called when a connection has been opened
 */
socket.on("connect", () => {
	console.log("Connection established ", socket.id);
});

/**
 * Device disconnect method
 * 
 * Gets called when the connection has been closed
 */
socket.on("disconnect", () => {
	console.log("Disconnected from server");
})