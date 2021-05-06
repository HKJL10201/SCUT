<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()"/>
          </div>
        <span>登入页面</span>
      </div>
    </div>
    <!--笑脸-->
    <div class="smile">
      <van-icon name="smile-o" />
      <div>请登入</div>
    </div>
    <!--账号-->
    <div class="alter-item">
      <div class="word">账号</div>
      <!-- <van-field v-model="inputUsername" placeholder="账号或邮箱" /> -->
      <input v-model="inputUsername" placeholder="账号或邮箱" />
    </div>
    <!--密码-->
    <div class="alter-item">
      <div class="word">密码</div>
      <!-- <van-field v-model="inputPassword" type="password" placeholder="不要输错噢" /> -->
      <input v-model="inputPassword" placeholder="不要输错噢" v-show="showPass"/>
      <input v-model="inputPassword" type="password" placeholder="不要输错噢"  v-show="!showPass"/>
      <div @click="showPass = !showPass">
        <svg-icon icon-class="show_password" class="if-show-password" v-show="showPass"/>
        <svg-icon icon-class="hide_password" class="if-show-password" v-show="!showPass"/>
      </div>
    </div>
    <!--忘记密码-->
    <router-link to="/forget_password/">
      <div id="forget-password">忘记密码</div>
    </router-link>
    <!--登入与注册按钮-->
    <div class="buttons">
      <van-button id="sign" color="#7BD58F" @click="clickLogin">登入</van-button>
      <router-link to="/register">
        <van-button id="regi" color="#969E97">注册</van-button>
      </router-link>
    </div>
  </div>
</template>

<script>
export default {
  name: 'loginPage',
  components: {},
  data () {
    return {
      inputUsername: '',
      inputPassword: '',
      showPass: false
    }
  },
  methods: {
    // 点击登录按钮
    clickLogin () {
      // 用户名正则匹配
      const checkUsername = /^[a-zA-Z0-9_-]{4,16}$/
      // 邮箱格式正则匹配
      const checkEmail = /^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$/
      if (!checkUsername.test(this.inputUsername) && !checkEmail.test(this.inputUsername)) { //
        this.$toast('用户名/邮箱的格式或长度错误!')
        return
      }
      // 密码长度限制
      if (this.inputPassword.length < 6 || this.inputPassword.length > 16) {
        this.$toast('密码长度为6~16!')
        return
      }
      if (checkEmail.test(this.inputUsername)) { // 邮箱登录
        this.loginByEmail()
      } else { // 用户名登录
        this.loginByUsername()
      }
    },
    // 用户名登录
    loginByUsername () {
      // console.log('用户名登录')
      this.$axios.post('https://afs7hx.toutiao15.com/loginByUn', {
        username: this.inputUsername,
        password: this.inputPassword
      }).then(response => {
        // console.log(response)
        if (response.status === 200) { // 服务器请求成功
          const res = response.data
          if (res.code === 1) {
            this.$toast('登录成功')
            // 登录成功，用户信息存入state
            console.log(res.data)
            const userInfo = {
              username: res.data.username,
              nickname: res.data.nickname,
              gender: res.data.gender,
              signature: res.data.signature,
              profile: res.data.profile,
              email: res.data.email,
              quiz: res.data.quiz.question
            }
            console.log(userInfo)
            this.$store.commit('loginUser', userInfo)
            this.redirectLastPage() // 页面跳转
          } else { // 登录失败
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 邮箱登录
    loginByEmail () {
      console.log('邮箱登录')
      const user = {
        userS: {
          username: 123123213,
          nickname: '刺客567',
          email: '94812104@qq.com',
          profile: '../assets/profile.jpg',
          gender: '男',
          signature: '云云云'
        }
      }
      console.log(user)
      // 发起登录请求
      this.$axios.post('https://afs7hx.toutiao15.com/loginByEm', {
        email: this.inputUsername,
        password: this.inputPassword
      }).then(response => {
        console.log(response)
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('登录成功')
            // 登录成功，用户信息存入state
            const userInfo = {
              username: res.data.username,
              nickname: res.data.nickname,
              gender: res.data.gender,
              signature: res.data.signature,
              profile: res.data.profile,
              email: res.data.email
            }
            this.$store.commit('loginUser', userInfo)
            this.redirectLastPage() // 页面跳转
          } else { // 登录失败
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 页面跳转
    redirectLastPage () {
      if (this.$route.query.redirect) {
        this.$router.replace({
          path: this.$route.query.redirect,
          query: this.$route.query
        })
      } else {
        this.$router.replace('/')
      }
    }
  },
  mounted () {
  }
}

</script>

<style lang="scss" scoped>
  #nav-bar {
    position: fixed;
    top: 0;
    height: 40px;
    width: 100%;
    z-index: 999;
    text-align: center;
    line-height: 40px;

    @include themify {
      background-color: themed('nav-bg-color');
      color: themed('nav-font-color');
    }

    span {
      font-size: 18px;
    }
  }

  #nav-left {
    height: 100%;
    position: absolute;
    display: flex;
    align-items: center;
    left: 10px;

    @include themify {
      color: themed('nav-font-color');
    }

    span {
      font-size: 14px;
    }
  }

  #nav-left-icon {
    font-size: 25px;
    font-weight: bolder;

    &:hover {
      cursor: pointer;
    }
  }

  .header {
    padding-top: 40px;
  }

  .smile {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-around;
    font-size: 28px;
    font-weight: 570;
    margin: 70px 85px 70px 85px;
    color: rgba(89, 147, 210, 0.65);
    @include themify {
      color: themed('smile-color') !important;
    }

    i {
      font-size: 50px;
    }
  }

  .alter-item {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-between;
    height: 60px;
    padding: 0 55px 0 50px;
    position: relative;

    .word {
      flex: none;
      font-size: 20px;
      // padding: 0px 0px 0px 0px;
      margin-right: 15px;
      font-weight: 600;
      color: rgba(42, 42, 42, 0.8);
      @include themify {
        color: themed('log-font-color');
      }
    }

    input {
      width: 100%;
      font-size: 14px;
      outline: none;
      border: none;
      box-sizing: border-box;
      line-height: 24px;
      border-radius: 2px;
      background-color: #f7f7f7;
      padding: 3px 5px;
      @include themify {
        background-color: themed('for-input-color');
      }

      &::placeholder{
        color: #A0A0A0;
      }

      &:focus {
        border: 1px solid rgb(181, 212, 245);
        box-shadow: 0 0 5px rgba(181, 212, 245, 0.678);
      }
    }

    .if-show-password {
      position: absolute;
      top: 0;
      bottom: 0;
      margin-top: auto;
      margin-bottom: auto;
      font-size: 16px;
      flex: none;
      margin-left: 6px;
      color: #636363;
    }
  }

  .buttons {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-around;
    margin: 40px 30px 0px 30px;

    #sign,
    #regi {
      font-size: 18px;
      width: 114px;
    }
  }

  #forget-password {
    font-size: 14px;
    font-weight: 560;
    text-align: right;
    text-decoration: underline;
    color: rgba(99, 98, 98, 1);
    margin-top: 25px;
    padding-right: 30px;
  }

</style>
