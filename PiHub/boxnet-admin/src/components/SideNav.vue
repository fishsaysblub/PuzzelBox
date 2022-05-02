<template>
  <div>
    <nav class="sidebar sidebar-offcanvas" id="sidebar">
      <!-- Logo -->
      <div
        class="
          sidebar-brand-wrapper
          d-none d-lg-flex
          align-items-center
          justify-content-center
          fixed-top
        "
      >
        <router-link to="/">
          <a class="sidebar-brand brand-logo" href="#"
            ><img src="@/assets/images/logo.svg" alt="logo"
          /></a>
          <a class="sidebar-brand brand-logo-mini" href="#"
            ><img src="@/assets/images/logo-mini.svg" alt="logo"
          /></a>
        </router-link>
      </div>

      <ul class="nav">
        <li class="nav-item nav-category">
          <span class="nav-link">Navigation</span>
        </li>

        <li class="nav-item menu-items" :class="{ active: getActive('Dash') }">
          <router-link class="nav-link" to="/">
            <span class="menu-icon">
              <i class="mdi mdi-speedometer"></i>
            </span>
            <span class="menu-title">Scoreboard</span>
          </router-link>
        </li>

        <li class="nav-item menu-items" :class="{ active: getActive('SettingsList') }">
          <router-link class="nav-link" to="/settings">
            <span class="menu-icon">
              <i class="mdi mdi-settings"></i>
            </span>
            <span class="menu-title">Settings</span>
          </router-link>
        </li>

        <!-- Dropdown -->
        <li class="nav-item menu-items" :class="{ active: getActive('Link') || getActive('Network') }">
          <a
            class="nav-link"
            data-toggle="collapse"
            href="#ui-basic"
            aria-expanded="false"
            aria-controls="ui-basic"
          >
            <span class="menu-icon">
              <i class="mdi mdi-laptop"></i>
            </span>
            <span class="menu-title">Network</span>
            <i class="menu-arrow"></i>
          </a>
          <div class="collapse" :class="{ show: getActive('Link') || getActive('Network') }" id="ui-basic">
            <ul class="nav flex-column sub-menu">
              <li class="nav-item">
                <router-link class="nav-link" :class="{ active: getActive('Network') }" to="/network">Network Map</router-link>
              </li>
              <li class="nav-item">
                <router-link class="nav-link" :class="{ active: getActive('Link') }" to="/devicelink"
                  >Device Links</router-link
                >
              </li>
            </ul>
          </div>
        </li>
      </ul>
    </nav>
  </div>
</template>

<script>
export default {
  name: "SideNav",
  props: {},
  methods: {
    getActive: function (link) {
      if (this.$route.matched.some(({ name }) => name === link)) return true;
      else return false;
    },
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
