<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <div id="nav-left">
          <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()" />
        </div>
        <span>忘记密码</span>
      </div>
    </div>
    <!-- 忘记密码 step1 输入用户名 -->
    <div v-if="curStep === 0">
      <!--文字提示-->
      <div id="hint">请输入您的用户名:</div>
      <!--输入框-->
      <div class="alter-item">
        <input v-model="inputUsername" @input="filterUsername" />
      </div>
      <!--按钮-->
      <div id="button-wrap">
        <van-button color="#66A2E4" @click="getQuestion" :disabled="inputUsername === ''">下一步</van-button>
      </div>
    </div>

    <!-- 忘记密码 step2 验证密保问题 -->
    <div v-if="curStep === 1">
      <!--提示列-->
      <div id="hint">请正确回答密保问题</div>
      <!--密保问题-->
      <div class="alter-item">
        <div class="word">问题</div>
        <div class="question">{{pwProtection}}</div>
      </div>
      <!--答案-->
      <div class="alter-item">
        <div class="word">答案</div>
        <input v-model="inputAnswer" placeholder="请输入问题答案" />
      </div>
      <!--按钮-->
      <div id="button-wrap">
        <van-button color="#66A2E4" @click="verifyQuestion" :disabled="inputAnswer === ''">下一步</van-button>
      </div>
    </div>

    <!-- 忘记密码 step3 设置新密码 -->
    <div v-if="curStep === 2">
      <!--文字提示-->
      <div id="hint">设定新的密码:</div>
      <!--输入框-->
      <div class="alter-item">
        <input v-model="inputNewPassword" type="password" />
      </div>
      <div id="hint">再次确认密码:</div>
      <div class="alter-item">
        <input v-model="inputNewPasswordCheck" type="password" />
      </div>
      <!--按钮-->
      <div id="button-wrap">
        <van-button color="#66A2E4" @click="setNewPassword"
          :disabled="inputNewPassword === '' || inputNewPasswordCheck === ''">完成</van-button>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'forgetPassword',
  components: {},
  data () {
    return {
      curStep: 0, // 0:输入用户名步骤  1:验证密保步骤  2:设置新密码步骤
      pwProtection: '您最熟悉的学校宿舍舍友名字是?',
      inputUsername: '',
      inputAnswer: '',
      inputNewPassword: '',
      inputNewPasswordCheck: ''
    }
  },
  methods: {
    // 用户名输入限制
    filterUsername (e) {
      const value = e.target.value
      const pattern = /[^a-zA-Z0-9_-]/g
      if (pattern.test(value)) {
        this.$toast('限数字英文下划线与中划线!')
      }
      const filter = value.replace(pattern, '') // 限英文数字、下划线中划线
      if (filter.length > 16) {
        this.$toast('用户名长度限制为4~16!')
      }
      this.inputUsername = filter.substr(0, 16) // 限制长度16
    },
    // 验证用户名并获取问题
    getQuestion () {
      // 检查用户名长度
      if (this.inputUsername.length < 4) {
        this.$toast('用户名长度限制为4~16!')
        return
      }
      // 验证用户名并获取问题
      this.$axios.post('https://afs7hx.toutiao15.com/getQuiz', {
        username: this.inputUsername
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            // this.$toast(res.msg)
            this.pwProtection = res.data
            this.curStep = 1
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 核验答案是否正确
    verifyQuestion () {
      this.$axios.post('https://afs7hx.toutiao15.com/quiz', {
        username: this.inputUsername,
        answer: this.inputAnswer
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('密保验证成功!')
            this.curStep = 2
            this.answer = '' // 清空输入
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 设置新密码
    setNewPassword () {
      // 检查新密码长度是否符合要求
      if (this.inputNewPassword.length < 6 || this.inputNewPassword.length > 16) {
        this.$toast('密码长度限制为6~16!')
        return
      }
      // 检查两次密码是否一致
      if (this.inputNewPassword !== this.inputNewPasswordCheck) {
        this.$toast('两次输入的新密码不一致!')
        return
      }
      // 发起修改密码请求
      this.$axios.post('https://afs7hx.toutiao15.com/modPassword', {
        username: this.inputUsername,
        newPassword: this.inputNewPassword
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('修改成功')
            this.$router.replace('/login')
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
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

  #hint {
    font-size: 16px;
    font-weight: 600;
    color: rgba(171, 170, 170, 170);
    margin-top: 20px;
    margin-left: 30px;
  }

  .alter-item {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-between;
    height: 60px;
    padding: 0 45px 0 45px;

    .word {
      font-size: 18px;
      flex: none;
      // width: 75px;
      text-align: right;
      margin-right: 15px;
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

    .question {
      width: 100%;
      background-color: #f7f7f7;
      border-radius: 2px;
      padding: 5px;
      font-size: 15px;
      text-align: center;
      color: #66A2E4;
      @include themify {
        background-color: themed('chP-picker-color');
      }
    }
  }

  #button-wrap {
    display: flex;
    justify-content: center;
    margin-top: 45px;
  }

</style>
