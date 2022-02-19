import store from '../store'
import VueSocketIO from 'vue-socket.io'
import { io } from 'socket.io-client'

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
    connection: io('http://localhost:5000', options), //options object is Optional
    vuex: {
        store,
        actionPrefix: "SOCKET_",
        mutationPrefix: "SOCKET_"
    }
})

export default socket