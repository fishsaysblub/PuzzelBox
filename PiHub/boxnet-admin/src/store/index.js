import { createStore } from 'vuex';

export default createStore({
  state: {
    user: null,
    devices: {},
    links: {}
  },
  getters: {
  },
  mutations: {
    "setUser"(state, user) {
      state.user = user;
    },
    "SOCKET_device_list_res"(state, data) {
      state.devices = data;
      console.log("Received socket device update");
    },
    "SOCKET_link_list_res"(state, data) {
      state.links = data;
      console.log("Received socket link update");
    }
  },
  actions: {
  },
  modules: {
  }
})
