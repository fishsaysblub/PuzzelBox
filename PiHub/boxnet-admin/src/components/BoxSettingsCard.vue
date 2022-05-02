<template>
  <div class="row">
    <div class="col-md-12 grid-margin stretch-card">
      <div class="card">
        <div class="card-body">
          <h4 class="card-title">Default form</h4>
          <p class="card-description">Basic form layout</p>
          <form class="forms-sample">
            <div class="form-group">
              <label for="exampleInputUsername1">Username</label>
              <input
                type="text"
                class="form-control"
                id="exampleInputUsername1"
                placeholder="Username"
              />
            </div>
            <div class="form-group">
              <label for="exampleInputEmail1">Email address</label>
              <input
                type="email"
                class="form-control"
                id="exampleInputEmail1"
                placeholder="Email"
              />
            </div>
            <div class="form-group">
              <label for="exampleInputPassword1">Password</label>
              <input
                type="password"
                class="form-control"
                id="exampleInputPassword1"
                placeholder="Password"
              />
            </div>
            <div class="form-group">
              <label for="exampleInputConfirmPassword1">Confirm Password</label>
              <input
                type="password"
                class="form-control"
                id="exampleInputConfirmPassword1"
                placeholder="Password"
              />
            </div>
            <div class="form-check form-check-flat form-check-primary">
              <label class="form-check-label">
                <input type="checkbox" class="form-check-input" /> Remember me
                <i class="input-helper"></i
              ></label>
            </div>
            <button type="submit" class="btn btn-primary mr-2">Submit</button>
            <button class="btn btn-dark">Cancel</button>
          </form>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
// import socket from '../socket/index.js';

export default {
  name: "BoxSettingsCard",
  methods: {},
  props: {
    mac: String,
  },
  data() {
    return {};
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
