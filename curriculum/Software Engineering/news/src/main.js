import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import Axios from 'axios'
import Vant from 'vant'
import 'vant/lib/index.css'
import 'lib-flexible'
import { Radio } from 'mint-ui'
// import 'mint-ui/lib/style.css' 已局部引入
import './mock/mock.js'
import { getDateTime, transTime, transNumber } from './assets/my.js'
import './icons'
import echarts from 'echarts'
import draggable from 'vuedraggable'

Vue.config.productionTip = false
Vue.use(store)
Vue.use(Vant)

// Vue.use(Radio) 不可用
Vue.component(Radio.name, Radio)
Vue.prototype.$axios = Axios
Vue.prototype.$echarts = echarts
Vue.prototype.$getDateTime = getDateTime
Vue.prototype.$transTime = transTime
Vue.prototype.$transNumber = transNumber
Vue.component(draggable.name, draggable)
new Vue({
  router,
  store,
  render: h => h(App),
  created () {
    // 获取字体大小设定
    if (localStorage.getItem('fontSize') === null) {
      localStorage.setItem('fontSize', 'medium')
    } else {
      this.$store.commit('setFontSize', localStorage.getItem('fontSize'))
    }
    // 获取主题色设定
    if (localStorage.getItem('themeColor') === null) {
      localStorage.setItem('themeColor', 'default')
    } else {
      this.$store.commit('setThemeColor', localStorage.getItem('themeColor'))
    }
    // 获取日夜间模式设定
    if (localStorage.getItem('darkMode') === null) {
      localStorage.setItem('darkMode', 0)
    } else {
      if (Number(localStorage.getItem('darkMode')) === 1) {
        this.$store.commit('setDarkMode', true)
      } else {
        this.$store.commit('setDarkMode', false)
      }
    }
    // 获取省流量模式设定
    if (localStorage.getItem('noPicMode') === null) {
      localStorage.setItem('noPicMode', 0)
    } else {
      if (Number(localStorage.getItem('noPicMode')) === 1) {
        this.$store.commit('setNoPicMode', true)
      } else {
        this.$store.commit('setNoPicMode', false)
      }
    }
  },
  mounted () {
    const state = this.$store.state
    // 设置主题色
    if (state.darkMode === false) {
      document.body.setAttribute('data-theme', state.themeColor)
    } else {
      document.body.setAttribute('data-theme', 'dark')
    }
    // 设置字体大小
    document.body.setAttribute('data-size', state.fontSize)
  }
}).$mount('#app')

/*
 * render: h => h(app)是缩写:
 * render: function(createElement) {
 *    returnr createElement(App)
 * }
 */
