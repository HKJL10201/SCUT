<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/my_center">
          <van-icon id="nav-left-icon" name="arrow-left" @click="goLastPage" />
        </router-link>
        <span>我的评论({{ replyCount}})</span>
      </div>
    </div>
    <!-- 评论和评论回复，下拉刷新，瀑布流 -->
    <van-pull-refresh v-model="refreshing" @refresh="onRefresh">
      <van-list
        v-model="loading"
        :finished="finished"
        finished-text="没有更多评论了"
        @load="onLoad"
      >
        <!-- 评论项 -->
        <!-- <div class="reply-block" v-for="(item, index) in list" :key="index"> -->
        <!-- <router-link class="reply-block" v-for="(item, index) in list" :key="index"
          :to="{path:'/reply', query: {news_id: item.news_id, comment_id: item.is_reply === true ? item.comment_id: item._id}}"> -->
        <!-- <router-link class="reply-block" v-for="(item, index) in list" :key="index"
          :to="/news_details/ + item.news_id + /comments/ + item.is_reply === true ? item.comment_id: item._id"> -->
        <!-- <router-link class="reply-block" v-for="(item, index) in list" :key="index"
          :to="{name: 'reply', params: { news_id: item.news_id, comment_id: item.is_reply === true ? item.comment_id: item._id }}"> -->
        <!-- <router-link class="reply-block" v-for="(item, index) in list" :key="index"
          :to="{name: 'reply', params: { n_abcd: item.news_id, nefg_id: item.comment_id}}"> -->
        <router-link class="reply-block"  v-for="(item, index) in list" :key="index"
          :to="/news_details/ + item.news_id + /comments/ + (item.is_reply === true ? item.comment_id: '')">
          <!-- 上侧部分 -->
          <div class="reply-block-content" >
            <!-- 标题名, 点赞图标 -->
            <div class="reply-news-title">
                <div class="reply-news-title-style" v-if="item.is_reply === true">——{{item.quote.news_title}}</div>
                <div class="reply-news-title-style" v-else>——{{item.news_title}}</div>
            </div>
            <!-- 我的回复/评论内容 -->
            <div class="my-reply-content">
                {{item.content}}
            </div>
            <!-- 我回复的评论的评论内容 -->
            <div class="reply-content"  v-if="item.is_reply === true">
              <div class="reply-user-name">
                {{item.quote.nickname}}
              </div>
              :{{item.quote.content}}
            </div>
            <!-- </div> -->
            <!-- 发布时间 -->
            <div class="reply-time">
              {{item.createdAt}}
            </div>
          </div>
        <!-- </div> -->
        </router-link>
      </van-list>
    </van-pull-refresh>
  </div>
</template>

<script>
import axios from 'axios'
export default {
  name: 'myComment',
  data () {
    return {
      // text: '',
      replyCount: 0, // 收藏数量
      curReplyCount: 0, // 本次请求获得的收藏数量
      list: [], // 获取的收藏列表
      loading: false, // 是否正在加载
      finished: false, // 是否加载完成
      refreshing: false, // 是否刷新
      pageNum: 1, // 页数
      pageSize: 20 // 每页加载的评论数
    }
  },
  created () {
    // axios.get('http://localhost:3344/my_comment')
    // axios.get('https://afs7hx.toutiao15.com/getMyComment', {
    //   params: {
    //     username: this.username,
    //     // pageNum: this.pageNum,
    //     // pageSize: this.pageSize
    //     pageNum: 1,
    //     pageSize: this.pageSize
    //   }
    //   // headers: {}
    // })
    // axios.post('https://afs7hx.toutiao15.com/getMyComment', {
    //   username: this.username,
    //   pageNum: this.pageNum,
    //   pageSize: this.pageSize
    // }, {})
    //   .then(_d => {
    //   //   this.list = _d.data
    //   //   this.replyCount = _d.data.length
    //     if (_d.data.data) {
    //       this.list = _d.data.data
    //       console.log(this.list[0])
    //       this.replyCount = _d.data.data.length
    //     }
    //     if (_d.data.data === this.list) {
    //       this.finished = true // 加载完所有评论
    //     }
    //     console.log('uuu')
    //     console.log(_d.data.data)
    //     console.log(_d.data.data.length)
    //   })
  },
  computed: {
    username: function () {
      return this.$store.state.user.username
    },
    nickname: function () {
      return this.$store.state.user.username
    }
  },
  methods: {
    // 返回上一页
    goLastPage () {},
    // 跳转到评论详情页
    goCommentsPage () {},
    myTouchMove (evt) {
      if (document.hasFocus) {
        // 输入框失去焦点,隐藏键盘
        this.$refs.comInput.blur()
        // console.log('失去焦点')
      }
    },
    onClickLeft () {},
    onLoad () {
      setTimeout(() => {
        if (this.refreshing) {
          this.list = []
          this.refreshing = false
          this.pageNum = 1
        }
        // axios.get('http://localhost:3344/my_comment')
        // axios.get('https://afs7hx.toutiao15.com/getMyComment', {
        //   params: {
        //     username: this.username,
        //     pageNum: 1,
        //     pageSize: 25
        //   }
        //   // headers: {}
        // })
        axios.post('https://afs7hx.toutiao15.com/getMyComment', {
          username: this.username,
          pageNum: this.pageNum,
          pageSize: this.pageSize
        }, {})
          .then(_d => {
            if (_d.status === 200) {
              // 将每页获取的数据添加到list列表中
              this.list.push(..._d.data.data)
              this.curReplyCount = _d.data.data.length
              console.log(this.pageNum, '  onLoad')
              console.log(this.list)
              console.log(_d.data.data)
              // 当前页面的数据项数目
              this.replyCount = this.list.length
              this.loading = false // 加载结束
              this.pageNum += 1 // 加载下一页
              // 加载到最后一页
              if (this.curReplyCount !== this.pageSize) {
                console.log('finished')
                console.log(this.curReplyCount)
                console.log(this.pageSize)
                this.finished = true // 加载完所有评论
              }
              // console.log(_d.data.data.length)
            } else {
              this.$toast('请求失败，请稍后重试')
            }
          })
          .catch(err => {
            this.finished = true // 加载完所有评论
            this.$toast('请求失败，请稍后重试')
            console.log(err)
          })
        // this.loading = false
        // if (this.list.length >= 40) {
        //   this.finished = true;
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
  .reply-news-title{
    height: 22px;
    /* 行高为0 */
    display: flex;
    justify-content: space-between;

    .reply-news-title-style{
        overflow: hidden;
        text-overflow:ellipsis;
        white-space: nowrap;
        font-style: oblique;
        color: #aaa;
        width: 300px;
        font-size: 13px;
        @include themify {
          color: themed('thumb-up-sub-title-color');
        }
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

  .reply-time {
    margin: 5px 0 0 4px;
    display: flex;
    align-items: center;
    font-size: 12px;
    color:rgb(189, 189, 189);
          @include themify {
        color: themed('thumb-up-sub-title-color');
      }
// =======
    // font-size: 12px;
    // color:rgb(189, 189, 189);
  }

  // 评论项目
  .reply-block {
    margin: 0;
    padding: 15px 15px 10px 15px;
    display: flex;
    justify-content: space-between;
    border-bottom: 1Px solid rgb(224, 224, 224);
    // border-bottom: .6px solid rgb(240, 240, 240);
    .reply-block-content{
      width: 100%;
    }
    @include themify {
      border-bottom: 1Px solid themed('reply-block-bd-color');
    }
  }

  .reply-content {
    font-size: 16.5px;
    line-height: 26.5px;
    text-align: justify;
    margin: 4px 0 0 0;
    width: 94%;
    // display: -webkit-box;
    // -webkit-box-orient: vertical;
    // -webkit-line-clamp: 3;
    // overflow: hidden;
    background-color: rgb(233, 233, 233);
    color: rgb(154, 154, 154);
    padding: 5px 10px;
    border-radius: 7px;
    border: solid 1Px rgb(209, 209, 209);
    @include themify {
      background-color: themed('reply-content-bg-color');
      border: 1Px solid themed('reply-content-bd-color');
    }

    .reply-user-name {
      flex-grow: 1;
      color: cornflowerblue;
      display:inline;
    }
  }

  .my-reply-content{
    width: 100%;
    margin: 0;
    font-size: 16.5px;
    line-height: 26.5px;
    color:rgb(0, 0, 0);
    @include themify {
      color: themed('thumb-up-content-color');
    }
  }

</style>
