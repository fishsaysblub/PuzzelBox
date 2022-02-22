import { createStore } from 'vuex';

export default createStore({
  state: {
    devices: {}
  },
  getters: {
  },
  mutations: {
    "SOCKET_device_list_res"(state, data) {
      state.devices = data;
      console.log("Received socket device update");
    }
  },
  actions: {
  },
  modules: {
  }
})
