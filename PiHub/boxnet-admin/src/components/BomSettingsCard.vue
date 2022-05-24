<template>
  <div class="row">
    <div class="col-md-12 grid-margin stretch-card">
      <div class="card">
        <div class="card-body">
          <h4 class="card-title">Bomb settings</h4>
          <p class="card-description">
            Settings for bomb: <code>{{ mac }}</code>
          </p>
          <form class="forms-sample" onsubmit="return false">
            <!-- Game length -->
            <div class="form-group">
              <label for="bombGameLen"
                >Countdown length
                <small class="text-success">Default 1:30</small></label
              >
              <input
                type="time"
                min="00:00"
                max="05:00"
                v-model="settings.countdown_len"
                class="form-control"
                id="bombGameLen"
                placeholder="length"
                required
              />
            </div>

            <!-- Ammount of codes -->
            <div class="form-group">
              <label for="bombCodeCount"
                >Bomb defusion code count
                <small class="text-success">Default 5</small></label
              >
              <input
                type="number"
                min="1"
                max="20"
                v-model="settings.code_count"
                class="form-control"
                id="bombCodeCount"
                placeholder="Amount of codes"
                required
              />
            </div>

            <!-- Wire cut settings -->
            <div class="form-group">
              <label for="bombWireCuts"
                >Wire cut settings
                <small class="text-danger"> Remove time </small> -
                <small class="text-success"> Add time</small></label
              >
              <div class="row" id="bombWireCuts">
                <div class="col-2">
                  <p>Wire 1</p>
                </div>
                <label class="container col-9">
                  <input
                    type="checkbox"
                    id="wire1"
                    value="w1"
                    v-model="settings.wire_cuts"
                  />
                  <span class="wire"></span>
                </label>
                <div class="col-2">
                  <p>Wire 2</p>
                </div>
                <label class="container col-9">
                  <input
                    type="checkbox"
                    id="wire2"
                    value="w2"
                    v-model="settings.wire_cuts"
                  />
                  <span class="wire"></span>
                </label>
                <div class="col-2">
                  <p>Wire 3</p>
                </div>
                <label class="container col-9">
                  <input
                    type="checkbox"
                    id="wire3"
                    value="w3"
                    v-model="settings.wire_cuts"
                  />
                  <span class="wire"></span>
                </label>
                <div class="col-2">
                  <p>Wire 4</p>
                </div>
                <label class="container col-9">
                  <input
                    type="checkbox"
                    id="wire4"
                    value="w4"
                    v-model="settings.wire_cuts"
                  />
                  <span class="wire"></span>
                </label>
              </div>
            </div>

            <!-- Keypad settings -->
            <div class="form-group">
              <label for="bombKeypadLinks"
                >Keypad wire links
                <small class="text-success">Draggable</small></label
              >
              <div class="row pl-2 pr-2">
                <div class="col-3">
                  <div class="jumerBase">Key 1</div>
                  <div class="jumerBase">Key 2</div>
                  <div class="jumerBase">Key 3</div>
                  <div class="jumerBase">Key 4</div>
                  <div class="jumerBase">Key 5</div>
                  <div class="jumerBase">Key 6</div>
                  <div class="jumerBase">Key 7</div>
                  <div class="jumerBase">Key 8</div>
                </div>
                <div class="col-9">
                  <Container @drop="onDrop" drag-class="drag-hover">
                    <Draggable v-for="item in settings.wire_links" :key="item.id">
                      <div class="jumerBase drag draggable-item">
                        {{ item.data }}
                      </div>
                    </Draggable>
                  </Container>
                </div>
              </div>
            </div>
            <hr />
            <button @click="onSave()" class="btn btn-primary mr-2">
              Save to Bomb
            </button>
            <button @click="onSaveAll()" class="btn btn-dark mr-2">
              Save to <b>All</b> Bombs
            </button>
          </form>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import _ from "lodash";
import { Container, Draggable } from "vue-dndrop";
import socket from '../socket/index.js';

export default {
  name: "BoxSettingsCard",
  components: { Container, Draggable },
  created() {
    console.log("Created", this.$store.state.bombSettings);
    socket.get().emit("bomb_settings_req", { mac: this.mac});
  },
  methods: {
    applyDrag: function (arr, dragResult) {
      const { removedIndex, addedIndex, payload } = dragResult;
      if (removedIndex === null && addedIndex === null) return arr;

      const result = [...arr];
      let itemToAdd = payload;

      if (removedIndex !== null) {
        itemToAdd = result.splice(removedIndex, 1)[0];
      }

      if (addedIndex !== null) {
        result.splice(addedIndex, 0, itemToAdd);
      }

      return result;
    },
    onDrop(dropResult) {
      this.settings.wire_links = this.applyDrag(this.settings.wire_links, dropResult);
    },
    onSave() {
      this.$store.commit('saveBombSettings', this.settings);
      socket.get().emit("bomb_settings_save", { mac: this.mac, settings: this.settings});
    },
    onSaveAll() {
      this.$store.commit('saveBombSettings', this.settings);
      this.filteredBombs.forEach(bomb => {
        socket.get().emit("bomb_settings_save", { mac: bomb.mac_address, settings: this.settings});
      });
      
    },
  },
  props: {
    mac: String,
  },
  watch: {
    "$store.state.bombSettings": {
      handler: function(newVal) {
        this.settings = newVal;
      },
      deep: true,
    },
  },
  computed: {
    filteredBombs: function () {
      return _.filter(this.$store.state.devices, function (device) {
        return device.device_name == "Bomb";
      });
    },
  },
  data() {
    return {
      settings: {
        countdown_len: "01:30",
        code_count: 5,
        wire_cuts: [],
        wire_links: [
          { id: 0, data: "A" },
          { id: 1, data: "B" },
          { id: 2, data: "C" },
          { id: 3, data: "D" },
          { id: 4, data: "E" },
          { id: 5, data: "F" },
          { id: 6, data: "G" },
          { id: 7, data: "H" },
        ],
      },
    };
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
/* Customize the label (the container) */
.container {
  display: block;
  position: relative;
  padding-left: 35px;
  margin-bottom: 12px;
  cursor: pointer;
  font-size: 22px;
  -webkit-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}

/* Hide the browser's default checkbox */
.container input {
  position: absolute;
  opacity: 0;
  cursor: pointer;
  height: 0;
  width: 0;
}

/* Create a custom checkbox */
.wire {
  position: absolute;
  top: 0;
  left: 0;
  height: 15px;
  width: 100%;
  background-color: rgb(236, 54, 54);
}

/* On mouse-over, add a grey background color */
.container:hover input ~ .wire {
  background-color: rgb(201, 255, 196);
}

/* When the checkbox is checked, add a blue background */
.container input:checked ~ .wire {
  background-color: #53ff5c;
}

/* Create the checkmark/indicator (hidden when not checked) */
.checkmark:after {
  content: "";
  position: absolute;
  display: none;
}

/* Show the checkmark when checked */
.container input:checked ~ .wire:after {
  display: block;
}

/* Style the checkmark/indicator */
.container .wire:after {
  left: 9px;
  top: 5px;
  width: 5px;
  height: 10px;
  border: solid white;
  border-width: 0 3px 3px 0;
  -webkit-transform: rotate(45deg);
  -ms-transform: rotate(45deg);
  transform: rotate(45deg);
}
</style>

<style scoped>
.jumerBase {
  width: 100%;
  border-radius: 3px;
  height: 25px;
  margin-top: 5px;
}

.drag {
  text-align: center;
  border: 1px solid #a1a3a5;
  cursor: move;
}

.drop {
  background: #56c960;
}

.drag-hover {
  background: #2a3038;
}
</style>