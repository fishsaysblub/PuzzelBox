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
          ><img src="assets/images/logo.svg" alt="logo"
        /></a>
        <a class="sidebar-brand brand-logo-mini" href="#"
          ><img src="assets/images/logo-mini.svg" alt="logo"
        /></a>
      </router-link>
      </div>

      <ul class="nav">

        <li class="nav-item nav-category">
          <span class="nav-link">Navigation</span>
        </li>

        <li class="nav-item menu-items" :class="{active: getActive('Dash')}">
          <router-link class="nav-link" to="/">
            <span class="menu-icon">
              <i class="mdi mdi-speedometer"></i>
            </span>
            <span class="menu-title">Dashboard</span>
          </router-link>
        </li>

        <li class="nav-item menu-items" :class="{active: getActive('Network')}">
          <router-link class="nav-link" to="/network">
            <span class="menu-icon">
              <i class="mdi mdi-speedometer"></i>
            </span>
            <span class="menu-title">Network</span>
          </router-link>
        </li>
        <li class="nav-item menu-items" :class="{active: getActive('Link')}">
          <router-link class="nav-link" to="/devicelink">
            <span class="menu-icon">
              <i class="mdi mdi-speedometer"></i>
            </span>
            <span class="menu-title">Device Links</span>
          </router-link>
        </li>

        <!-- Dropdown -->
        <li class="nav-item menu-items">
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
            <span class="menu-title">Basic UI Elements</span>
            <i class="menu-arrow"></i>
          </a>
          <div class="collapse" id="ui-basic">
            <ul class="nav flex-column sub-menu">
              <li class="nav-item">
                <a class="nav-link" href="#"
                  >Buttons</a
                >
              </li>
              <li class="nav-item">
                <a class="nav-link" href="#"
                  >Dropdowns</a
                >
              </li>
              <li class="nav-item">
                <a class="nav-link" href="#"
                  >Typography</a
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
    getActive: function(link) {
      if (this.$route.matched.some(({ name }) => name === link))
        return true;
      else
        return false;
    }
  }
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
