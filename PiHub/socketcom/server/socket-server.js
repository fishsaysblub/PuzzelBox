import {start_device_socket} from './sockets/device-socket.js';
import {start_web_socket} from './sockets/web-socket.js';

// Device IP setting for development
const device_host_ip = "127.0.0.1";
const web_host_ip = "127.0.0.1";

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