<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/my_center/change_info">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" />
          </div>
        </router-link>
        <span>修改密码</span>
      </div>
    </div>
    <!-- 修改列 -->
    <div class="alter-list">
      <!--原密码-->
      <div class="alter-item">
        <div class="word">原密码</div>
        <!-- <van-field class="alter-item-input" v-model="originPassword" placeholder="请输入原密码"/> -->
        <input class="alter-item-input" v-model="originPassword" type="password" placeholder="请输入原密码" />
      </div>
      <!--新密码-->
      <div class="alter-item">
        <div class="word">新密码</div>
        <input class="alter-item-input" v-model="newPassword" type="password" placeholder="请输入新密码" />
      </div>
      <!--确认新密码-->
      <div class="alter-item">
        <div class="word">确认新密码</div>
        <input class="alter-item-input" v-model="newPasswordCheck" type="password" placeholder="请再次输入新密码" />
      </div>
    </div>
    <!--保存按钮-->
    <div id="save-button">
      <!-- #8EC963 -->
      <van-button class="vanbutton" color=#66A2E4 :disabled="!ifDoneInput" type="primary" @click="clickChangePassword">
        保存</van-button>
    </div>
  </div>
</template>

<script>
export default {
  name: 'changePassword',
  components: {},
  data () {
    return {
      originPassword: '',
      newPassword: '',
      newPasswordCheck: ''
    }
  },
  methods: {
    clickChangePassword () {
      // 检查新密码长度是否符合要求
      if (this.newPassword.length < 6 || this.newPassword.length > 16) {
        this.$toast('密码长度限制为6~16!')
        return
      }
      // 检查两次密码是否一致
      if (this.newPassword !== this.newPasswordCheck) {
        this.$toast('两次输入的新密码不一致!')
        return
      }
      // 修改密码
      this.$axios.post('https://afs7hx.toutiao15.com/modUser', {
        username: this.userId,
        password: this.originPassword,
        newPassword: this.newPassword
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('修改成功!请重新登录')
            // 跳转到登录页
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    }
  },
  computed: {
    // 获取用户Id
    userId: function () {
      if (this.$store.state.user !== null && this.$store.state.user !== '') {
        return this.$store.state.user.username
      } else {
        return ''
      }
    },
    // 是否已经完成三项输入
    ifDoneInput: function () {
      if (this.originPassword !== '' && this.newPassword !== '' && this.newPasswordCheck !== '') {
        return true
      } else {
        return false
      }
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

  .alter-list {
    display: flex;
    flex-direction: column;
    margin-top: 60px;
  }

  .alter-item {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-between;
    height: 60px;
    padding: 0 30px;

    .word {
      font-size: 18px;
      flex: none;
      width: 110px;
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

      // background-color: #252525;
      @include themify {
        background-color: themed('chP-back-color');
      }

      padding: 3px 5px;

      &::placeholder {
        color: #A0A0A0;
      }

      &:focus {
        border: 1px solid rgb(181, 212, 245);
        box-shadow: 0 0 5px rgba(181, 212, 245, 0.678);
      }
    }
  }

  #save-button {
    text-align: center;
    margin-top: 40px;

    .vanbutton {
      font-size: 18px;
      width: 90px;
    }
  }

</style>
