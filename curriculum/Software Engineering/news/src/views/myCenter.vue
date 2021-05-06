<template>
  <div class="my-center">
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/news_list">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" />
            <span>返回首页</span>
          </div>
        </router-link>
        <span>个人中心</span>
      </div>
    </div>
    <!-- 基本资料 -->
    <router-link to='/my_center/change_info'>
      <div class="edit">
        <div class="profile">
          <img v-if="ifLogin" :src="userInfo.profile">
          <img v-else src="../assets/profile_logout.png">
          <div id="edit-name">{{ userInfo.nickname }}</div>
          <!-- <div id="edit-name"> Douglas.Y </div> -->
          <van-icon id="edit-arror" name="arrow" />
        </div>
        <div id="notice">设定基本资料</div>
      </div>
    </router-link>
    <!-- 选项列 -->
    <div class="options">
      <!-- 应用设置 -->
      <router-link to="/my_center/settings">
        <div class=hori-text>
          <div class="option-left">
            <van-icon class="icon" name="setting" color="#5e5e5e" />
            <div class="upright-text">
              <div class="op">应用设置</div>
              <div class="op-disc">主题色、字体大小等</div>
            </div>
          </div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
      <router-link to="/my_center/collection">
        <div class=hori-text>
          <div class="option-left">
            <van-icon class="icon" name="star" color="#F0CB54" />
            <div class="upright-text">
              <div class="op">我的收藏</div>
              <div class="op-disc">收藏的新闻</div>
            </div>
          </div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
      <router-link to="/my_center/thumb_up_comments">
        <div class=hori-text>
          <div class="option-left">
            <van-icon class="icon" name="good-job" color="#ED6161" />
            <div class="upright-text">
              <div class="op">我的点赞</div>
              <div class="op-disc">点赞过的评论</div>
            </div>
          </div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
      <router-link to="/my_center/comments">
        <div class=hori-text>
          <div class="option-left">
            <van-icon class="icon" name="comment" color="#5993D2" />
            <div class="upright-text">
              <div class="op">我的评论</div>
              <div class="op-disc">参与评论的新闻或回复</div>
            </div>
          </div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
      <router-link to="/my_center/user_report">
        <div class=hori-text>
          <div class="option-left">
            <van-icon class="icon" name="column" color="#86B6CD" />
            <div class="upright-text">
              <div class="op">使用报告</div>
              <div class="op-disc">注册至今的使用数据</div>
            </div>
          </div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
    </div>
    <!--注销按钮-->
    <div id="logout-button" v-if="ifLogin">
      <van-button class="vanbutton" color=#1890FF type="info" @click="logout">注销</van-button>
    </div>
    <!-- 登录按钮 -->
    <div id="login-button" v-else>
      <!-- <router-link to="/login/"> -->
        <van-button class="vanbutton" color=#1890FF type="info" @click="login">登录</van-button>
      <!-- </router-link> -->
    </div>
  </div>
</template>

<script>
export default {
  name: 'myCenter',
  components: {},
  data () {
    return {
      popAlter: false
    }
  },
  methods: {
    // login登入
    login () {
      this.$router.push({ path: '/login', query: { redirect: this.$route.fullPath } })
    },
    // logout注销
    logout () {
      this.$store.commit('logoutUser') // 注销用户
    }
  },
  computed: {
    // 是否已登录
    ifLogin: function () {
      // console.log('ifLogin的值已经改变')
      // console.log(this.$store.getters.ifLogin)
      return this.$store.getters.ifLogin
    },
    // 显示用户信息
    userInfo: function () {
      const user = this.$store.state.user
      let userInfo
      if (this.ifLogin) {
        userInfo = {
          nickname: user.nickname,
          profile: user.profile,
          signature: user.signature
        }
      } else {
        userInfo = {
          nickname: '未登录',
          profile: '',
          signature: ''
        }
      }
      return userInfo
    }
  },
  mounted: function () {
    // console.log(this.ifLogin)
    // const p = '\\A\\B\\C'
    // console.log(p)
    // const reg = new RegExp('\\\\', 'g')
    // const r = p.replace(reg, '')
    // console.log('结果:' + r)
  }
}

</script>

<style lang="scss" scoped>
  .my-center {
    // background-color: white;
    background-color: white;
    @include themify {
      background-color: themed('theme-bg-color');
    }
  }

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

  .edit {
    position: relative;
    border-bottom: 2px solid;
    border-color: #f0f0f0;
    @include themify {
      border-color: themed('profile-bd-color');
    }
  }

  .profile {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-between;
    padding: 10px 20px 10px 20px;
    margin: 4px 0;

  }

  img {
    border-radius: 50%;
    height: 50px;
    width: 50px;
  }

  #edit-name {
    font-size: 25px;
    color: rgba(48, 48, 48, 0.8);
    @include themify {
      color: themed('sig-font-color');
    }
  }

  #edit-arror {
    color: rgba(48, 48, 48, 0.4);
    font-size: 20px;
    @include themify {
      color: themed('arr-color') ;
    }
  }

  #notice {
    color: #5e5e5e;
    top: 50px;
    right: 24px;
    position: absolute;
    font-size: 10px;
    color: rgba(16, 16, 16, 0.6);
    @include themify {
      color: themed('not-font-color');
    }
  }

  .options {
    display: flex;
    flex-direction: column;
  }

  .option-left {
    display: flex;
    align-items: center;

    .icon {
      font-size: 23px;
      text-shadow: 0px 1px 1px rgba(206, 206, 206, 0.61);
    }
  }

  .upright-text {
    margin-left: 10px;
    padding: 10px 0px 0px 5px;
    line-height: 19px;
    flex-direction: column;
  }

  .hori-text {
    display: flex;
    flex-direction: row;
    align-items: center;
    padding: 7px 15px 10px 15px;
    justify-content: space-between;
  }

  .op {
    font-size: 18px;
    color: rgba(0, 0, 0, 0.87);
    @include themify {
      color: themed('op-font-color');
    }
  }

  .op-disc {
    font-size: 10px;
    color: rgba(0, 0, 0, 0.60);
    @include themify {
      color: themed('opdi-font-color');
    }
  }

  .goto {
    color: rgba(16, 16, 16, 0.6);
    font-size: 20px;
    @include themify {
      color: themed('goto-color') !important;
    }
  }

  #login-button, #logout-button {
    width: 90px;
    height: 42px;
    // position: absolute;
    // left: 0;
    // right: 0;
    bottom: 60px;

    margin: {
      left: auto;
      right: auto;
      top: 110px;
    }

    .vanbutton {
      font-size: 18px;
      width: 100%;
      // color: #66A2E4 !important;
      border-color: none !important;
      @include themify {
      background-color: themed('sig-but-color') !important;
      border-color: themed('border-color') !important;
      }
    }
  }

</style>
