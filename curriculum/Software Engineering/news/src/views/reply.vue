<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()" />
        <span>回复({{replyCount - 1}})</span>
      </div>
    </div>
    <!-- 评论和评论回复，下拉刷新，瀑布流 -->
    <van-pull-refresh v-model="refreshing" @refresh="onRefresh">
      <van-list v-model="loading" :finished="finished" finished-text="没有更多评论了" @load="onLoad">
        <div v-for="(item, index) in list" :key="index">
          <!-- 评论项 -->
          <div class="reply-block">
            <!-- 左侧头像 -->
            <div class="reply-block-left">
              <img class="user-profile" v-if=!index v-bind:src="item.user.avatar_url" />
              <img class="user-profile" v-else v-bind:src="item.user.avatar_url" />
            </div>
            <!-- 右侧部分 -->
            <div class="reply-block-right">
              <!-- 用户名, 点赞/踩 -->
              <div class="reply-sub">
                <div class="reply-sub-info">
                  <div class="reply-user-name">{{item.user.name}}</div>
                  <div class="reply-space" v-if=!index><code> . </code></div>
                  <div class="reply-if-lz" v-if=!index>楼主</div>
                </div>
                <!-- 点赞/踩 wrap -->
                <div class="reply-interaction-wrap">
                  <!-- 点赞 -->
                  <transition name="fade" mode="out-in">
                    <div class="reply-inter reply-like" v-if="item.user_like" @click="changeReplyLike(index)"
                      key="like">
                      <van-icon class="reply-inter-icon" name="good-job"></van-icon>
                      {{item.like_count}}
                      <i class=marg />
                    </div>
                    <div class="reply-inter reply-dislike" v-else @click="changeReplyLike(index)" key="dislike">
                      <van-icon class="reply-inter-icon" name="good-job-o"></van-icon>
                      {{item.like_count}}
                      <i class=marg />
                    </div>
                  </transition>
                  <!-- 踩 -->
                  <transition name="fade" mode="out-in">
                    <div class="reply-inter reply-trample" v-if="item.user_oppose" @click="changeReplyTrample(index)"
                      key="trample">
                      <van-icon class="reply-inter-icon icon-dislike" name="good-job"></van-icon>
                      {{item.oppose_count }}
                      <i class=marg />
                    </div>
                    <div class="reply-inter reply-not-trample" v-else @click="changeReplyTrample(index)"
                      key="notTrample">
                      <van-icon class="reply-inter-icon icon-dislike" name="good-job-o"></van-icon>
                      {{item.oppose_count }}
                      <i class=marg />
                    </div>
                  </transition>
                </div>
              </div>
              <!-- 评论内容 -->
              <div class="reply-content">
                {{item.text}}
                <!-- 要切实发挥大项目、大企业的牵引作用，着力支持点多面广的小微企业和个体工商户复商复市，带动产业链上下游、大中小企业协同复工复产达产。 -->
              </div>
              <!-- 底部 -->
              <div class="reply-bottom">
                <!-- <span class="reply-time" v-if=!index>{{item.comment_time}}</span> -->
                <span class="reply-time">{{item.create_time}}</span>
                <router-link to="/home">
                </router-link>
              </div>
            </div>
          </div>
          <div class="reply-block-de" v-if=!index>
            <div class="reply-block-de-text">全部回复</div>
          </div>
        </div>
      </van-list>
    </van-pull-refresh>
    <div class="footer">
      <!-- 键盘未弹出时的底栏 -->
      <div class="footer-col footer-fixed" v-if="!ifShowKeybord">
        <div class="trigger-input" @click="showKeybord">
          <!-- <van-icon name="comment-o" /> -->
          <svg-icon icon-class="write" class="i-write"></svg-icon>
          <span>写下你的评论...</span>
        </div>
      </div>
      <!-- 键盘弹出时的评论框 -->
      <div class="footer-input footer-fixed" v-else>
        <van-field placeholder="写下你的评论..." ref="replyInput" type="textarea" maxlength="50" v-model="replyInputContent">
        </van-field>
        <div class="button-reply" ref="buttonReply" @click="addReply">
          发布
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios'
export default {
  name: 'reply',
  data () {
    return {
      newsId: '', // 获取新闻ID
      replyInputContent: '', // 评论输入内容为空
      // 是否有弹出键盘
      ifShowKeybord: false,
      replyCount: 0, // 评论数量
      list: [], // 评论列表
      loading: false,
      finished: false,
      refreshing: false,
      // 是否点赞
      user_like: true,
      // 是否踩
      user_oppose: true
    }
  },
  created () {
    // axios.get('http://localhost:3344/reply-lists')
    axios.get('https://afs7hx.toutiao15.com/getReplyList', {
      params: {
        username: this.username,
        // username: 'jack',
        // comment_id: '5ec63598f485ab00753c1ede'
        // username: this.$route.query.username,
        comment_id: this.$route.params.comment_id
      }
    })
      .then(_d => {
        this.list = _d.data
        this.replyCount = _d.data.length
        console.log(_d.data)
        console.log('create')
        console.log(this.$route)
      })
  },
  computed: {
    username: function () { // 已登录的用户ID
      return this.$store.state.user.username
    },
    nickname: function () { // 已登录的用户昵称
      return this.$store.state.user.nickname
    },
    profile: function () { // 已登录的用户头像
      return this.$store.state.user.profile
    }
  },
  methods: {
    // 返回上一页
    goLastPage () {

    },
    // 点赞
    changeReplyLike (index) {
      let commentId = ''
      if (index) {
        commentId = this.list[index].reply_id
      } else {
        commentId = this.list[index].comment_id
      }
      console.log(this.list[index].user_like)
      if (this.list[index].user_like === true) {
        this.list[index].user_like = false
        this.list[index].like_count -= 1
        // 同步到数据中：
        axios.post('https://afs7hx.toutiao15.com/thumbsUp', {
          // username: this.username,
          // username: 'jack',
          username: this.username,
          comment_id: commentId
        }, {})
          .then(_d => {
            console.log(_d)
            if (_d.status !== 200) {
              this.$toast('请求失败，请稍后重试')
            }
          })
          .catch(err => {
            this.$toast('请求失败，请稍后重试')
            console.log(err)
          })
      } else {
        this.list[index].user_like = true
        this.list[index].like_count += 1
        // 同步到数据中：
        axios.post('https://afs7hx.toutiao15.com/thumbsUp', {
          username: this.username,
          // username: 'jack',
          comment_id: commentId
        }, {})
          .then(_d => {
            console.log(_d)
            if (_d.status !== 200) {
              this.$toast('请求失败，请稍后重试')
            }
          })
          .catch(err => {
            this.$toast('请求失败，请稍后重试')
            console.log(err)
          })
      }
      console.log(this.list[index])
    },
    // 踩
    changeReplyTrample (index) {
      let commentId = ''
      if (index) {
        commentId = this.list[index].reply_id
      } else {
        commentId = this.list[index].comment_id
      }
      if (this.list[index].user_oppose === true) {
        this.list[index].user_oppose = false
        this.list[index].oppose_count -= 1
        // 同步到数据中：
        axios.post('https://afs7hx.toutiao15.com/thumbsDown', {
          username: this.username,
          // username: 'jack',
          comment_id: commentId
        }, {})
          .then(_d => {
            console.log(_d)
            if (_d.status !== 200) {
              this.$toast('请求失败，请稍后重试')
            }
          })
          .catch(err => {
            this.$toast('请求失败，请稍后重试')
            console.log(err)
          })
      } else {
        this.list[index].user_oppose = true
        this.list[index].oppose_count += 1
        // 同步到数据中：
        axios.post('https://afs7hx.toutiao15.com/thumbsDown', {
          username: this.username,
          // username: 'jack',
          comment_id: commentId
        }, {})
          .then(_d => {
            console.log(_d)
            if (_d.status !== 200) {
              this.$toast('请求失败，请稍后重试')
            }
          })
          .catch(err => {
            this.$toast('请求失败，请稍后重试')
            console.log(err)
          })
      }
    },
    // 添加评论
    addReply () {
      console.log('ls')
      // 输入内容为空
      if (this.replyInputContent === '') {
        this.$refs.replyInput.focus()
        this.$toast({
          message: '输入内容为空！',
          duration: 1300
        })
      } else { // 发布评论
        // https://afs7hx.toutiao15.com/addReply
        axios.post('https://afs7hx.toutiao15.com/addReply', {
          // username: 'jack',
          // comment_id: '5ec63598f485ab00753c1ede',
          username: this.username,
          comment_id: this.$route.params.comment_id,
          content: this.replyInputContent
        }, {
          // params: {
          //   // username: this.username,
          //   username: 'jack',
          //   comment_id: '5ec63598f485ab00753c1ede',
          //   content: this.replyInputContent
          // }
        })
          .then(res => {
            console.log(this.$route.params.comment_id)
            if (res.status === 200) { // 发布成功
              this.onLoad()
              this.$refs.replyInput.blur()
              this.ifShowKeybord = false
              this.replyInputContent = ''
              this.$toast({
                message: '评论成功',
                duration: 1300
              })
            }
            console.log(res)
          })
          .catch(err => {
            this.$toast('发布失败，请稍后重试')
            console.log(err)
          })
      }
    },
    // 弹窗评论输入框和键盘
    showKeybord () {
      this.ifShowKeybord = true
      this.$nextTick(() => {
        this.$refs.replyInput.focus()
      })
    },
    // 屏幕滚动响应事件
    myTouchMove (evt) {
      if (document.hasFocus()) { // 任一元素获取焦点
        // 输入框失去焦点,隐藏键盘
        // this.$refs.replyInput.blur()
        this.ifShowKeybord = false
      }
    },
    // 屏幕点击响应事件
    myTouch (evt) {
      if (evt.target !== this.$refs.buttonReply) {
        // this.$refs.replyInput.blur()
        this.ifShowKeybord = false
      }
    },
    onClickLeft () {},
    // 加载回复
    onLoad () {
      setTimeout(() => {
        if (this.refreshing) {
          this.list = []
          this.refreshing = false
        }
        // axios.get('https://afs7hx.toutiao15.com/judgeLikeComment')
        axios.get('https://afs7hx.toutiao15.com/getReplyList', {
          params: {
            username: this.username,
            // username: 'jack',
            // comment_id: '5ec63598f485ab00753c1ede'
            // username: this.$route.query.username,
            comment_id: this.$route.params.comment_id
          }
        }).then(_d => {
          console.log('reply')
          if (_d.status === 200) {
            // 将所有回复数据添加到list中
            this.list = _d.data
            this.replyCount = _d.data.length
          } else {
            this.$toast('请求失败，请稍后重试')
          }
          if (_d.data === this.list) {
            this.finished = true // 加载完所有评论
          }
        }).catch(err => {
          this.$toast('请求失败，请稍后重试')
          console.log(err)
        })
        this.loading = false // 加载结束
      }, 1000)
    },
    onRefresh () {
      // 清空列表数据
      this.finished = false
      // 重新加载数据
      // 将 loading 设置为 true，表示处于加载状态
      this.loading = true
      this.onLoad()
    }
  },

  watch: {
    // 发布按钮变色
    replyInputContent: function (newValue, oldValue) {
      console.log(newValue)
      if ((oldValue === '' || oldValue === null) && (newValue !== null && newValue !== '')) {
        console.log('变蓝色')
        this.$refs.buttonReply.classList.add('button-reply-blue')
      }
      if ((oldValue !== '' && oldValue !== null) && (newValue === null || newValue === '')) {
        console.log('变灰色')
        this.$refs.buttonReply.classList.remove('button-reply-blue')
      }
    }
  },
  mounted () {
    // 监听屏幕滚动
    window.addEventListener('touchmove', this.myTouchMove)
    window.addEventListener('touchstart', this.myTouch)
    // 获取新闻ID
    this.newsId = this.$route.params.newsId
    console.log(this.newsId)
  }
}

</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style lang="scss" scoped>
  .header {
    padding-top: 40px;
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

  .footer-fixed {
    position: fixed;
    bottom: 0;
    width: 100%;
    // border-top: 1PX solid #e4e4e4;
    border-top: 1PX solid #f0f0f0;
    background-color: white;
    @include themify{
      border-top: themed('footer-fixed-bd-top');
      background-color: themed('footer-fixed-bg-color');
    }
    z-index: 999;
  }

  //底部栏——输入框
  .footer-input {
    display: flex;

    //textaret-wrap
    .van-cell {
      padding: 12px 0 12px 20px;
      width: auto;
      flex: auto;

      @include themify {
        background-color: themed('trigger-input-wrap-bg-color');
      }
    }

    // textarea
    /deep/ .van-field__control {
      padding: 7px 10px;
      height: 70px;
      border-radius: 5px;
      border: 1Px solid #EEEEEE;
      font-size: 16px;
      background-color: #f0f0f0;
      caret-color: #66A2E4;

      @include themify {
        background-color: themed('trigger-input-bg-color');
        border: themed('trigger-input-bg-color');
        color: themed('trigger-input-font-color');
      }

      &::placeholder {
        font-size: 16px;
        color: rgb(187, 186, 186);
      }
    }

    //button
    .button-reply {
      margin: 0 15px;
      font-size: 17px;
      font-weight: bolder;
      margin-top: auto;
      margin-bottom: auto;
      line-height: inherit;
      color: #B7B7B7;
    }

    .button-reply-blue {
      color: #66A2E4;

      @include themify {
        color: themed('button-reply-color')
      }
    }
  }

  //底部栏
  .footer-col {
    position: fixed;
    bottom: 0;
    width: 100%;
    height: 45px;
    border-top: 1PX solid #e4e4e4;
    z-index: 999;
    background-color: white;
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 30px 0 15px;
    box-sizing: border-box;

    // van-field 输入框
    .van-cell {
      width: 65%;
      background-color: #e9e9e9;
      height: 35px;
      border-radius: 25px;
      font-size: 18px;
      line-height: 36px;
      padding: 0 15px;
    }
  }

  .footer {
    padding-top: 45px;
  }

  // 评论项目
  .reply-block {
    margin: 0;
    padding: 15px 15px 10px 15px;
    display: flex;
    justify-content: space-between;
    border-bottom: 1Px solid rgb(240, 240, 240);
    @include themify {
      border-bottom: 1Px solid themed('reply-block-bd-color');
    }
// =======
    // border-bottom: .6px solid rgb(240, 240, 240);
  }

  .reply-block-left {
    display: flex;
    width: 11%;

    .user-profile {
      margin-top: 3px;
      height: 36px;
      width: 36px;
      border-radius: 50%;
      // background-color: cadetblue;

    }
  }

  .reply-block-right {
    padding: 0 0 0 11px;
    width: 89%;
  }

  .reply-sub {
    height: 30px;
    /* 行高为0 */
    font-size: 15px;
    display: flex;
    justify-content: space-between;

    .reply-sub-info {
      height: 30px;
      color: cornflowerblue;
      justify-content: space-between;

      .reply-if-lz {
        // display: inline-block;
        display: inline;
        // width: 20%;
        font-size: 80%;
        border: .6px solid cornflowerblue;
      }

      .reply-space {
        display: inline;
        font-size: 25%;
      }

      .reply-user-name {
        display: inline;
        flex-grow: 1;
      }
    }

    .reply-interaction-wrap {
      display: flex;
      transform: translateY(-10%);
      // min-width: 130px;
      justify-content: space-between;

      .marg {
        width: 10px;
      }

      .reply-inter {
        display: flex;
        // padding-left: 10px;
        align-items: center;

        .reply-inter-icon {
          margin-right: 5px;
          font-size: 22px;
          display: block;
        }

        .icon-dislike {
          // margin-left: 10px;
          transform: rotate(180deg);
        }
      }

      .reply-like {
        color: #ED6161;
      }

      // .reply-trample, .reply-not-trample {
      //   margin-left: 10px;
      // }

    }
  }

  .reply-content {
    font-size: 17px;
    line-height: 23px;
    padding-right: 15px;
    text-align: justify;
    margin-bottom: 2px;
  }

  .reply-block-de {
    display: block;
    font-size: 15px;
    // line-height: 35px;
    // color: #5f5f5f;
    // border-top: .6px solid #a2a0a0;
// =======
    color: #7d7d7d;
    border-top: 1Px solid  #a2a0a0;
    text-align: center;
    padding: 10px, 0, 0, 20px;

    .reply-block-de-text {
      margin-top: 8px;
      margin-left: 20px;
      margin-bottom: 0;
    }
  }

  .reply-bottom {
    margin-top: 2px;
    display: flex;
    align-items: center;
    font-size: 13px;

    span {
      display: block;
      height: 30px;
      line-height: 30px;
    }

    .reply-time {
      color: rgb(189, 189, 189);
    }
  }

  //底部栏
  .footer-col {
    height: 45px;
    // border-top: 1PX solid #e4e4e4;
    // z-index: 999;
    background-color: white;
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 30px 0 15px;
    box-sizing: border-box;

    @include themify {
      border-top: themed('footer-fixed-bd-top');
      background-color: themed('footer-fixed-bg-color');
    }

    // van-field 输入框
    .trigger-input {
      display: flex;
      min-width: 95%;
      flex: 0 0 auto;
      background-color: #f0f0f0;
      height: 35px;
      border-radius: 25px;
      font-size: 18px;
      line-height: 36px;
      padding: 0 15px;
      align-items: center;

      @include themify {
        background-color: themed('trigger-input-bg-color');
      }

      i {
        display: block
      }

      .i-write {
        transform: translateY(-5%);
        color: #888888;
      }

      span {
        font-size: 15px;
        margin-left: 5px;
        display: block;
        color: #a5a4a4;
      }

    }

    .i-com {
      position: relative;
      color: rgb(51, 51, 51);
      top: 1px;
      margin-left: -10px;
    }
  }

</style>
