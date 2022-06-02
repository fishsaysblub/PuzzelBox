import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import LoginView from '../views/LoginView.vue'
import DashView from '../views/DashView.vue'
import NetworkView from '../views/NetworkView.vue'
import SettingsBoxView from '../views/settings/SettingsBoxView.vue'
import SettingsBomView from '../views/settings/SettingsBomView.vue'
import SettingsListView from '../views/settings/SettingsListView.vue'
import GameListView from '../views/GameListView.vue'
import CreateGameView from '../views/CreateGameView.vue'
import DeviceLinkView from '../views/DeviceLinkView.vue'
import { firebaseapp } from '@/main.js'


const routes = [
  {
    path: '/',
    name: 'Dash',
    component: DashView,
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
    path: '/settings',
    name: 'SettingsList',
    component: SettingsListView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/settings/box/:mac',
    name: 'SettingsBox',
    component: SettingsBoxView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/settings/bom/:mac',
    name: 'SettingsBom',
    component: SettingsBomView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/gameschedule',
    name: 'GameList',
    component: GameListView,
    meta: {
      authRequired: true,
    }
  },
  {
    path: '/creategame',
    name: 'CreateGame',
    component: CreateGameView,
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
  },
  {
    path: '/:pathMatch(.*)*',
    redirect: '/',
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

router.beforeEach(async (to, from, next) => {
  if (!await firebaseapp.getCurrentUser() && to.meta.authRequired == true) {
    next({path: 'login'});
    return false;
  } else {
    next();
    return true;
  }
})

export default router
