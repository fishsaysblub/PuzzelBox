<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Create Game</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item">
            <router-link to="/gameschedule"> Game-Schedule</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            Create-Game
          </li>
        </ol>
      </nav>
    </div>

    <div class="row">
      <div class="col-lg-10 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>Set start time</b></h4>
            <p class="card-description">Time to start the game</p>
            <form class="forms-sample" onsubmit="return false">
              <!-- Game Start -->
              <div class="form-group">
                <label for="bombGameLen">Start time</label>
                <input
                  type="datetime-local"
                  :min="today"
                  v-model="startTime"
                  class="form-control"
                  required
                />
              </div>

              <div class="form-group row">
                <label class="col-sm-12 col-form-label">GameType <code>{{gameType}}</code></label>
                <div class="col-sm-4">
                  <div class="form-check">
                    <label class="form-check-label">
                      <input
                        type="radio"
                        class="form-check-input"
                        name="membershipRadios"
                        v-model="gameType"
                        id="gameType1"
                        value="bomb-box"
                        checked />
                      Bomb & Box <i class="input-helper"></i
                    ></label>
                  </div>
                </div>
                <div class="col-sm-4">
                  <div class="form-check">
                    <label class="form-check-label">
                      <input
                        type="radio"
                        class="form-check-input"
                        name="membershipRadios"
                        v-model="gameType"
                        id="gameType2"
                        value="bomb" />
                      Bomb Only <i class="input-helper"></i
                    ></label>
                  </div>
                </div>
                <div class="col-sm-4">
                  <div class="form-check">
                    <label class="form-check-label">
                      <input
                        type="radio"
                        class="form-check-input"
                        name="membershipRadios"
                        v-model="gameType"
                        id="gameType3"
                        value="box" />
                      Box Only <i class="input-helper"></i
                    ></label>
                  </div>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
      <div class="col-lg-2 grid-margin stretch-card">
        <button
          class="btn btn-lg create-new-button"
          @click="createGame()"
          :class="{
            'btn-success': (selectedLink != null && gameType == 'bomb-box') || (selectedBomb != null  && gameType == 'bomb') || (selectedBox != null  && gameType == 'box'),
            'btn-dark': (selectedLink == null && gameType == 'bomb-box') || (selectedBomb == null  && gameType == 'bomb') || (selectedBox == null  && gameType == 'box'),
          }"
        >
          <h4><b>Create Game</b></h4>
        </button>
      </div>

      <div class="col-lg-12 grid-margin stretch-card">
        <!-- Bomb-Box game -->
        <div class="card" v-if="gameType == 'bomb-box'">
          <div class="card-body">
            <h4 class="card-title"><b>Select pair</b></h4>
            <p class="card-description">
              Box -> Bomb links <code>Click to select and identify</code>
            </p>
            <hr />
            <div class="row">
              <DeviceLinkCard
                v-for="link in $store.state.links"
                :key="link.box_mac"
                :link="link"
                @click="selectPair(link)"
                :class="{ activeLink: selectedLink == link }"
              />
            </div>
          </div>
        </div>

        <!-- Bomb game -->
        <div class="card" v-if="gameType == 'bomb'">
          <div class="card-body">
            <h4 class="card-title"><b>Select Bomb</b></h4>
            <p class="card-description">
              Bombs <code>Click to select and identify</code>
            </p>
            <hr />
            <div class="row">
              <DeviceCard
                v-for="bomb in filteredBombs"
                :key="bomb.mac_address"
                :link="bomb"
                @click="selectBomb(bomb)"
                :class="{ activeLink: selectedBomb == bomb }"
                class="col-12"
              />
            </div>
          </div>
        </div>

        <!-- Box game -->
        <div class="card" v-if="gameType == 'box'">
          <div class="card-body">
            <h4 class="card-title"><b>Select Box</b></h4>
            <p class="card-description">
              Boxes <code>Click to select and identify</code>
            </p>
            <hr />
            <div class="row">
              <DeviceCard
                v-for="box in filteredBoxes"
                :key="box.mac_address"
                :link="box"
                @click="selectBox(box)"
                :class="{ activeLink: selectedBox == box }"
                class="col-12"
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
import DeviceCard from "@/components/DeviceCard.vue";
import socket from "@/socket/index.js";
import { v4 as uuidv4 } from 'uuid';

export default {
  name: "CreateGame",
  components: {
    DeviceLinkCard,
    DeviceCard,
  },
  created() {
    this.startTime = this.today;
  },
  computed: {
    today() {
      let date = new Date();

      let year = date.getFullYear();
      let month = ("00" + (date.getMonth() + 1)).slice(-2);
      let day = ("00" + date.getDate()).slice(-2);
      let time =
        ("00" + date.getHours()).slice(-2) +
        ":" +
        ("00" + date.getMinutes()).slice(-2);
      let now = year + "-" + month + "-" + day + "T" + time;
      return now;
    },
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
  methods: {
    identify: function (bombMac, boxMac) {
      console.log("Identifying ", bombMac, boxMac);
      socket.get().emit("device_ident_req", { mac: bombMac });
      socket.get().emit("device_ident_req", { mac: boxMac });
    },
    startingTimestamp(time) {
      const dtFormat = new Intl.DateTimeFormat("en-GB", {
        timeStyle: "short",
        dateStyle: "long",
        timeZone: "CET",
      });
      return dtFormat.format(new Date(time * 1e3));
    },
    selectPair(link) {
      this.selectedLink = link;
      this.identify(link.bomb_mac, link.box_mac);
    },
    selectBox(box) {
      this.selectedBox = box;
      socket.get().emit("device_ident_req", { mac: box.mac_address });
    },
    selectBomb(bomb) {
      this.selectedBomb = bomb;
      socket.get().emit("device_ident_req", { mac: bomb.mac_address });
    },
    createGame() {
      if (this.selectedLink != null && this.gameType == "bomb-box") {
        socket.get().emit("game_create_req", {
           uid: uuidv4(),
           game: {
             game_type: this.gameType,
             start_time: this.startTime,
             device: this.selectedLink
           } 
          });
        console.log("Creating game Bomb Box", this.startTime, this.selectedLink);
      } else if (this.selectBox != null && this.gameType == "box") {
        socket.get().emit("game_create_req", {
           uid: uuidv4(),
           game: {
             game_type: this.gameType,
             start_time: this.startTime,
             device: this.selectedBox
           } 
          });
        console.log("Creating game Box Only", this.startTime, this.selectedBox);
      } else if (this.selectBomb != null && this.gameType == "bomb") {
        socket.get().emit("game_create_req", {
           uid: uuidv4(),
           game: {
             game_type: this.gameType,
             start_time: this.startTime,
             device: this.selectedBomb
           } 
          });
        console.log("Creating game Bomb Only", this.startTime, this.selectedBomb);
      } else {
        return;
      }
      // Todo: Send new game to socket
      this.$router.push("/gameschedule");
    },
  },
  data() {
    return {
      startTime: "",
      selectedLink: null,
      selectedBomb: null,
      selectedBox: null,
      gameType: "bomb-box",
    };
  },
};
</script>

<style scoped>
.activeLink {
  background: #00d25b;
  border-radius: 4px;
}
</style>
