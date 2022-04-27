<template>
  <div class="container-scroller">
    <div class="container-fluid page-body-wrapper full-page-wrapper">
      <div class="row w-100 m-0">
        <div
          class="
            content-wrapper
            full-page-wrapper
            d-flex
            align-items-center
            auth
            login-bg
          "
        >
          <div class="card col-lg-4 mx-auto">
            <div class="card-body px-5 py-5">
              <h3 class="card-title text-left mb-3">Login</h3>
              <!-- <form> -->
              <div class="form-group">
                <label>Email *</label>
                <input
                  type="text"
                  class="form-control p_input"
                  v-model="email"
                />
              </div>
              <div class="form-group">
                <label>Password *</label>
                <input
                  type="password"
                  class="form-control p_input"
                  v-model="password"
                />
              </div>
              <div
                class="
                  form-group
                  d-flex
                  align-items-center
                  justify-content-between
                "
              >
                <a href="#" class="forgot-pass">Forgot password</a>
              </div>
              <div class="text-center">
                <button
                  class="btn btn-primary btn-block enter-btn"
                  @click="login()"
                >
                  Login
                </button>
              </div>
              <p class="sign-up">
                Don't have an Account?<a href="#"> Sign Up</a>
              </p>
              <!-- </form> -->
            </div>
          </div>
        </div>
        <!-- content-wrapper ends -->
      </div>
      <!-- row ends -->
    </div>
    <!-- page-body-wrapper ends -->
  </div>
</template>

<script>
import { signInWithEmailAndPassword } from "firebase/auth";
import { auth } from "../main.js";

export default {
  name: "TestView",
  components: {},
  methods: {
    login: function () {
      console.log(this.email);
      signInWithEmailAndPassword (auth, this.email, this.password)
        .then((data) => {
          console.log("Successfully Logged In!", data);
          this.$router.push('/') // redirect to Dash
        })
        .catch((error) => {
          switch (error.code) {
            case 'auth/user-not-found':
              alert(error.message);
              break;
            case 'auth/wrong-password':
              alert(error.message);
              break;
            default:
              break;
          }
          console.log(error.code);
        });
    },
  },
  data() {
    return {
      email: "",
      password: "",
    };
  },
};
</script>
