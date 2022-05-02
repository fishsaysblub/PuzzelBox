<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Bomb settings</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            <router-link to="/settings"> Device-Settings</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            Bomb-Settings
          </li>
        </ol>
      </nav>
    </div>

    <p>{{ $route.params.mac }}</p>
  </div>
  <!-- partial -->
</template>

<script>
export default {
  name: "SettingsView",
  components: {},
  methods: {},
};
</script>
