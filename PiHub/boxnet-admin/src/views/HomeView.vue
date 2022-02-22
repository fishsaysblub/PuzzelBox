<template>
  <div class="home">
    <img alt="Vue logo" src="../assets/logo.png" />
    <HelloWorld msg="Welcome to Your Vue.js App" />
    <p>{{ $store.state.devices }}</p>
    <button @click="clickButton()">add</button>
    <button @click="clickButton2()">remove</button>
  </div>
</template>

<script>
// @ is an alias to /src
import HelloWorld from "@/components/HelloWorld.vue";

export default {
  name: "HomeView",
  components: {
    HelloWorld,
  },
  methods: {
    clickButton: function () {
      console.log("Sending");
      this.$socket.emit("device_unlink_req", { mac: "00:15:5d:fa:1f:ad" });
      this.$socket.emit("device_link_req", { bomb_mac: "41", box_mac: "00:15:5d:fa:1f:ad" });
    },
    clickButton2: function () {
      console.log("Sending");
      this.$socket.emit("device_unlink_req", { mac: "00:15:5d:fa:1f:ad" });
    },
  },
};
</script>
