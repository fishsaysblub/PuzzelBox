<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title">Bomb settings <p>Mac: <code class="text-success">{{ $route.params.mac }}</code></p></h3>
      
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

    <!-- Image -->
    <div class="row">
      <img class="col-7 boxImage" src="@/assets/images/bom.png" alt="test">
    </div>
    
    <div class="row justify-content-end">
      <div class="col-5">
        <BomSettingsCard :mac="$route.params.mac" />
      </div>
    </div>
    
  </div>
  <!-- partial -->
</template>

<script>
import BomSettingsCard from "@/components/BomSettingsCard.vue";

export default {
  name: "BomSettingsView",
  components: {
    BomSettingsCard,
  },
  methods: {},
};
</script>

<style scoped>
.boxImage {
  position: absolute;
  max-height: 100%;
  resize: horizontal;
  overflow: auto;

}
</style>
