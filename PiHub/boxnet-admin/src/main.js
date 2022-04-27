import { createApp } from 'vue'
import App from './App.vue'
import store from './store'
import router from './router'
import socket from './socket'
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth } from 'firebase/auth';
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

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
const firebaseapp = initializeApp(firebaseConfig);
export const auth = getAuth(firebaseapp);

const app = createApp(App);
app.use(router)
app.use(store)
app.use(socket)

app.mount('#app')
