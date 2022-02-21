<template>
  <div class="home">
    <img alt="Vue logo" src="../assets/logo.png">
    <HelloWorld msg="Welcome to Your Vue.js App"/>
    <p>{{ $store.state.devices }}</p>
    <button @click="clickButton()"> send</button>
  </div>
</template>

<script>
// @ is an alias to /src
import HelloWorld from '@/components/HelloWorld.vue'

export default {
  name: 'HomeView',
  components: {
    HelloWorld
  },
  methods: {
    clickButton: function () {
      console.log("Sending")
      this.$socket.emit("device_list_req");
    }
  }
}
</script>
