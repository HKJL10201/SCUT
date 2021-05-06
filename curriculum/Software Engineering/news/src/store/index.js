import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    fontSize: 'medium', // 字体大小
    themeColor: 'default', // 主题色
    darkMode: false,
    noPicMode: false, // 省流量模式
    useSr: {
      username: 'test123',
      nickname: '刺客567',
      email: '94812104@qq.com',
      profile: '../assets/profile.jpg',
      gender: '男',
      signature: '云云云'
    },
    tmpNewsImage: '',
    user: null
  },
  mutations: {
    increment () {
    },
    // 设置用户id
    setUserId (state, userId) {
      state.userId = userId
    },
    // 设置字体大小
    setFontSize (state, fontSize) {
      state.fontSize = fontSize
    },
    // 设置主题色
    setThemeColor (state, themeColor) {
      state.themeColor = themeColor
    },
    // 设置夜间模式
    setDarkMode (state, darkMode) {
      state.darkMode = darkMode
    },
    // 设置省流量模式
    setNoPicMode (state, noPicMode) {
      state.noPicMode = noPicMode
    },
    // 登录——获取用户全部信息
    loginUser (state, user) {
      state.user = user
      // if (state.user.profile === null || state.user.profile === '') {
      // state.user.profile = 'data:image/png;base64,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'
      // }
    },
    // 注销——清除用户信息
    logoutUser (state) {
      state.user = null
    },
    // 修改用户头像
    setUserProfile (state, profile) {
      state.user.profile = profile
    },
    // 修改用户其他信息
    setUserOtherInfo (state, otherInfo) {
      state.user.nickname = otherInfo.nickname
      state.user.signature = otherInfo.signature
      state.user.gender = otherInfo.gender
      state.user.email = otherInfo.email
    },
    // 暂存新闻封面图片
    setTmpNewsImage (state, imageUrl) {
      state.tmpNewsImage = imageUrl
    },
    // 设置密保问题
    setPasswordQuiz (state, question) {
      state.quiz = question
    }
  },
  getters: {
    ifLogin: state => {
      if (state.user !== null && state.user !== '') {
        return true
      } else {
        return false
      }
    }
  },
  actions: {
  },
  modules: {
  }
})
