import store from '../store'
import VueSocketIO from 'vue-socket.io'
import { io } from 'socket.io-client'
// import { firebaseapp } from '@/main.js'

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

// Not loaden if user not Auth
let socket = null

export function initSocket() {
    console.log('Connecting to Socket');
    socket = new VueSocketIO({
        debug: true,
        connection: io(host, options),
        vuex: {
            store,
            actionPrefix: "SOCKET_",
            mutationPrefix: "SOCKET_"
        }
    })
}

export default socket