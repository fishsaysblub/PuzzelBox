<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Network</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">Network</li>
        </ol>
      </nav>
    </div>
    <div class="row">
      <div class="col-lg-12 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>Device Table</b></h4>
            <p class="card-description">
              Connected devices within network <code>online</code>
            </p>
            <div class="table-responsive">
              <table class="table">
                <thead>
                  <tr>
                    <th><b>Device</b></th>
                    <th><b>SID</b></th>
                    <th><b>Mac Address</b></th>
                    <th><b>Identify</b></th>
                    <th><b>Status</b></th>
                  </tr>
                </thead>
                <tbody>
                  <tr
                    v-for="device in orderedDevices"
                    :key="device.mac_address"
                  >
                    <td>{{ device.device_name }}</td>
                    <td>{{ device.sid }}</td>
                    <td>{{ device.mac_address }}</td>
                    <td><button class="btn btn-secondary"  @click="identify(device.mac_address)">I</button></td>

                    <td>
                      <label
                        class="badge badge-danger"
                        v-if="device.device_status == 'Error'"
                        >{{ device.device_status }}</label
                      >
                      <label
                        class="badge badge-warning"
                        v-if="device.device_status == 'Idle'"
                        >{{ device.device_status }}</label
                      >
                      <label
                        class="badge badge-success"
                        v-if="device.device_status == 'InGame'"
                        >{{ device.device_status }}</label
                      >
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
import _ from 'lodash';
import socket from '../socket/index.js';

export default {
  name: "TestView",
  components: {},
  methods: {
    identify: function(mac) {
      console.log("Identifying " + mac);
      socket.get().emit("device_ident_req", { mac: mac });
    }
  },
  computed: {
    orderedDevices: function() {
      return _.orderBy(this.$store.state.devices, 'device_name' );
    },
    filteredBombs: function() {
      return _.filter(this.$store.state.devices,
      function(device) {
        return device.device_name == 'Bomb';
      });
    },
    filteredBoxes: function() {
      return _.filter(this.$store.state.devices,
      function(device) {
        return device.device_name == 'PuzzleBox';
      });
    }
  }
};
</script>
