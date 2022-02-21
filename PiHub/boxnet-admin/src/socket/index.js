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

const socket = new VueSocketIO({
    debug: true,
    connection: io(host, options), //options object is Optional
    vuex: {
        store,
        actionPrefix: "SOCKET_",
        mutationPrefix: "SOCKET_"
    }
})

export default socket