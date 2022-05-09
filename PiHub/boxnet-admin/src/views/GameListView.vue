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
                    <th>Scheduled time</th>
                    <th>State</th>
                    <th>Bomb mac</th>
                    <th>Box mac</th>
                    <th>Identify</th>
                  </tr>
                </thead>
                <tbody>
                  <tr>
                    <td>{{ startingTimestamp(1652094947) }}</td>
                    <td><label class="badge badge-danger">Pending</label></td>
                    <td>bom mac</td>
                    <td>box mac</td>
                    <td>
                      <button
                        class="btn btn-secondary"
                        @click="identify('bom', 'box')"
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
  },
};
</script>
