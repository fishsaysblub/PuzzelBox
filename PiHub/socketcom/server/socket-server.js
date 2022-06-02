import { create_game, get_game_list } from './data/game.js';
import {start_device_socket} from './sockets/device-socket.js';
import {start_web_socket} from './sockets/web-socket.js';

// Device IP setting for development
const device_host_ip = "192.168.199.1";
const web_host_ip = "192.168.10.1";

console.log("Starting socket server");
/**
 * Event message syntax:
 *  - Request                   = [name]_req
 *  - Response                  = [name]_rep
 *  - Client generated event    = [name]
 */

/**
 * Start device socket
 * Mesh data transfer socket
 */
start_device_socket(device_host_ip);

/**
 * Start web socket
 * User website interaction socket
 */
start_web_socket(web_host_ip);