<template>
  <div>
    <div class="reply-block" v-for="(item, index) in myCommentsList" :key="item.comment_id">
      <!-- <div v-if="0" class="comments-list"> -->
      <!-- <div class="reply-block" v-for="(item, index) in hotComments" :key="index"> -->

      <!-- 左侧头像 -->
      <div class="reply-block-left" v-if="!noPicMode">
        <img class="user-profile" :src="item.user.avatar_url" />
      </div>
      <!-- 右侧部分 -->
      <div class="reply-block-right">
        <!-- 用户名, 点赞/踩 -->
        <div class="reply-sub">
          <div class="reply-user-name reply-sub-info">{{item.user.name}}</div>
          <!-- 点赞/踩 wrap -->
          <div class="reply-interaction-wrap">
            <!-- 点赞 -->
            <transition name="fade" mode="out-in">
              <div class="reply-inter reply-like" v-if="item.user_like" @click="changeReplyLike(index)" key="like">
                <van-icon class="reply-inter-icon icon-if-like" name="good-job"></van-icon>
                <span>{{item.like_count}}</span>
                <i class=marg />
              </div>
              <div class="reply-inter reply-dislike" v-else @click="changeReplyLike(index)" key="dislike">
                <van-icon class="reply-inter-icon icon-if-like" name="good-job-o"></van-icon>
                <span>{{item.like_count}}</span>
                <i class=marg />
              </div>
            </transition>
            <!-- 踩 -->
            <transition name="fade" mode="out-in">
              <div class="reply-inter reply-oppose" v-if="item.user_oppose" @click="changeReplyOppose(index)"
                key="oppose">
                <van-icon class="reply-inter-icon icon-if-oppose" name="good-job"></van-icon>
                <!-- <svg-icon class="reply-inter-icon icon-oppose" icon-class="yicai"></svg-icon> -->
                <span>{{ item.oppose_count }}</span>
                <i class=marg />
              </div>
              <div class="reply-inter reply-not-oppose" v-else @click="changeReplyOppose(index)" key="notOppose">
                <van-icon class="reply-inter-icon icon-if-oppose" name="good-job-o"></van-icon>
                <!-- <svg-icon class="reply-inter-icon icon-not-oppose" icon-class="cai_2"></svg-icon> -->
                <span>{{ item.oppose_count }}</span>
                <i class=marg />
              </div>
            </transition>
          </div>
        </div>
        <!-- 评论内容 -->
        <div class="reply-content">
          {{item.text}}
        </div>
        <!-- 底部 -->
        <div class="reply-bottom">
          <span class="reply-time"> {{ transTime(item.create_time) }} </span>
          <!-- <router-link :to="{path:'/reply', query: {username: item.comment_id} }"> -->
          <!-- <router-link  :to="/news_details/ + newsId + /comments/ + item.comment_id "> -->
          <router-link :to="/news_details/ + newsId + /comments/ + item.comment_id">
            <span class=reply-count> 回复({{ item.reply_count }})</span>
          </router-link>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'commentsList',
  props: ['commentsList', 'newsId', 'userId'],
  data () {
    return {
      myCommentsList: this.commentsList
    }
  },
  methods: {
    // 呈现评论时间
    transTime (dateTime) {
      return this.$transTime(dateTime)
    },
    // 评论,点赞,踩呈现数字转换
    transNumber (number) {
      return this.$transNumber(number)
    },
    // 点赞/取消点赞
    changeReplyLike (index) {
      // 判断是否已登录
      if (!this.$store.getters.ifLogin) { // 未登录，跳转到登录页
        this.$router.push({
          path: '/login',
          query: {
            redirect: this.$route.fullPath
          }
        })
        return
      }
      // console.log(index)
      const commentId = this.myCommentsList[index].comment_id
      if (this.myCommentsList[index].user_like === true) { // 取消点赞
        this.myCommentsList[index].user_like = false
        this.myCommentsList[index].like_count--
        // this.$axios.delete('/news_details/' + this.newsId + '/comments/' + commentId + '/like', {
        //   user_id: this.userId,
        //   comment_id: commentId
        // }).then(response => {
        //   if (response) {}
        // })
      } else { // 点赞
        this.myCommentsList[index].user_like = true
        this.myCommentsList[index].like_count++
        // this.$axios.post('/news_details/' + this.newsId + '/comments/' + commentId + '/like', {
        //   user_id: this.userId,
        //   comment_id: commentId
        // }).then(response => {
        //   if (response) {}
        // })
      }
      // 发起请求
      this.$axios.post('https://afs7hx.toutiao15.com/thumbsUp', {
        username: this.$store.state.user.username,
        comment_id: commentId
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          console.log(res.data)
          if (res.code === 1) {
            // this.$toast({
            //   message: 'commentId: ' + commentId + ' code1:' + res.msg + ' thumbs_up ' + res.data.thumbs_up + ' bb:' + this.bb,
            //   duration: 3000
            // })
          } else {
            // this.$toast({
            //   message: 'commentId: ' + commentId + ' code0:' + res.msg + ' thumbs_up ' + res.data.thumbs_up + ' bb:' + this.bb,
            //   duration: 3000
            // })
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 踩/取消踩
    changeReplyOppose (index) {
      // 判断是否已登录
      if (!this.$store.getters.ifLogin) { // 未登录，跳转到登录页
        this.$router.push({
          path: '/login',
          query: {
            redirect: this.$route.fullPath
          }
        })
        return
      }
      // console.log(index)
      const commentId = this.myCommentsList[index].comment_id
      if (this.myCommentsList[index].user_oppose === true) { // 取消踩
        this.myCommentsList[index].user_oppose = false
        this.myCommentsList[index].oppose_count--
        // this.$axios.delete('/news_details/' + this.newsId + '/comments/' + commentId + '/oppose', {
        //   user_id: this.userId,
        //   comment_id: commentId
        // }).then(response => {
        //   // if (response) {}
        // })
      } else { // 踩
        this.myCommentsList[index].user_oppose = true
        this.myCommentsList[index].oppose_count++
        // this.$axios.post('/news_details/' + this.newsId + '/comments/' + commentId + '/oppose', {
        //   user_id: this.userId,
        //   comment_id: commentId
        // }).then(response => {
        //   // if (response) {}
        // })
      }
      // 发起请求
      this.$axios.post('https://afs7hx.toutiao15.com/thumbsDown', {
        username: this.$store.state.user.username,
        comment_id: commentId
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          console.log(res.data)
          if (res.code === 1) {
            // this.$toast({
            //   message: 'commentId: ' + commentId + ' code1:' + res.msg + ' thumbs_up ' + res.data.thumbs_up + ' bb:' + this.bb,
            //   duration: 3000
            // })
          } else {
            // this.$toast({
            //   message: 'commentId: ' + commentId + ' code0:' + res.msg + ' thumbs_up ' + res.data.thumbs_up + ' bb:' + this.bb,
            //   duration: 3000
            // })
          }
        } else {
          this.$toast('请求失败')
        }
      })
    }
  },
  computed: {
    // 是否已开启省流量模式
    noPicMode: function () {
      return this.$store.state.noPicMode
    }
  },
  watch: {
    // 将更新同步到父组件列表数据
    myCommentsList: function () {
      this.$emit('update:commentsList', this.myCommentsList)
    },
    // 将父组件列表数据的更新同步到该列表
    commentsList: function (newValue) {
      this.myCommentsList = newValue
    }
  }
}

</script>

<style scoped lang="scss">
   // 评论项目
  .reply-block {
    margin: 0;
    padding: 15px 0px 10px 15px;
    display: flex;
    justify-content: space-between;
  }

  .reply-block-left {
    display: flex;
    width: 40px;

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
    width: 330px;
  }

  .reply-sub {
    // height: 30px;
    font-size: 15px;
    display: flex;
    justify-content: space-between;

    // margin-right: -5px;
    .reply-user-name {
      flex-grow: 1;
      color: cornflowerblue;
    }

    .reply-interaction-wrap {
      display: flex;
      margin-right: 10px;
      // transform: translateY(-10%);
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

        .icon-if-like {
          // margin-right: 5px;
        }

        .icon-if-oppose {
          // transform: scaleY(-1);
          transform: rotate(180deg);
        }

        .icon-oppose {
          font-size: 20px;
        }

        .icon-not-oppose {
          font-size: 19px;
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
    line-height: 27px;
    padding-right: 35px;
    text-align: justify;
    margin: 10px 0 0 0;
  }

  .reply-bottom {
    margin-top: 4px;
    display: flex;
    align-items: center;
    font-size: 13px;

    span {
      display: block;
      height: 35px;
      line-height: 35px;
    }

    .reply-time {
      color: #888888;
    }

    .reply-count {
      margin-left: 10px;
      color: #66A2E4;
    }
  }

  .fade-enter-active {
    transition: opacity .9s;
  }

  .fade-enter,
  .fade-leave-to {
    opacity: 0.3;
  }

</style>
