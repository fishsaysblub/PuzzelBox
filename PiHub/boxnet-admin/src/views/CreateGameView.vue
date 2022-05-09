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
            </form>
          </div>
        </div>
      </div>
      <div class="col-lg-2 grid-margin stretch-card">
        <button
          class="btn btn-lg create-new-button"
          @click="createGame()"
          :class="{ 'btn-success': selectedLink != null, 'btn-dark': selectedLink == null }"
        >
          <h4><b>Create Game</b></h4>
        </button>
      </div>
      <div class="col-lg-12 grid-margin stretch-card">
        <div class="card">
          <div class="card-body">
            <h4 class="card-title"><b>Select pair</b></h4>
            <p class="card-description">Box -> Bomb links</p>
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
      </div>
    </div>
  </div>
</template>

<script>
import DeviceLinkCard from "@/components/DeviceLinkCard.vue";
import socket from "@/socket/index.js";

export default {
  name: "CreateGame",
  components: {
    DeviceLinkCard,
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
    },
    createGame() {
      if (this.selectedLink == null) return;
      console.log("Creating game", this.startTime, this.selectedLink);
      // Todo: Send new game to socket
      this.$router.push("/gameschedule");
    },
  },
  data() {
    return {
      startTime: "",
      selectedLink: null,
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
