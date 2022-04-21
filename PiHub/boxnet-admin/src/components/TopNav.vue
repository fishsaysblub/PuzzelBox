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
            ><img src="assets/images/logo-mini.svg" alt="logo"
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
          <li class="nav-item dropdown d-none d-lg-block">
            <a
              class="nav-link btn btn-success create-new-button"
              id="createbuttonDropdown"
              data-toggle="dropdown"
              aria-expanded="false"
              href="#"
              >+ Button</a
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
                  src="assets/images/faces/face15.jpg"
                  alt=""
                />
                <p class="mb-0 d-none d-sm-block navbar-profile-name">Admin</p>
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
              <a class="dropdown-item preview-item">
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
              <a class="dropdown-item preview-item">
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
export default {
  name: "TopNav",
  props: {},
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>
