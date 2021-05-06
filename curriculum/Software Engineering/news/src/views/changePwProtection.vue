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
        <span>密保设置</span>
      </div>
    </div>
    <!--提示列-->
    <div id="hint" v-if="curStep === 0">设置密保问题可以用于密码找回</div>
    <div id="hint" v-if="curStep === 1">点击修改按钮可重新设定密保问题</div>
    <div id="hint" v-if="curStep === 2">请输入当前密保的答案进行验证</div>
    <!-- 修改列 -->
    <div class="alter">
      <!--密保问题-->
      <div class="alter-item alter-picker">
        <div class="word">密保问题</div>
        <!-- 已设置过密码问题, 只显示, 禁止点击 -->
        <div class="pop-picker" v-if="curStep !== 0">
          {{pwProtection}}
        </div>
        <!-- 点击可选择密保问题项 -->
        <div class="pop-picker" @click="showPicker=true" v-if="!curStep">
          {{pwProtection}}
        </div>
        <!-- 密保问题选择弹窗 -->
        <van-popup v-model="showPicker" round position="bottom">
          <van-picker show-toolbar :columns="columns" title="密保问题"
          @cancel="showPicker = false" @confirm="pickerConfirm" item-height="40"/>
        </van-popup>
      </div>
      <!--输入答案-->
      <div class="alter-item" v-if="curStep !== 1">
        <div class="word">答案</div>
        <input v-model="answer" placeholder="请输入答案" />
      </div>
      <!--按钮组-->
      <div id="buttons">
        <!-- 已设置过密保, 点击进入密保修改 -->
        <van-button color=#66A2E4 type="primary" v-if="curStep === 1" @click="curStep = 2">修改密保</van-button>
        <!-- 点击验证已有密保 -->
        <van-button color=#66A2E4 type="primary" v-if="curStep === 2" @click="toVerifyCurProtection">下一步</van-button>
        <!-- 点击保存新的密保设定 -->
        <van-button color=#66A2E4 :disabled="!answer" type="primary"
        v-if="curStep === 0" @click="saveChange">保存</van-button>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'changePwProtection',
  components: {},
  data () {
    return {
      curStep: 0, // 0:未设定密保问题(或设定新的密保)  1:已设定密保问题  2:验证当前密保
      columns: ['1、您目前的姓名是?',
        '2、您配偶的生日是?',
        '3、您的学号（或工号）是?',
        '4、您母亲的生日是?',
        '5、您高中班主任的名字是?',
        '6、您父亲的姓名是?',
        '7、您小学班主任的名字是?',
        '8、您父亲的生日是?',
        '9、您配偶的姓名是?',
        '10、您初中班主任的名字是?',
        '11、您最熟悉的童年好友名字是?',
        '12、您最熟悉的学校宿舍舍友名字是?',
        '13、对您影响最大的人名字是?'
      ],
      showPicker: false,
      pwProtection: '点击选择密保问题', // 密保问题
      answer: '' // 密保答案
      // pwProtection: '你最喜欢小猪还是迷你猪还是超级迷你小猪猪?'
    }
  },
  methods: {
    pickerConfirm (value) {
      // 去掉问题前面的序号
      const reg = /[0-9、]+/g
      this.pwProtection = value.replace(reg, '')
      this.showPicker = false
    },
    // 验证当前密保的答案
    toVerifyCurProtection () {
      this.$axios.post('https://afs7hx.toutiao15.com/quiz', {
        username: this.$store.state.user.username,
        answer: this.answer
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('密保验证成功!')
            this.curStep = 0
            this.answer = '' // 清空输入
            this.pwProtection = '点击选择密保问题'
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 保存密保问题修改
    saveChange () {
      if (this.pwProtection === '点击选择密保问题') {
        this.$toast('未选择密保问题!')
        return
      }
      this.$axios.post('https://afs7hx.toutiao15.com/modQuiz', {
        username: this.$store.state.user.username,
        question: this.pwProtection,
        answer: this.answer
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.$toast('密保问题修改成功!')
            this.curStep = 1
            this.answer = ''
            this.$store.commit('setPasswordQuiz', this.pwProtection)
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 获取密保问题
    getQuiz () {
      if (this.$store.state.user.quiz && this.$store.state.user.quiz !== '') {
        this.pwProtection = this.$store.state.user.quiz
        this.curStep = 1
      }
    }
  },
  created: function () {
    // 获取密保问题
    this.getQuiz()
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
    margin-top: 18px;
    margin-left: 30px;
  }

  .alter {
    display: flex;
    flex-direction: column;
    margin-top: 20px;
  }

  .alter-item {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: space-between;
    height: 60px;
    padding: 0 25px 0 25px;

    .word {
      font-size: 18px;
      flex: none;
      width: 75px;
      text-align: right;
      margin-right: 10px;
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
      text-align:center;
      @include themify {
        background-color: themed('chP-picker-color');
      }

      &::placeholder {
        color: #A0A0A0;
      }

      &:focus {
        border: 1px solid rgb(181, 212, 245);
        box-shadow: 0 0 5px rgba(181, 212, 245, 0.678);
      }
    }

    .pop-picker {
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

  .alter-picker {
    justify-content: left;
  }

  #buttons {
    display: flex;
    justify-content: center;
    margin-top: 45px;
  }

</style>
