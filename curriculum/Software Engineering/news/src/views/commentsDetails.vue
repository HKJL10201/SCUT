<template>
  <div>
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <!-- <router-link to="$router.go(-1)"> -->
        <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()" />
        <!-- </router-link> -->
        <span>评论详情</span>
      </div>
    </div>
    <!-- 评论 -->
    <div class="comments-wrap">
      <!-- 热评 -->
      <!-- <div class="hotComments-wrap">
        <div class="label">热门评论</div>
        <commentsList v-if="hotComments !== null && hotComments.length !== 0" class="comments-list"
          :commentsList.sync='hotComments' :newsId='newsId' :userId="userId">
        </commentsList>
        <div v-else class="comment-empty">
          暂无评论，快来抢沙发~
        </div>
      </div> -->
      <!-- 全部评论 -->
      <div class="allComments-wrap">
        <div class="label">全部评论</div>
         <!-- 评论列表 -->
        <commentsList v-if="allComments !== null && allComments.length !== 0" class="comments-list"
          :commentsList.sync='allComments' :newsId='newsId' :userId="userId">
        </commentsList>
        <!-- 暂无评论 -->
        <div v-else class="comment-empty">
          暂无评论，快来抢沙发~
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import commentsList from '@/components/commentsList'

export default {
  name: 'commentsDetails',
  components: {
    commentsList: commentsList
  },
  data () {
    return {
      newsId: '',
      hotComments: '',
      allComments: ''
    }
  },
  methods: {
    // 获取热评
    // gethotComments () {
    //   this.$axios.get('/news_details/' + this.newsId + '/hot_comments')
    //     .then(response => {
    //       if (response.data) {
    //         this.hotComments = response.data
    //         console.log(this.hotComments)
    //       }
    //     })
    // }
    gethotComments () {
    //   this.$axios.get('/news_details/' + this.newsId + '/hot_comments')
    //     .then(response => {
    //       if (response.data) {
    //         this.hotComments = response.data
    //         console.log(this.hotComments)
    //       }
    //     })
    // }
      this.$axios.post('https://afs7hx.toutiao15.com/getCommentList', {
        username: this.userId,
        news_id: this.newsId
      }).then(response => {
        console.log(response)
        if (response.status === 200) {
          this.hotComments = response.data
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 获取所有评论
    getAllComments () {
      this.$axios.post('https://afs7hx.toutiao15.com/getCommentList', {
        username: this.userId,
        news_id: this.newsId
      }).then(response => {
        console.log(response)
        if (response.status === 200) {
          this.allComments = response.data.comment_list
        } else {
          this.$toast('请求失败')
        }
      })
    }
  },
  computed: {
    userId: function () {
      if (this.$store.state.user !== null && this.$store.state.user !== '') {
        return this.$store.state.user.username
      } else {
        return ''
      }
    }
  },
  created () {
    // 获取新闻ID
    this.newsId = this.$route.params.news_id
    // 获取热门评论
    this.gethotComments()
    // 获取全部评论
    this.getAllComments()
    // this.$axios.post('/news_details/234234234/comments/', {
    // news_id: this.$route.params.news,
    // })
    // 请求评论, 携带参数新闻ID, 用户ID(检查是否已点赞过)
  }
}

</script>

<style scoped lang="scss">
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

  .comments-wrap {
    // margin-top: 10px;
    padding-top: 13px;
    background-color: white;
    @include themify {
      background-color: themed('theme-bg-color');
    }

    .hotComments-wrap .label {
      text-align: center;
      font-size: 18px;
      color: #F74444;
    }

    .allComments-wrap .label {
      text-align: center;
      font-size: 18px;
      color: #66A2E4;
    }
  }

  .comment-empty {
    margin-top: 10px;
    text-align: center;
    font-size: 14px;
    padding-bottom: 20px;
  }

</style>
