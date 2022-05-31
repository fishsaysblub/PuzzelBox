<template>
  <div class="content-wrapper">
    <div class="page-header">
      <h3 class="page-title"><b>Game Schedule</b></h3>
      <nav aria-label="breadcrumb">
        <ol class="breadcrumb">
          <li class="breadcrumb-item">
            <router-link to="/"> Dashboard</router-link>
          </li>
          <li class="breadcrumb-item active" aria-current="page">
            Game-Schedule
          </li>
        </ol>
      </nav>
    </div>

    <div class="row">
      <div class="col-lg-12 grid-margin stretch-card"><router-link to="/creategame" class="btn btn-lg btn-success create-new-button">+ Schedule new game</router-link></div>
      <div class="col-lg-12 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title">Scheduled Games</h4>
            <p class="card-description">Scheduled Bomb - Box pairs</p>
            
            <div class="table-responsive">
              <table class="table">
                <thead>
                  <tr>
                    <th>Game-Type</th>
                    <th>Scheduled time</th>
                    <th>Bomb mac</th>
                    <th>Box mac</th>
                    <th>Identify</th>
                    <th>Delete</th>
                  </tr>
                </thead>
                <tbody>
                  <tr v-for="(game, key) in $store.state.gameList" v-bind:key="key">
                    <td>{{game.game_type}}</td>
                    <td>{{ game.start_time }}</td>
                    <td v-if="game.game_type == 'bomb-box'">{{game.device.bomb_mac}}</td>
                    <td v-if="game.game_type == 'bomb'">{{game.device.mac_address}}</td>
                    <td v-if="game.game_type == 'bomb'">-</td>
                    <td v-if="game.game_type == 'bomb-box'">{{game.device.box_mac}}</td>
                    <td v-if="game.game_type == 'box'">-</td>
                    <td v-if="game.game_type == 'box'">{{game.device.mac_address}}</td>
                    <td>
                      <button
                        v-if="game.game_type == 'bomb-box'"
                        class="btn btn-secondary"
                        @click="identify(game.device.bomb_mac, game.device.box_mac)"
                      >
                        I
                      </button>
                      <button
                        v-else
                        class="btn btn-secondary"
                        @click="identify(game.device.mac_address)"
                      >
                        I
                      </button>
                    </td>
                    <td>
                      <button
                        class="btn btn-danger mdi mdi-delete"
                        @click="deleteGame(key)"
                      >
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
</template>

<script>
import socket from "@/socket/index.js";

export default {
  name: "GameList",
  components: {},
  computed: {},
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
    deleteGame(uid) {
      socket.get().emit("game_delete_req", {uid: uid});
    }
  },
};
</script>
