import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import TestView from '../views/TestView.vue'
import NetworkView from '../views/NetworkView.vue'
import DeviceLinkView from '../views/DeviceLinkView.vue'

const routes = [
  {
    path: '/',
    name: 'Dash',
    component: TestView
  },
  {
    path: '/network',
    name: 'Network',
    component: NetworkView
  },
  {
    path: '/devicelink',
    name: 'Link',
    component: DeviceLinkView
  },
  {
    path: '/home',
    name: 'home',
    component: HomeView
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
