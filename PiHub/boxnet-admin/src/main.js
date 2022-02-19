import { createApp } from 'vue'
import App from './App.vue'
import store from './store'
import router from './router'
import socket from './socket'

createApp(App).use(router).use(store).use(socket).mount('#app')
