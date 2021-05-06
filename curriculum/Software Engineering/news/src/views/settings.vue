<template>
  <div>
    <div id="nav-bar">
      <router-link to="/my_center">
        <van-icon id="nav-left-icon" name="arrow-left" @click="goLastPage" />
      </router-link>
      <span>应用设置</span>
    </div>
    <div id="theme-area">
      <div id="theme-title">主题色</div>
      <div id="theme-wrap">
        <div class="theme-img theme-blue"></div>
        <div class="theme-img theme-red"></div>
        <div class="theme-img theme-khaki"></div>
      </div>
      <van-radio-group v-model="theme" direction="horizontal" @change="themeChange">
        <van-radio name="default"></van-radio>
        <van-radio name="red"></van-radio>
        <van-radio name="khaki"></van-radio>
      </van-radio-group>
    </div>
    <div class="settings-cell cell-small">
      <div class="settings-item">
        <!-- <van-icon name="info-o" /> -->
        <svg-icon icon-class="dark" class="i-dark-model"></svg-icon>
        <span>日夜间模式</span>
      </div>
      <van-switch v-model="nightMode" size="0.7rem" />
    </div>
    <div class="settings-cell cell-small" @click="popFontSize = true">
      <div class="settings-item">
        <!-- <van-icon name="info-o" /> -->
        <svg-icon icon-class="font" class="i-font"></svg-icon>
        <span>字体大小</span>
      </div>
      <div class="setting-content"> {{ myFontSize }}</div>
    </div>
    <div class="settings-cell cell-big">
      <div class="settings-item">
        <!-- <van-icon class="settings-icon" name="info-o" /> -->
        <svg-icon icon-class="no-pic" class="i-no-pic"></svg-icon>
        <div>
          <div>省流量模式</div>
          <div class="setting-desc">
            * 省流量模式下不显示图片或视频
          </div>
        </div>
      </div>
      <van-switch v-model="noPicMode" size="0.7rem" />
    </div>
    <van-overlay :show="popFontSize" @click="popFontSize = false">
      <div class="pop-wrap">
        <div class="pop-font-choose" @click.stop>
          <div>字体大小</div>
          <mt-radio align="right" v-model="myFontSize" :options="options">
          </mt-radio>
        </div>
      </div>
    </van-overlay>
    <!-- <van-button type="info">信息按钮</van-button> -->
  </div>
</template>

<script>
export default {
  name: 'settings',
  data () {
    return {
      theme: 'default',
      nightMode: false,
      noPicMode: false,
      myFontSize: '中',
      popFontSize: false,
      options: [{ // 分别表示"显示内容"与选中项对应的绑定值myFontSize;
        label: '小',
        value: '小'
      },
      {
        label: '中',
        value: '中'
      },
      {
        label: '大',
        value: '大'
      }
      ],
      themeList: ['default', 'red', 'khaki'],
      fontSizeMap: {
        小: 'small',
        中: 'medium',
        大: 'large'
      }
    }
  },
  methods: {
    // 返回上一页
    goLastPage () {
    },
    // 主题修改
    themeChange (name, index) {
      console.log(name)
    }
  },
  computed: {
  },
  watch: {
    // 修改日夜间模式
    nightMode: function (val) {
      console.log(val)
      if (val) {
        document.body.setAttribute('data-theme', 'dark')
        this.$store.commit('setDarkMode', true)
        localStorage.darkMode = 1
      } else {
        document.body.setAttribute('data-theme', this.$store.state.themeColor)
        this.$store.commit('setDarkMode', false)
        localStorage.darkMode = 0
      }
    },
    // 修改省流量模式
    noPicMode: function (val) {
      this.$store.commit('setNoPicMode', val)
      if (val) {
        localStorage.noPicMode = 1
      } else {
        localStorage.noPicMode = 0
      }
    },
    // 修改主题
    theme: function (val) {
      // 如果夜间模式未开，则修改 "theme" 全局变量，但不更改body属性
      if (!this.$store.state.darkMode) {
        document.body.setAttribute('data-theme', val)
      }
      this.$store.commit('setThemeColor', val)
      localStorage.themeColor = val
    },
    // 修改字体大小
    myFontSize: function (val) {
      console.log(this.fontSizeMap[val])
      const fontSize = this.fontSizeMap[val]
      document.body.setAttribute('data-size', fontSize)
      this.$store.commit('setFontSize', fontSize)
      localStorage.fontSize = fontSize
    }

  },
  mounted: function () {
    this.noPicMode = this.$store.state.noPicMode
    this.nightMode = this.$store.state.darkMode
    this.theme = this.$store.state.themeColor
    this.myFontSize = Object.keys(this.fontSizeMap).find(k => this.fontSizeMap[k] === this.$store.state.fontSize)
  }

}

</script>

<style lang="scss" scoped>
  #nav-bar {
    position: relative;
    height: 40px;
    text-align: center;
    line-height: 40px;

    @include themify {
      background-color: themed('nav-bg-color');
      color: themed('nav-font-color');
    }

    span {
      font-size: 18px;
      @include setFontSize(18px);
    }
  }

  #nav-left-icon {
    position: absolute;
    left: 10px;
    top: 50%;
    transform: translate(0, -50%);
    font-size: 25px;
    font-weight: bolder;

    @include themify {
      color: themed('nav-font-color');
    }

    &:hover {
      cursor: pointer;
    }
  }

  #theme-area {
    @include themify {
      border-bottom: 1Px solid themed('theme-divider-color');
    }

    .van-radio-group--horizontal {
      justify-content: space-between;
      margin-top: 10px;
      padding-left: 33px;
      padding-right: 33px;
      margin-bottom: 10px;
    }

    .van-radio--horizontal {
      width: 85px;
      margin-right: 0;
      display: flex;
      justify-content: center;
    }

    // 单选框
    /deep/ .van-radio__icon--checked .van-icon{
      @include themify {
        background-color: themed('theme-ch-radio-bg-color');
        border-color: themed('theme-ch-radio-border-ck-color'); // 非夜间模式下有效, 设定选中项边框色
        color: themed('theme-ch-radio-color');
      }
    }

    /deep/ .van-icon {
      @include themify {
        border-color: themed('theme-ch-radio-border-color'); // 夜间模式下有效，设置常态项边框色 (非夜间模式下，取默认)
      }
    }
  }

  #theme-title {
    font-size: 18px;
    @include setFontSize(18px);
    padding-left: 33px;
    margin: 12px 0 12px 0;
  }

  #theme-wrap {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    padding-left: 33px;
    padding-right: 33px;
  }

  .theme-img {
    display: block;
    height: 100px;
    width: 80px;
    border-radius: 15px;

    @include themify {
      border: themed('theme-img-border');
      box-shadow: themed('theme-img-box-shadow');
    }
  }

  .theme-blue {
    background-color: #66A2E4;
  }

  .theme-red {
    background-color: #ED6161;
  }

  .theme-khaki {
    background-color: #dddaa9;
  }

  .settings-cell {
    display: flex;
    align-items: center;
    padding: 12px;

    /deep/ .van-switch {
      @include themify {
        background-color: themed('switch-bg-color');
      }
    }

    /deep/ .van-switch--on {
      @include themify {
        background-color: themed('switch-bg-on-color');
      }
    }

    /deep/ .van-switch__node {
      @include themify {
        background-color: themed('switch-circle-color');
      };
    }

    .svg-icon {
      // margin-right: 7px;
      display: block;
      color: #6d6d6d;
    }

    .i-dark-model {
      // display:block;
      font-size: 23px;
      @include setFontSize(23px);
      margin: -2px 9px 0 0;
    }

    .i-font {
      margin: -3px 12px 0 3px;
    }

    .i-no-pic {
      margin: 0px 13px 0 3px;
    }
  }

  .cell-small {
    height: 32px;
    line-height: 32px;
  }

  .settings-item {
    font-size: 18px;
    display: flex;
    align-items: center;
    width: 295px;

    @include setFontSize(18px);

    .van-icon {
      font-size: 30px;
      @include setFontSize(30px);
      color: #66A2E4;
      margin-right: 5px;
    }

    .setting-desc {
      font-size: 13px;
      @include setFontSize(13px);

    }

    span {
      display: block;
    }
  }

  .setting-content {
    padding-left: 16px;
    font-size: 19px;
    @include setFontSize(19px);
    /* font-weight: bold; */
    color: #ABAAAA;
  }

  .pop-wrap {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100%;
  }

  .pop-font-choose  {
    height: 140px;
    width: 170px;
    padding: 15px 20px 0px 20px;
    border-radius: 5px;
    background-color: rgb(255, 255, 255);
    @include themify {
      background-color: themed('pop-font-ch-color');
    }

    div {
      font-size: 18px;
      @include setFontSize(18px);
    }

    //字体单选框-radio
    /deep/ .mint-cell {
      min-height: 0;
      height: 30px;
      @include themify {
        background-color: themed('pop-font-ch-color');
      }

      .mint-radio-label {

      }
    }

    /deep/ .mint-radiolist-label {
      padding: 0;
      height: 21px;
      line-height: 21px;
    }

    /deep/ .mint-radio-label {
      margin-left: 0;
      @include setFontSize(16px);
    }

    /deep/ .mint-cell-wrapper {
      background-image: none;
      padding: 0;
    }

    /deep/ .mint_radio {
      height: 25px;
    }

    /deep/ .mint-radio-input:checked + .mint-radio-core {
      // 选中项内部颜色
      background-color: #66A2E4;
      @include themify {
        background-color: themed('font-ch-radio-inner-color');
      }
    }

    /deep/ .mint-radio-core {
      border-radius: 100%;
      @include themify {
        background-color: themed('font-ch-radio-bg-color');
        border-color: themed('font-ch-radio-border-color');
      }

      &::after {
        @include themify {
          background-color: themed('font-ch-radio-core-color');
        }
      }
    }
  }

</style>
