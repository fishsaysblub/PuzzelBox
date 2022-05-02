<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Device link</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            Device-Linking
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
              Online Puzzle Boxes <code>online</code>
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
                  <tr
                    v-for="device in filteredBoxes"
                    :key="device.mac_address"
                    @click="selectBox(device.mac_address)"
                    :class="{ pairSelect: amSelected(device.mac_address) }"
                  >
                    <td>
                      {{ device.mac_address }}
                      <i
                        v-if="deviceLinked(device.mac_address)"
                        class="icon-sm mdi mdi-check text-success ml-auto p-2"
                      ></i>
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
            <p class="card-description">Online Bombs <code>online</code></p>
            <div class="table-responsive">
              <table class="table">
                <thead>
                  <tr>
                    <th><b>Mac Address</b></th>
                    <th><b>Identify</b></th>
                  </tr>
                </thead>
                <tbody>
                  <tr
                    v-for="device in filteredBombs"
                    :key="device.mac_address"
                    @click="selectBomb(device.mac_address)"
                    :class="{ pairSelect: amSelected(device.mac_address) }"
                  >
                    <td>
                      {{ device.mac_address }}
                      <i
                        v-if="deviceLinked(device.mac_address)"
                        class="icon-sm mdi mdi-check text-success ml-auto p-2"
                      ></i>
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
      <div class="col-lg-12 grid-margin stretch-card">
        <div class="card">
          <div class="card-body" v-if="bomb != null && boxe != null">
            <button
              class="btn btn-inverse-success btn-lg btn-block"
              @click="bindDevices()"
            >
              Connect Selected Devices
            </button>
          </div>
          <div class="card-body" v-else>
            <button class="btn btn-inverse-secondary btn-lg btn-block">
              Connect Selected Devices
            </button>
          </div>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-lg-12 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>Device Links</b></h4>
            <p class="card-description">Box -> Bomb links</p>
            <hr />
            <div class="row">
              <DeviceLinkCard
                v-for="link in $store.state.links"
                :key="link.box_mac"
                :link="getLink(link)"
              />
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import _ from "lodash";
import DeviceLinkCard from "@/components/DeviceLinkCard.vue";
import socket from '@/socket/index.js';

export default {
  name: "TestView",
  data() {
    return {
      bomb: null,
      boxe: null,
    };
  },
  components: {
    DeviceLinkCard,
  },
  methods: {
    identify: function (mac) {
      console.log("Identifying " + mac);
      socket.get().emit("device_ident_req", { mac: mac });
    },
    selectBox: function (mac) {
      this.boxe = mac;
    },
    selectBomb: function (mac) {
      this.bomb = mac;
    },
    amSelected: function (mac) {
      if (this.bomb == mac || this.boxe == mac) return true;
    },
    bindDevices: function () {
      if (this.bomb == null || this.boxe == null) {
        return;
      }
      socket.get().emit("device_link_req", {
        bomb_mac: this.bomb,
        box_mac: this.boxe,
      });
      this.bomb = null;
      this.boxe = null;
    },
    getLink: function (link) {
      let bombOnline = _.find(this.filteredBombs, function (bomb) {
        if (bomb.mac_address == link.bomb_mac) {
          return true;
        }
      });

      if (bombOnline != undefined) {
        link["bomb_status"] = "Connected";
        link["bomb_connected"] = true;
      } else {
        link["bomb_status"] = "Offline";
        link["bomb_connected"] = false;
      }

      let boxOnline = _.find(this.filteredBoxes, function (bomb) {
        if (bomb.mac_address == link.box_mac) {
          return true;
        }
      });

      if (boxOnline != undefined) {
        link["box_status"] = "Connected";
        link["box_connected"] = true;
      } else {
        link["box_status"] = "Offline";
        link["box_connected"] = false;
      }

      return link;
    },
    deviceLinked: function (mac) {
      let linked = _.find(this.$store.state.links, function (link) {
        if (link.bomb_mac == mac || link.box_mac == mac) return true;
      });

      return linked;
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
.pairSelect {
  background-color: #f8a719;
  color: #191c24;
}
</style>
