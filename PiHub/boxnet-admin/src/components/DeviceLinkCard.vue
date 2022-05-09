<template>
  <div class="col-12 grid-margin">
    <div class="card linkCard" :class="{ linkCardDeleted: deleted }">
      <div class="card-body">
        <h5>
          <b class="p-2">Box Link</b>
          <button
            v-if="deleted == false && modify"
            @click="deleteLink()"
            class="btn btn-sm btn-danger"
          >
            Delete
          </button>
          <button
            v-if="deleted == true && modify"
            @click="undoDelete()"
            class="btn btn-sm btn-primary"
          >
            Undo
          </button>
        </h5>
        <div class="row">
          <!-- Box -->
          <div class="col-4 col-sm-12 col-xl-4 my-auto">
            <div class="d-flex d-sm-block d-md-flex align-items-center">
              <h2 class="mb-0">Puzzle Box</h2>
              <p
                class="ml-2 mb-0 font-weight-medium"
                :class="{ 'text-success': link.box_connected }"
              >
                {{ link.box_status }}
              </p>
            </div>
            <h6 class="text-muted font-weight-normal">{{ link.box_mac }}</h6>
          </div>
          <div class="col-1 col-sm-12 col-xl-1 text-center text-xl-right">
            <i class="icon-lg mdi mdi-cube-outline text-primary ml-auto"></i>
          </div>

          <!-- Devider -->
          <div class="col-1 col-sm-12 col-xl-1 text-center text-xl-right">
            <i
              class="icon-lg mdi mdi-arrow-left-right text-warning ml-auto"
            ></i>
          </div>
          <!-- Bomb -->
          <div class="col-4 col-sm-12 col-xl-4 my-auto">
            <div class="d-flex d-sm-block d-md-flex align-items-center">
              <h2 class="mb-0">Bomb</h2>
              <p
                class="ml-2 mb-0 font-weight-medium"
                :class="{ 'text-success': link.bomb_connected }"
              >
                {{ link.bomb_status }}
              </p>
            </div>
            <h6 class="text-muted font-weight-normal">{{ link.bomb_mac }}</h6>
          </div>
          <div class="col-1 col-sm-12 col-xl-1 text-center text-xl-right">
            <i class="icon-lg mdi mdi-bomb text-info ml-auto"></i>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import socket from "../socket/index.js";

export default {
  name: "LinkCard",
  methods: {
    deleteLink: function () {
      socket.get().emit("device_unlink_req", { mac: this.link.box_mac });
      this.deleted = true;
    },
    undoDelete: function () {
      socket.get().emit("device_link_req", {
        bomb_mac: this.link.bomb_mac,
        box_mac: this.link.box_mac,
      });
      this.deleted = false;
    },
  },
  props: {
    link: JSON,
    modify: Boolean,
  },
  data() {
    return {
      deleted: false,
    };
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.linkCard {
  background-color: #0f1015;
}

.linkCardDeleted {
  background-color: #3e1e1e !important;
}
h1,
h2,
h3,
h4,
h5 {
  color: white;
}
</style>
