<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Device settings</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            Device-Settings
          </li>
        </ol>
      </nav>
    </div>

    <div class="row">
      <div class="col-lg-6 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>PuzzleBoxes</b></h4>
            <p class="card-description">
              Online Puzzle Boxes <code>Click To Edit</code>
            </p>
            <div class="table-responsive">
              <table class="table">
                <thead>
                  <tr>
                    <th><b>Mac Address</b></th>
                    <th><b>Identify</b></th>
                  </tr>
                </thead>
                <tbody>
                  <tr v-for="device in filteredBoxes" :key="device.mac_address">
                    <td
                      @click="selectBox(device.mac_address)"
                      style="cursor: pointer"
                    >
                      {{ device.mac_address }}
                    </td>
                    <td>
                      <button
                        class="btn btn-secondary"
                        @click="identify(device.mac_address)"
                      >
                        I
                      </button>
                    </td>
                  </tr>
                </tbody>
              </table>
            </div>
          </div>
        </div>
      </div>
      <div class="col-lg-6 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>Bombs</b></h4>
            <p class="card-description">
              Online Bombs <code>Click To Edit</code>
            </p>
            <div class="table-responsive">
              <table class="table">
                <thead>
                  <tr>
                    <th><b>Mac Address</b></th>
                    <th><b>Identify</b></th>
                  </tr>
                </thead>
                <tbody>
                  <tr v-for="device in filteredBombs" :key="device.mac_address">
                    <td
                      @click="selectBomb(device.mac_address)"
                      style="cursor: pointer"
                    >
                      {{ device.mac_address }}
                    </td>
                    <td>
                      <button
                        class="btn btn-secondary"
                        @click="identify(device.mac_address)"
                      >
                        I
                      </button>
                    </td>
                  </tr>
                </tbody>
              </table>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <!-- partial -->
</template>

<script>
import _ from "lodash";
import socket from "@/socket/index.js";

export default {
  name: "SettingsListView",
  components: {},
  methods: {
    identify: function (mac) {
      console.log("Identifying " + mac);
      socket.get().emit("device_ident_req", { mac: mac });
    },
    selectBox: function (mac) {
      console.log("Box: ", mac);
      this.$router.push("/settings/box/" + mac);
    },
    selectBomb: function (mac) {
      console.log("Bomb: ", mac);
      this.$router.push("/settings/bom/" + mac);
    },
  },
  computed: {
    orderedDevices: function () {
      return _.orderBy(this.$store.state.devices, "device_name");
    },
    filteredBombs: function () {
      return _.filter(this.$store.state.devices, function (device) {
        return device.device_name == "Bomb";
      });
    },
    filteredBoxes: function () {
      return _.filter(this.$store.state.devices, function (device) {
        return device.device_name == "PuzzleBox";
      });
    },
  },
};
</script>

<style scoped>
tr:hover {
  background: #f8a719;
}
</style>
