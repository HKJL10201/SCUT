<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/my_center">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" />
          </div>
        </router-link>
        <span>个人中心</span>
      </div>
    </div>
    <!-- 基本资料 -->
    <div class="edit">
      <div class="profile">
        <!--头像-->
        <div class="alter-pro" @click="popAlter = true">
          <img :src="curInfo.profile" />
        </div>
        <div class="name-edit-wrap">
          <van-field class="name-edit" v-model="curInfo.nickname" ref="nameInput" placeholder="输入你的昵称"
            @keyup.enter="doneInput" />
          <!-- <div id="edit-name"> Douglas.YSSS </div> -->
          <van-icon id="edit-icon" name="edit" />
        </div>
      </div>
    </div>
    <!-- 修改列 -->
    <div class="alter-wrap">
      <!--修改性别-->
      <div class="alter-item">
        <div class="word">性别</div>
        <div class="alter-item-radio">
          <van-radio-group v-model="curInfo.gender" direction="horizontal">
            <van-radio name="男">男</van-radio>
            <van-radio name="女">女</van-radio>
          </van-radio-group>
        </div>
      </div>
      <!--修改个签-->
      <div class="alter-item item-signature">
        <div class="word">个性签名</div>
        <van-field class="alter-item-input" type="textarea" ref="sigInput" @keydown.enter="doneInput" maxlength="25"
          v-model="curInfo.signature" placeholder="输入你的个性签名(限25个汉字)" />
      </div>
      <!--修改邮箱-->
      <div class="alter-item">
        <div class="word">邮箱</div>
        <van-field class="alter-item-input" ref="emailInput" v-model="curInfo.email" placeholder="123456@qq.com"
          @keyup.enter="doneInput" />
      </div>
      <!--修改密码-->
      <router-link to="/change_password">
        <div class="alter-item">
          <div class="word">修改密码</div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
      <!--密保设置-->
      <router-link to="/change_pw_protection">
        <div class="alter-item">
          <div class="word">密保设置</div>
          <van-icon class="goto" name="arrow" />
        </div>
      </router-link>
    </div>
    <!--保存按钮-->
    <div id="save-button">
      <!-- #8EC963 -->
      <van-button class="vanbutton" color=#66A2E4 :disabled="!ifInfoChanged" type="primary" @click="saveInfo">保存
      </van-button>
    </div>
    <!--修改头像遮罩-->
    <van-overlay :show="popAlter" @click="popAlter=false">
      <div class="holder" @click.stop>
        <van-uploader v-model="firt" :before-read="beforeRead" :afterRead="afterRead" :max-count='1'
          :max-size="1024 * 1024" accept="image/png, image/jpeg" />
        <van-button id="save-but" color="#8EC963" @click="saveProfile">保存头像</van-button>
      </div>
    </van-overlay>
  </div>
</template>

<script>
export default {
  name: 'changeProfile',
  components: {},
  data () {
    return {
      gender: ['男', '女'],
      popAlter: false,
      curInfo: { // 当前输入的信息
        nickname: '',
        gender: '',
        signature: '',
        email: '',
        profile: ''
      },
      firt: []
    }
  },
  methods: {
    beforeRead (file) {
      const regex = /(.jpg|.jpeg|.png|.bmp)$/
      if (!regex.test(file.type)) {
        this.$Toast('图片格式不支持上传!')
        return false
      } else {
        return true
      }
    },
    afterRead (file) {
      // 图片压缩
      const image = new Image()
      const canvas = document.createElement('canvas')
      const ctx = canvas.getContext('2d')
      const that = this
      image.onload = function () {
        canvas.width = 80
        canvas.height = 80
        ctx.drawImage(image, 0, 0, 80, 80) // 这里是设置图片大小
        // result = canvas.toDataURL("image/jpeg", 0.7);
        that.curInfo.profile = canvas.toDataURL(file.file.type, 0.92)
      }
      image.src = file.content
    },
    // 按下回车，取消输入框焦点
    doneInput () {
      this.$refs.sigInput.blur()
      // 禁止textarea按下回车键换行
      window.event.preventDefault()
      this.$refs.nameInput.blur()
      this.$refs.emailInput.blur()
    },
    // 保存信息修改
    saveInfo () {
      if (this.ifInfoChanged) {
        // 发起请求
        this.$axios.post('https://afs7hx.toutiao15.com/modAllProfile', {
          username: this.$store.state.user.username,
          nickname: this.curInfo.nickname,
          email: this.curInfo.email,
          signature: this.curInfo.signature,
          gender: this.curInfo.gender
        }).then(response => {
          if (response.status === 200) {
            const res = response.data
            if (res.code === 1) {
              // 修改成功
              this.$toast({
                message: '保存成功',
                duration: 1300
              })
              // 修改store
              this.$store.commit('setUserOtherInfo', this.curInfo)
            } else {
              this.$toast(res.msg)
            }
          } else {
            this.$toast('请求失败')
          }
        })
      }
    },
    // 保存头像
    saveProfile () {
      console.log('执行保存')
      this.$axios.post('https://afs7hx.toutiao15.com/modProfile', {
        username: this.$store.state.user.username,
        profile: this.curInfo.profile
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('修改成功')
            this.$store.commit('setUserProfile', this.curInfo.profile)
          }
        }
      })
    }
  },
  computed: {
    // 获取当前登录用户的用户信息
    userInfo: function () {
      const user = this.$store.state.user
      const userInfo = {
        nickname: user.nickname,
        profile: user.profile,
        gender: user.gender,
        signature: user.signature,
        email: user.email
      }
      return userInfo
    },
    // 获取当前昵称输入框内容
    curNickNameInput: function () {
      return this.curInfo.nickname
    },
    // 获取当前个签输入框内容
    curSignatureInput: function () {
      return this.curInfo.signature
    },
    // 判断信息是否有修改
    ifInfoChanged: function () {
      if (JSON.stringify(this.curInfo) !== JSON.stringify(this.userInfo)) {
        return true
      } else {
        return false
      }
    }
  },
  watch: {
    // 监听输入内容, 限制输入不超过10个汉字或20个英文或字符
    curNickNameInput: function (newValue, oldValue) {
      console.log(newValue)
      if (newValue !== null && newValue !== '' && newValue.replace(/[\u4e00-\u9fa5]/g, '**').length > 20) {
        this.curInfo.nickname = oldValue
      }
    },
    // 监听个人签名，限制输入不超过25个汉字或50个字符
    curSignatureInput: function (newValue, oldValue) {
      console.log(newValue)
      if (newValue !== null && newValue !== '' && newValue.replace(/[\u4e00-\u9fa5]/g, '**').length > 50) {
        this.curInfo.signature = oldValue
      }
    }
  },
  mounted () {
    // 获取当前登录用户的信息并呈现
    this.curInfo = JSON.parse(JSON.stringify(this.userInfo))
    // const a = {
    //   a: '123'
    // }
    // const b = {
    //   a: '123'
    // }
    // console.log(a === b)
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

  .edit {
    position: relative;
  }

  .profile {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-start;
    padding: 12px 30px 12px 40px;
    margin-bottom: 8px;
    border-bottom: 2px solid #DEDEDE;
    @include themify {
      border-bottom: 2px solid themed('profile-bd-color');
    }
  }

  img {
    border-radius: 50%;
    height: 50px;
    width: 50px;
  }

  #edit-icon {
    color: rgba(48, 48, 48, 0.4);
    font-size: 25px;
    margin: 0 10px 0 10px;

    @include themify {
      color: themed('icon-color') !important;
    }
  }

  .name-edit-wrap {
    display: flex;
    flex-direction: row;
    align-items: center;
    padding-left: 15px;
    // border: 1px solid;

    .name-edit {
      border: 1px dashed rgba(136, 136, 136, 0.8);
      padding: 0;
    }

    /deep/ input {
      padding: 3px 5px;
      font-size: 18px;
      color: #585858;
      // border: 1px solid;
      outline: none;
    }
  }

  .alter-wrap {
    display: flex;
    flex-direction: column;
    margin-top: 0px;
  }

  .alter-item {
    display: flex;
    align-items: center;
    height: 65px;
    justify-content: space-between;
    padding: 0 40px 0 40px;
  }

  .word {
    font-size: 18px;
    // margin: 0px 0px 0px 40px;
    width: 73px;
    font-weight: 700;
    color: #303030;
    flex: none;

    @include themify {
      color: themed('word-color');
    }
  }

  .alter-item-radio {
    flex: auto;
    margin-left: 20px;
    width: 168px;
    display: flex;

    .van-radio {
      font-size: 15px;
      margin-right: 0;
    }

    .van-radio+.van-radio {
      margin-left: 30px;
    }
  }

  .alter-item-input {
    margin-left: 20px;
    border: 1px solid;
    padding: 0;
    border: 1px dashed rgba(136, 136, 136, 0.8);
    padding: 3px;
  }

  .item-signature {
    /deep/ .van-field__control {
      // box-sizing: border-box;
      min-height: 48px;
    }
  }

  .goto {
    color: rgba(16, 16, 16, 0.6);
    font-size: 20px;

    // padding: 0px 0px 0px 180px;
    @include themify {
      color: themed('goto-color') !important;
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

  .holder {
    display: flex;
    flex-direction: column;
    align-items: center;
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);

    /deep/ .van-uploader__upload {
      width: 120px;
      height: 130px;
      margin: 0 0 30px 0;
    }

    #save-but {
      width: 120px;
      font-size: 20px;
    }
  }

  .alter-item-input,
  .name-edit-wrap .name-edit {
    @include themify {
      background-color: themed('field-color');
    }
  }

  /* .name-edit-wrap /deep/ .van-field__control{ */
  .edit,
  .alter-wrap {
    /deep/ .van-field__control {
      @include themify {
        background-color: themed('field-color') !important;
        color: themed('name-edit-color');
      }
    }
  }

  .van-radio__label {
    @include themify {
      color: themed('sex-color');
    }
  }

  .alter-item-radio {

    /deep/.van-radio__icon--checked .van-icon {
      //background-color: #1989fa;
      //border-color: #1989fa;
      @include themify {
        // background-color: themed('choose-color') !important;
        // border-color: themed('choose-color') !important;
        background-color: themed('theme-ch-radio-bg-color');
        border-color: themed('theme-ch-radio-border-ck-color');
        color: themed('theme-ch-radio-color');
      }

    }

    /deep/ .van-icon {
      @include themify {
        border-color: themed('theme-ch-radio-border-color');
      }
    }
  }

  .vanbutton {
    font-size: 18px;
    width: 100%;

    @include themify {
      background-color: themed('button-color') !important;
      border-color: themed('button-color') !important;

    }
  }

</style>
