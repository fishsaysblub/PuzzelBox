import { createStore } from 'vuex';

export default createStore({
  state: {
    devices: {}
  },
  getters: {
  },
  mutations: {
    "SOCKET_device_list_rep"(state, server) {
      state.devices = server;
      console.log("Received socket device update");
    }
  },
  actions: {
  },
  modules: {
  }
})
