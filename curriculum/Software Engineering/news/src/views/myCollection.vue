<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <router-link to="/my_center">
          <van-icon id="nav-left-icon" name="arrow-left" @click="goLastPage" />
        </router-link>
        <span>我的收藏({{ replyCount}})</span>
      </div>
    </div>
    <!-- 评论和评论回复，下拉刷新，瀑布流 -->
    <van-pull-refresh v-model="refreshing" @refresh="onRefresh">
      <van-list
        v-model="loading"
        :finished="finished"
        finished-text="没有更多收藏了"
        @load="onLoad"
      >
        <!-- 评论项 -->
        <router-link class="news-card-cell" v-for="(item, index) in list" :key="index"
          :to='/news_details/ + item.news_id'>
          <!-- 纯文字新闻 -->
          <div class="news-card card-words" v-if="hasImage(item)">
            <div class="skip">
              <div class="news-info">
                <h3 class="news-title">
                  {{item.news_title}}
                </h3>
                <div class="news-detail">
                  <span class="news-source">{{ item.source }}</span>
                  <!-- <span class="news-comments">{{ transNumber(item.comment_count) + '评论' }}</span> -->
                  <span class="news-time">{{ transTime(item.create_time) }}</span>
                </div>
              </div>
            </div>
          </div>
          <!-- 单图 -->
          <div class="news-card card-one-pic" v-else>
            <div class="skip">
              <div class="news-info">
                <h3 class="news-title">
                  {{item.news_title}}
                </h3>
                <div class="news-detail">
                  <span class="news-source">{{ item.source }}</span>
                  <!-- <span class='news-comments'>{{ transNumber(item.comment_count) + '评论' }}</span> -->
                  <span class='news-time'>{{ transTime(item.create_time) }}</span>
                </div>
              </div>
              <div class="news-image">
                <img :src="item.news_img_url" alt="测试">
              </div>
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
  name: 'myCollection',
  data () {
    return {
      ifLogin: false,
      // username: 'test123',
      replyCount: 0, // 收藏数量
      list: [], // 获取的收藏列表
      loading: false, // 是否正在加载
      finished: false, // 是否加载完成
      refreshing: false // 是否刷新
    }
  },
  created () {
    // 获取收藏列表
    console.log(this.$store.getters.ifLogin)
    // axios.get('http://localhost:3344/my_favorite')
    axios.get('https://afs7hx.toutiao15.com/getLikeNewsList', {
      params: {
        username: this.username
      }
    })
      .then(_d => {
        if (_d.status === 200) {
          this.list = _d.data.data
          this.replyCount = _d.data.data.length
          console.log(_d)
        } else {
          this.$toast('请求失败，请稍后重试')
        }
      })
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
    goLastPage () {
      this.$router.push('/my_center')
    },
    // 获取收藏数据，加载数据
    onLoad () {
      // if (this.$store.getters.ifLogin) {
      //   this.$router.push('/my_center')
      // }
      setTimeout(() => {
        if (this.refreshing) {
          this.list = []
          this.refreshing = false
        }
        // axios.get('http://localhost:3344/my_favorite', {
        axios.get('https://afs7hx.toutiao15.com/getLikeNewsList', {
          params: {
            username: this.username
          },
          headers: {}
        }).then(_d => {
          if (_d.status === 200) {
            this.list = _d.data.data
            console.log(this.list)
          } else {
            this.$toast('请求失败，请稍后重试')
          }
          if (_d.data.data === this.list) {
            this.finished = true // 加载完所有评论
          }
        }).catch(err => {
          this.finished = true // 加载完所有评论
          this.$toast('请求失败，请稍后重试')
          console.log(err)
        })
        this.loading = false
      }, 1000)
    },
    // 判断新闻是否有图片封面
    hasImage (newsItem) {
      if (newsItem.news_img_url === '') {
        return true
      }
      return false
    },
    // 修改呈现时间
    transTime (dateTime) {
      return this.$transTime(dateTime)
    },
    // 修改评论
    transNumber (comments) {
      return this.$transNumber(comments)
    },
    onRefresh () {
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

  .news-time {
    padding-left: 15px;
  }

  .news-card {
    /* border: 1px solid; */
    border-bottom: 1px solid #f5f7f9;
    padding: 12px;
    @include themify {
      border: themed('col-border-color');
    }
  }

  .card-words .skip,
  .card-one-pic .skip {
    display: flex;
    align-items: flex-start;
    justify-content: space-between;
  }

  .card-words .news-info,
  .card-one-pic .news-info {
    flex: 1 1 auto;
  }

  .news-title {
    margin: 0;
    /* padding: 0; */
    font-size: 17px;
    font-weight: normal;
    color: #333;
    padding-right: 5px;
    @include themify {
      color: themed('col-title-color');
    }
  }

  .news-detail {
    margin-top: 7px;
    font-size: 12px;
    color: #b4b4b4;
    @include themify {
      color: themed('col-detail-color');
    }
  }

  .news-detail span {
    padding-right: 6px;
  }

  .card-one-pic .news-image {
    /*flex: 0 0 auto */
    flex: none;
    width: 116px
  }

  .card-one-pic .news-image img {
    height: 70px;
    display: block;
    width: 100%;
    /* border: 1px solid; */
    background-color: #66AECA;
  }

  .card-three-pics .news-image {
    margin-top: 7px;
    display: flex;
    justify-content: space-between;
    align-items: center;
  }

  .card-three-pics .news-image img {
    width: 115px;
    height: 70px;
    flex: none;
    /* border: 1px solid; */
    background-color: #66A2E4;
  }

</style>
