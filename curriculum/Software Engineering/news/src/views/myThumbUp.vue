<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/my_center">
          <van-icon id="nav-left-icon" name="arrow-left" @click="goLastPage" />
        </router-link>
        <span>我的点赞({{ replyCount}})</span>
      </div>
    </div>
    <!-- 我的点赞，下拉刷新，瀑布流 -->
    <van-pull-refresh v-model="refreshing" @refresh="onRefresh">
      <van-list
        v-model="loading"
        :finished="finished"
        finished-text="没有更多点赞了"
        @load="onLoad"
      >
        <!-- 点赞项 -->
        <router-link class="thumb-up-block" v-for="(item, index) in list" :key="index"
          :to="/news_details/ + item.news_id + /comments/ + (item.is_reply === true ? item.comment_id: '')">
          <div class="thumb-up-block-contant">
            <!-- 标题名, 点赞图标 -->
            <div class="thumb-up-sub">
              <!-- 点赞新闻标题 -->
              <div class="thumb-up-sub-title" v-if="item.is_reply === true">——{{item.quote.news_title}}</div>
              <div class="thumb-up-sub-title" v-else>——{{item.news_title}}</div>
              <!-- 点赞 -->
              <van-icon class="thumb-up-like" size="150%" name="good-job"></van-icon>
            </div>
            <!-- 评论内容 -->
            <div class="thumb-up-content">
              <div class="thumb-up-username">{{item.nickname}}</div>
              :{{item.content}}
            </div>
            <!-- 底部 -->
            <div class="thumb-up-bottom">
              <!-- <span class="thumb-up-time">{{item.create_time}}</span> -->
              <span class="thumb-up-time">{{item.updatedAt}}</span>
              <router-link to="/home">
              </router-link>
            </div>
          </div>
        </router-link>
      </van-list>
    </van-pull-refresh>
  </div>
</template>

<script>
import axios from 'axios'
export default {
  name: 'myThumbUp',
  data () {
    return {
      // username :'',
      replyCount: 0, // 收藏数量
      curReplyCount: 0, // 本次请求获得的收藏数量
      list: [], // 获取的收藏列表
      loading: false, // 是否正在加载
      finished: false, // 是否加载完成
      refreshing: false, // 是否刷新
      pageNum: 1, // 页数
      pageSize: 12 // 每页加载的评论数
    }
  },
  created () {
    // axios.get('http://localhost:3344/my_thumb_up')
    // axios.get('https://afs7hx.toutiao15.com/getLikeComment', {
    //   params: {
    //     username: this.username,
    //     pageNum: this.pageNum,
    //     pageSize: this.pageSize
    //   },
    //   headers: {}
    // }).
    // axios.post('https://afs7hx.toutiao15.com/getLikeComment', {
    //   username: this.username,
    //   pageNum: this.pageNum,
    //   pageSize: this.pageSize
    // }).then(_d => {
    //   this.list = _d.data.data
    //   this.replyCount = _d.data.data.length
    //   console.log(_d.data.data)
    //   console.log(this.replyCount)
    // })
  },
  computed: {
    username: function () { // 已登录的用户ID
      return this.$store.state.user.username
    },
    nickname: function () { // 已登录的用户昵称
      return this.$store.state.user.nickname
    }
  },
  methods: {
    // 返回上一页
    goLastPage () {},
    // 跳转到评论详情页
    goCommentsPage () {

    },
    onLoad () {
      setTimeout(() => {
        if (this.refreshing) {
          this.list = []
          this.curReplyCount = 0
          this.refreshing = false
          this.pageNum = 1
        }
        // axios.get('http://localhost:3344/my_thumb_up', {
        // axios.get('https://afs7hx.toutiao15.com/getLikeComment', {
        //   params: {
        //     username: this.username,
        //     pageNum: this.pageNum,
        //     pageSize: this.pageSize
        //   },
        //   headers: {}
        // }).
        axios.post('https://afs7hx.toutiao15.com/getLikeComment', {
          username: this.username,
          pageNum: this.pageNum,
          pageSize: this.pageSize
        }).then(_d => {
          this.replyCount = 0
          if (_d.status === 200) {
            // 将每页获取的数据添加到list列表中
            this.list.push(..._d.data.data)
            this.curReplyCount = _d.data.data.length
            console.log(this.list)
            console.log(_d.data.data)
            // 当前页面的数据项数目
            this.replyCount = this.list.length
            this.loading = false // 加载结束
            if (this.curReplyCount !== this.pageSize) {
              console.log('finished')
              console.log(this.curReplyCount)
              console.log(this.pageSize)
              this.finished = true // 加载完所有评论
            }
            this.pageNum += 1 // 加载下一页
          } else {
            this.$toast('请求失败，请稍后重试')
          }
        }).catch(err => {
          this.finished = true // 加载完所有评论
          this.$toast('请求失败，请稍后重试')
          console.log(err)
        })
        // this.loading = false

        // this.pageNum += 1
        // if (this.curReplyCount !== this.pageSize) {
        //   console.log('finished')
        //   console.log(this.curReplyCount)
        //   console.log(this.pageSize)
        //   this.finished = true
        // }
      }, 1000)
    },
    onRefresh () {
      this.list = []
      // 清空列表数据
      this.finished = false
      // 重新加载数据
      // 将 loading 设置为 true，表示处于加载状态
      this.loading = true
      this.onLoad()
    }
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

  // 评论项目
  .thumb-up-block {
    margin: 0;
    padding: 10px 15px 10px 15px;
    display: flex;
    justify-content: space-between;
    border-bottom: 1Px solid rgb(240, 240, 240);
    @include themify {
      border-bottom: 1Px solid themed('thumb-up-border-color');
    }
// =======
    // border-bottom: .6px solid rgb(240, 240, 240);

    .thumb-up-block-contant {
      width: 100%;
    }
  }

  .thumb-up-sub {
    height: 22px;
    /* 行高为0 */
    font-size: 12px;
    display: flex;
    justify-content: space-between;
    width: 100%;

    .thumb-up-sub-title{
      overflow: hidden;
      text-overflow:ellipsis;
      white-space: nowrap;
      font-style: oblique;
      color: #bfbfbf;
      width: 250px;
      font-size: 13px;
      width: 80%;
      @include themify {
        color: themed('thumb-up-sub-title-color');
      }
    }

    .thumb-up-like {
      display: flex;
      transform: translateY(-10%);
      // min-width: 130px;
      justify-content: space-between;
      color: #ED6161;
    }
  }

  .thumb-up-content {
    font-size: 16.5px;
    line-height: 27px;
    padding-right: 15px;
    text-align: justify;
    margin-bottom: 2px;
    display: -webkit-box;
    -webkit-box-orient: vertical;
    -webkit-line-clamp: 3;
    overflow: hidden;
    display:inline;
    color: #000;
    @include themify {
        color: themed('thumb-up-content-color')
    }

    .thumb-up-username {
      flex-grow: 1;
      color: cornflowerblue;
      display:inline;
      @include themify {
        color: themed('thumb-up-username-color')
      }
    }
  }

  .thumb-up-bottom {
    margin-top: 4px;
    display: flex;
    align-items: center;
    font-size: 13px;

    .thumb-up-time {
      color:rgb(189, 189, 189);
      @include themify {
        color: themed('thumb-up-time-color')
      }
      font-size: 12px;
    }
  }

</style>
