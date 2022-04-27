import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import LoginView from '../views/LoginView.vue'
import TestView from '../views/TestView.vue'
import NetworkView from '../views/NetworkView.vue'
import DeviceLinkView from '../views/DeviceLinkView.vue'
import Store from '@/store/index.js'


const routes = [
  {
    path: '/',
    name: 'Dash',
    component: TestView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/network',
    name: 'Network',
    component: NetworkView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/devicelink',
    name: 'Link',
    component: DeviceLinkView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/home',
    name: 'home',
    component: HomeView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/login',
    name: 'Login',
    component: LoginView,
    meta: {
      authRequired: false,
    }
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

router.beforeEach((to, from, next) => {
  if (Store.state.user == null && to.meta.authRequired == true) {
    next({path: 'login'});
    return false;
  } else {
    console.log("Routing from: ", from, " to: ", to, Store.state.user);
    next();
    return true;
  }
})

export default router
