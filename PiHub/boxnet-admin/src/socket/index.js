import store from '../store'
import VueSocketIO from 'vue-socket.io'
import { io } from 'socket.io-client'

const host = 'http://127.0.0.1:5001';

const options = {
    auth: {
        token: process.env.SERVER_TOKEN,
        type_id: 0
    },
    query: {
        client: "JavaScript"
    }
};

class SocketIO {
    constructor() {
        this.socket = null;
    }

    get() {
        return this.socket.io;
    }

    initSocket() {
        console.log('Connecting to Socket');
        this.socket = new VueSocketIO({
            debug: true,
            connection: io(host, options),
            vuex: {
                store,
                actionPrefix: "SOCKET_",
                mutationPrefix: "SOCKET_"
            }
        })
        console.log(this.socket);
    }
}

let so = new SocketIO();
export default so;

// // Not loaden if user not Auth
// let socket = null

// export function initSocket() {
//     console.log('Connecting to Socket');
//     socket = new VueSocketIO({
//         debug: true,
//         connection: io(host, options),
//         vuex: {
//             store,
//             actionPrefix: "SOCKET_",
//             mutationPrefix: "SOCKET_"
//         }
//     })
//     console.log(socket);
// }

// export default socket