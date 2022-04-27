<template>
  <div>
    <!-- Login -->
    <router-view v-if="getActive('Login')" />

    <!-- Dash -->
    <div class="container-scroller" v-if="!getActive('Login')">
      <!-- Side NAV -->
      <SideNav />

      <div class="container-fluid page-body-wrapper">
        <!-- Top NAV -->
        <TopNav />

        <div class="main-panel">
          <!-- TestView -->
          <router-view />
        </div>
      </div>
    </div>
  </div>
</template>

 <script>
import TopNav from "./components/TopNav.vue";
import SideNav from "./components/SideNav.vue";
import { auth } from "./main.js";
import { onAuthStateChanged } from "firebase/auth";

export default {
  name: "app",
  components: {
    TopNav,
    SideNav,
  },
  methods: {
    getActive: function (link) {
      if (this.$route.matched.some(({ name }) => name === link)) return true;
      else return false;
    },
  },
  mounted() {
    onAuthStateChanged(auth, (user) => {
      if (user) {
        this.$store.commit('setUser', user);
      } else {
        this.$store.commit('setUser', null);
      }
    });
  },
};
</script>

<style>
.hide {
  visibility: hidden;
}
</style>
