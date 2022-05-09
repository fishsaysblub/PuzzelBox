import { createApp } from 'vue'
import App from './App.vue'
import store from './store'
import router from './router'
import socket from './socket'
// import { initSocket } from './socket'

// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth } from 'firebase/auth';

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyCMEbxWo19PSfoJAASbaWDJjmmZBTt_JrA",
    authDomain: "puzzlebox-12971.firebaseapp.com",
    projectId: "puzzlebox-12971",
    storageBucket: "puzzlebox-12971.appspot.com",
    messagingSenderId: "199653926678",
    appId: "1:199653926678:web:e91351f6dd6b04682dd237"
};

// Initialize Firebase
export const firebaseapp = initializeApp(firebaseConfig);
export const auth = getAuth(firebaseapp);

firebaseapp.getCurrentUser = () => {
    return new Promise((resolve, reject) => {
        const unsubscribe = auth.onAuthStateChanged(user => {
            unsubscribe();
            resolve(user);
            if (user != null) {
                // Load socket if user is logged in
                if (socket.socket == null) {
                    socket.initSocket();
                    store.state.user = user;
                }
            }
        }, reject);
    }
)};


const app = createApp(App);
app.use(router)
app.use(store)
app.use(socket)

app.mount('#app')
