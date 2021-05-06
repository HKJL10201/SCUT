<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()"/>
          </div>
        <span>注册页面</span>
      </div>
    </div>
    <!--笑脸-->
    <div class="smile">
      <van-icon name="smile-o" />
      <div>注册</div>
    </div>
    <!--账号-->
    <div class="alter-item">
      <div class="word">账号</div>
      <!-- <van-field v-model="username" placeholder="限数字英文下划线与中划线" @input="filterUsername" /> -->
      <input v-model="username" placeholder="限数字英文下划线与中划线" @input="filterUsername" />
    </div>
    <!--密码-->
    <div class="alter-item">
      <div class="word">密码</div>
      <!-- <van-field v-model="password" placeholder="要记得噢" /> -->
      <input v-model="password" type="password" placeholder="要记得噢" />
    </div>
    <!-- 确认密码 -->
    <div class="alter-item">
      <div class="word">确认密码</div>
      <!-- <van-field v-model="password" placeholder="要记得噢" /> -->
      <input v-model="passwordCheck" type="password" placeholder="再次输入密码" />
    </div>
    <!--邮箱-->
    <div class="alter-item">
      <div class="word">邮箱</div>
      <!-- <van-field v-model="email" placeholder="填写邮箱" /> -->
      <input v-model="email" placeholder="填写邮箱" />
    </div>
    <!--验证码-->
    <div class="verify">
      <div id="miniword">请输入验证码：</div>
      <van-field v-model="verCode" type="digit" placeholder="验证码" maxlength="6" />
      <van-button round color="#C1C2C2" @click='sendVerCode'>获取验证码</van-button>
    </div>
    <!--完成注册-->
    <div class="finished">
      <van-button id="finished-button" color="#7BD58F" @click="clickRegister">完成注册</van-button>
    </div>
    <!--已有账号-->
    <router-link to="/login">
      <div id="already-have">已有账号，立即登入</div>
    </router-link>
  </div>
</template>

<script>
export default {
  name: 'registerPage',
  components: {},
  data () {
    return {
      username: '',
      password: '',
      passwordCheck: '',
      email: '',
      verCode: ''
    }
  },
  methods: {
    // 用户名输入限制
    filterUsername (e) {
      const value = e.target.value
      console.log(event)
      console.log(value)
      const pattern = /[^a-zA-Z0-9_-]/g
      if (pattern.test(value)) {
        this.$toast('限数字英文下划线与中划线!')
      }
      const filter = value.replace(pattern, '') // 限英文数字、下划线中划线
      if (filter.length > 16) {
        this.$toast('用户名长度限制为4~16!')
      }
      this.username = filter.substr(0, 16) // 限制长度16
    },
    // 发送验证码
    sendVerCode () {
      // 待实现
      this.$toast({
        message: '已发送',
        duration: 1300
      })
    },
    // 点击注册按钮
    clickRegister () {
      // 检查用户名长度
      if (this.username.length < 4) {
        this.$toast('用户名长度限制为4~16!')
        return
      }
      // 检查邮箱格式
      const checkEmail = /^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$/
      if (!checkEmail.test(this.email)) {
        this.$toast('邮箱格式错误!')
        return
      }
      // 检查密码长度
      if (this.password.length < 6 || this.password.length > 16) {
        this.$toast('密码长度限制为6~16!')
        return
      }
      // 检查两次密码是否一致
      if (this.password !== this.passwordCheck) {
        this.$toast('两次输入密码不一致!')
        return
      }
      // 注册
      this.register()
    },
    // 注册账号
    register () {
      // 发起注册请求
      this.$axios.post('https://afs7hx.toutiao15.com/register', {
        username: this.username,
        password: this.password,
        email: this.email
      }).then(response => {
        // console.log(response)
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) { // 注册成功
            this.$toast({
              message: '注册成功!',
              duration: 1300
            })
            this.$router.replace('/login')
          } else { // 注册失败
            this.$toast({
              message: res.msg,
              duration: 1300
            })
          }
        } else {
          this.$toast('请求失败')
        }
      })
    }
  },
  watch: {
    username: function () {
      this.username.replace()
    },

    email: function () {

    }
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
    margin: 70px 85px 40px 85px;
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
    height: 50px;
    padding: 0 50px 0 25px;

    .word {
      flex: none;
      font-size: 18px;
      padding: 0px 0px 0px 0px;
      margin-right: 15px;
      font-weight: 600;
      text-align: right;
      width: 73px;
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

      &::placeholder {
        color: #A0A0A0;
      }

      &:focus {
        border: 1px solid rgb(181, 212, 245);
        box-shadow: 0 0 5px rgba(181, 212, 245, 0.678);
      }
    }
  }

    .verify {
      display: flex;
      flex-direction: row;
      align-items: center;
      justify-content: space-around;
      padding: 24px 50px 0px 50px;

      #miniword {
        font-size: 12px;
        color: rgba(114, 113, 113, 1);
      }

      .van-field {
        height: auto;
        width: 60px;
        padding: 0px;
        border-radius: 5px;
        background-color: inherit;

        /deep/ input {
          border-radius: 2px;
          background-color: #f7f7f7;
          padding: 3px 5px;
                @include themify {
        background-color: themed('for-input-color');
      }
        }
      }

      .van-button {
        font-size: 12px;
        font-weight: 550;
        text-align: center;
        width: 95px;
        height: 22px;
        line-height: 20px;
        border-radius: 7px;
        box-shadow: 0px 2px 2px 0px rgba(0, 0, 0, 0.4);
      }
    }

    .finished {
      display: flex;
      flex-direction: row;
      align-items: center;
      justify-content: center;
      margin-top: 50px;

      #finished-button {
        font-size: 18px;
        font-weight: 555;
        width: 144px;
        height: 42px;
        line-height: 20px;
      }
    }

    #already-have {
      font-size: 14px;
      font-weight: 560;
      text-align: right;
      text-decoration: underline;
      color: rgba(99, 98, 98, 1);
      margin-top: 30px;
      padding-right: 28px;
    }

</style>
