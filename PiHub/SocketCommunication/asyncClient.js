import 'dotenv/config'
import { execSync } from "child_process"
import { io } from "socket.io-client";

function getmac(cwd) {
	return execSync("../localcmd/getmac.sh", { cwd, encoding: "utf8" }).replace(/\r?\n|\r/g, "");;
}

function getip(cwd) {
	return execSync("../localcmd/getip.sh", { cwd, encoding: "utf8" }).replace(/\r?\n|\r/g, "");;
}

const socket = io("http://localhost:5000", {
	auth: {
		token: process.env.SERVER_TOKEN
	},
	query: {
		type_id: 2,
		mac_address: getmac(),
		ip_address: getip()
	}
});

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