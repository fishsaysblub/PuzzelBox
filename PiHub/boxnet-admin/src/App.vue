<template>
  <div>
    <div class="container-scroller">
    <!-- Side NAV -->
    <SideNav />

    <div class="container-fluid page-body-wrapper">
      <!-- Top NAV -->
      <TopNav />
      
      <div class="main-panel">
        <!-- TestView -->
        <router-view /> 
      </div>
    </div>

  </div>

    
    <!-- <nav>
      <router-link to="/">Home</router-link> |
      <router-link to="/about">About</router-link>
    </nav>
    <router-view /> -->
  </div>
</template>

 <script>
    import TopNav from './components/TopNav.vue'
    import SideNav from './components/SideNav.vue'

    export default {
     name: 'app',
     components:{
        TopNav,
        SideNav
     }
    }
   </script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 30px;
}

nav a {
  font-weight: bold;
  color: #2c3e50;
}

nav a.router-link-exact-active {
  color: #42b983;
}
</style>
