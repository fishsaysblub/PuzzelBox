<template>
  <div>
    <!-- NavBar -->
    <nav class="navbar p-0 fixed-top d-flex flex-row">
      <!-- Logo -->
      <div
        class="
          navbar-brand-wrapper
          d-flex d-lg-none
          align-items-center
          justify-content-center
        "
      >
        <router-link to="/">
          <a class="navbar-brand brand-logo-mini" href="#"
            ><img src="@/assets/images/logo-mini.svg" alt="logo"
          /></a>
        </router-link>
      </div>

      <!-- Header -->
      <div class="navbar-menu-wrapper flex-grow d-flex align-items-stretch">
        <button
          class="navbar-toggler navbar-toggler align-self-center"
          type="button"
          data-toggle="minimize"
        >
          <span class="mdi mdi-menu"></span>
        </button>

        <ul class="navbar-nav navbar-nav-right">
          <!-- Button -->
          <li class="nav-item d-none d-lg-block">
            <router-link to="/creategame"
              class="nav-link btn btn-success create-new-button"
              >+ Schedule new game</router-link
            >
          </li>

          <!-- Profile -->
          <li class="nav-item dropdown">
            <a
              class="nav-link"
              id="profileDropdown"
              href="#"
              data-toggle="dropdown"
            >
              <div class="navbar-profile">
                <img
                  class="img-xs rounded-circle"
                  src="@/assets/images/faces/face24.jpg"
                  alt=""
                />
                <p v-if="$store.state.user != null" class="mb-0 d-none d-sm-block navbar-profile-name">{{ $store.state.user.providerData[0].displayName }}</p>
                <i class="mdi mdi-menu-down d-none d-sm-block"></i>
              </div>
            </a>

            <!-- Profile dropdown items -->
            <div
              class="
                dropdown-menu dropdown-menu-right
                navbar-dropdown
                preview-list
              "
              aria-labelledby="profileDropdown"
            >
              <h6 class="p-3 mb-0">Profile</h6>
              <div class="dropdown-divider"></div>
              <!-- Settings button -->
              <a @click="settings()" class="dropdown-item preview-item">
                <div class="preview-thumbnail">
                  <div class="preview-icon bg-dark rounded-circle">
                    <i class="mdi mdi-settings text-success"></i>
                  </div>
                </div>
                <div class="preview-item-content">
                  <p class="preview-subject mb-1">Settings</p>
                </div>
              </a>
              <div class="dropdown-divider"></div>
              <!-- Logout button -->
              <a @click="logout()" class="dropdown-item preview-item">
                <div class="preview-thumbnail">
                  <div class="preview-icon bg-dark rounded-circle">
                    <i class="mdi mdi-logout text-danger"></i>
                  </div>
                </div>
                <div class="preview-item-content">
                  <p class="preview-subject mb-1">Log out</p>
                </div>
              </a>
            </div>
          </li>
        </ul>

        <!-- Mobile menu button -->
        <button
          class="
            navbar-toggler navbar-toggler-right
            d-lg-none
            align-self-center
          "
          type="button"
          data-toggle="offcanvas"
        >
          <span class="mdi mdi-format-line-spacing"></span>
        </button>
      </div>
    </nav>
  </div>
</template>

<script>
import { signOut } from "firebase/auth";
import { auth } from "../main.js";

export default {
  name: "TopNav",
  props: {},
  methods: {
    logout: function () {
      signOut(auth)
        .then(() => {
          console.log('Logged out');
          this.$router.push('/login');
        })
        .catch((error) => {
          console.log(error);
        });
    },
    settings: function () {
      this.$router.push('/settings');
    }
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
