<template>
  <div id="news-details">
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
        <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()"/>
        <span>新闻详情</span>
      </div>
    </div>
    <van-loading type="spinner" v-if="!ifLoadingReady" class="loading" />
    <div v-else>
      <!-- 新闻 -->
      <div class="article-box">
        <h1 class="article-title">
          {{ newsDetails.title }}
        </h1>
        <div class="article-sub">
          <span class="news-source">{{newsDetails.source}}</span>
          <span class="news-time"> {{ newsDetails.publish_time }}</span>
        </div>
        <!-- 新闻内容 -->
        <!-- <video src="aHR0cDovL3YzLWRlZmF1bHQuaXhpZ3VhLmNvbS9jN2IzZDY1MDk4MWM2MGExNjA4YWU5NzFlZDcyM2Y2YS81ZWNkOTYwZC92aWRlby90b3MvY24vdG9zLWNuLXZlLTQvM2YxNThhMGU0YzJiNDEyYTkzOWU1NjdmNTkwNDZjZmYvP2E9MjAxMSZicj0yNDg0JmJ0PTgyOCZjcj0wJmNzPTAmZHI9MCZkcz0zJmVyPSZsPTIwMjAwNTI3MDUwOTM0MDEwMTk0MTAwMDEzM0UxQzBFQjUmbHI9Jm1pbWVfdHlwZT12aWRlbyUyRm1wNCZxcz0wJnJjPU16TmxiM0E4YW5WbWRUTXpPemN6TTBBcE56dzNaRGM3UER0b056czVabVkyYUdka01IRnVZMkZtY0ROZkxTMHVMUzl6YzJCZ1l5NWlYeTgyTVdNMFlHTXRNelk2WXclM0QlM0Qmdmw9JnZyPQ==">
        </video> -->
        <!-- <video controls @click="console.log(this)">
         <source
            src="http://v3-default.ixigua.com/abf54fcd0175eaee53b948323f0746d1/5ecd960d/video/tos/cn/tos-cn-ve-4/34b55620d6e041ac83a6f74a01d89d8a/?a=2011&br=1191&bt=397&cr=0&cs=0&dr=0&ds=2&er=&l=202005270509340101941000133E1C0EB5&lr=&mime_type=video/mp4&qs=0&rc=MzNlb3A8anVmdTMzOzczM0ApNTYzMzM4N2VmN2lnOjhlOWdkMHFuY2FmcDNfLS0uLS9zcy4vYzJgLjVgMWI2NmNiMmI6Yw==&vl=&vr="
            type="video/mp4">
        </video> -->
        <div class="article-content" v-html='newsDetails.content'>
        </div>
      </div>
      <!-- 评论 -->
      <div class="comments-wrap">
        <div class="label">热门评论</div>
        <!-- 评论项 -->
        <commentsList v-if="hotComments !== null && hotComments.length !== 0" class="comments-list"
          :commentsList.sync='hotComments' :newsId='newsId' :userId="userId">
        </commentsList>
        <!-- 暂无评论 -->
        <div v-else class="comment-empty">
          暂无评论，快来抢沙发~
        </div>
        <router-link :to="/news_details/ + newsId + /comments/">
          <div class="more-comments">
            查看更多
          </div>
        </router-link>
      </div>
      <!-- 底部栏——固定 -->
      <div class="footer">
        <!-- 键盘未弹出时的底栏 -->
        <div class="footer-col footer-fixed" v-show="!ifShowKeybord">
          <div class="trigger-input" @click="showKeybord">
            <!-- <van-icon name="comment-o" /> -->
            <svg-icon icon-class="write" class="i-write"></svg-icon>
            <span>写下你的评论...</span>
          </div>
          <!-- 评论数量 -->
          <router-link :to="/news_details/ + newsId + /comments/">
            <van-icon class="i-com" name="comment-o">
              <div class="i-tag"> {{ transNumber(newsDetails.comment_count) }} </div>
            </van-icon>
          </router-link>
          <!-- 收藏 -->
          <transition name="fade" mode="out-in">
            <div v-if="!ifCollected" key="not">
              <van-icon class="i-star star-off" name="star-o" @click="collectionHandle" />
            </div>
            <div v-else key="collect">
              <van-icon class="i-star star-on" name="star" @click="collectionHandle" />
            </div>
          </transition>
        </div>
        <!-- 键盘弹出时的评论框 -->
        <div class="footer-input footer-fixed" v-show="ifShowKeybord" @click.stop>
          <van-field placeholder="优质评论将会被优先展示" ref="replyInput" type="textarea" maxlength="50"
            v-model="replyInputContent">
          </van-field>
          <div class="button-reply" ref="buttonReply" @click="addReply">
            发布
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import commentsList from '@/components/commentsList'
export default {
  name: 'newsDetails',
  components: {
    commentsList: commentsList
  },
  data () {
    return {
      // userId: 1000011,
      newsId: '', // 新闻Id
      newsDetails: '', // 新闻内容
      hotComments: [], // 热评列表
      ifCollected: false, // 是否已收藏
      replyInputContent: '', // 评论输入内容
      // 是否有弹出键盘
      ifShowKeybord: false, // 是否展开键盘
      ifLoadingReady: false, // 是否加载完毕
      imgUrl: '', // 新闻封面图片
      title: '意大利外长：当初赠送中国4万只口罩被指责，如今对方回赠百万只',
      content: '当地时间24日，意大利外长迪马约在接受采访时表示，意大利疫情暴发后，中国第一个向意大利提供医疗物资，并派遣医疗专家。“当初武汉疫情暴发时，意大利向中国赠送了4万只口罩，而被指责廉价抛售了用来保护意大利人的物资。如今，中国回赠数百万只口罩。'
    }
  },
  methods: {
    // 添加/取消 收藏
    collectionHandle () {
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
      // 添加/取消收藏
      this.$axios.post('https://afs7hx.toutiao15.com/collectNews', {
        // username: 'test123',
        username: this.userId,
        news_id: this.newsId,
        news_title: this.newsDetails.title,
        news_img_url: this.imgUrl,
        source: this.newsDetails.source
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            this.ifCollected = !this.ifCollected
            this.$toast({
              message: res.msg,
              duration: 1300
            })
          } else {
            this.$toast({
              message: res.msg,
              duration: 1300
            })
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 添加评论
    addReply () {
      // 输入内容为空
      if (this.replyInputContent === '') {
        this.$refs.replyInput.focus()
        this.$toast({
          message: '输入内容为空！',
          duration: 1300
        })
      } else { // 发布评论
        // this.$axios.post('/news_details/' + this.newsId + '/comments/', {
        //   usr_id: this.userId,
        //   news_id: this.newsId,
        //   content: this.replyInputContent
        // }).then(response => {
        //   if (response.status === 200) { // 发布成功
        //     this.$refs.replyInput.blur()
        //     this.ifShowKeybord = false
        //     this.replyInputContent = ''
        //     this.$toast({
        //       message: '评论成功',
        //       duration: 1300
        //     })
        //   } else {
        //     this.$toast('请求失败')
        //   }
        // })
        this.$axios.post('https://afs7hx.toutiao15.com/addComment', {
          username: this.userId,
          news_id: this.newsId,
          news_title: this.newsDetails.title,
          content: this.replyInputContent
        }).then(response => {
          if (response.status === 200) {
            const res = response.data
            if (res.code === 1) {
              this.$refs.replyInput.blur() // 取消聚焦
              this.ifShowKeybord = false // 隐藏输入框
              this.replyInputContent = '' // 清空评论内容
              this.$toast('评论成功')
              this.newsDetails.comment_count++ // 评论数 + 1
              this.gethotComments() // 刷新评论
            } else {
              this.$toast(res.msg)
            }
          } else {
            this.$toast('请求失败')
          }
        })
      }
    },
    // 弹出评论输入框和键盘
    showKeybord () {
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
    // 获取新闻详情
    getNewsDetails () {
      this.$axios.post('https://afs7hx.toutiao15.com/getNewsDetails', {
        // news_id: '6706312322090009092'
        news_id: this.newsId
      }).then(response => {
        console.log(response)
        if (response.status === 200) {
          // console.log(response.data)
          this.newsDetails = response.data
          const tmp = response.data.content
          console.log(tmp)
          const chReg = /[^u4e00-u9fa5]+/g
          const result = tmp.replace(chReg, '')
          console.log(result)
          //
          this.handleNewsDetails() // 处理新闻内容标签
          this.ifLoadingReady = true // 显示加载完成
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 获取新闻热评
    gethotComments () {
      // this.$axios.get('/news_details/' + this.newsId + '/hot_comments')
      //   .then(response => {
      //     if (response.data) {
      //       this.hotComments = response.data
      //       // console.log(this.hotComments)
      //     }
      //   })
      this.$axios.post('https://afs7hx.toutiao15.com/getCommentList', {
        username: this.userId,
        news_id: this.newsId
      }).then(response => {
        console.log(response)
        if (response.status === 200) {
          this.hotComments = response.data.hot_comment_list
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 判断用户是否已收藏
    getCollectionInfo () {
      // 判断是否已登录
      if (!this.$store.getters.ifLogin) { // 未登录，不作处理
        return
      }
      // 发起判断请求
      this.$axios.post('https://afs7hx.toutiao15.com/judgeCollectedNews', {
        username: this.userId,
        news_id: this.newsId
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          if (res.code === 1) {
            if (res.data === true) {
              this.ifCollected = true
            } else {
              this.ifCollected = false
            }
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    // 获取新闻封面图
    getNewsImage () {
      if (typeof (this.$route.params.news_image) !== 'undefined') {
      // 路由参数中有, 则从路由参数中获取, 并存入state中
        if (this.$route.params.news_image && this.$route.params.news_image.length !== 0) {
          // console.log('从参数里获取: ' + this.$route.params.news_image)
          // console.log('从参数里获取: ' + this.$route.params.news_image[0])
          this.imgUrl = this.$route.params.news_image[0]
          this.$store.commit('setTmpNewsImage', this.imgUrl)
        } else {
          console.log('没有封面图片')
        }
      } else {
      // 路由参数中无，从stata中获取 (用于跳转至登录页面后再跳转回该页面)
        this.imgUrl = this.$store.state.tmpNewsImage
        // console.log('从stata里获取: ' + this.$store.state.tmpNewsImage)
      }
    },
    // 处理新闻内容
    handleNewsDetails () {
      // const p = '<p>受疫情的影响，现在全世界的体育运动都遭到重大打击，国内CBA停播、中超联赛迟迟未开，欧洲五大联赛和NBA也陷入停摆，目前仍没有开赛日期，而法甲直接宣布结束了。长时间没有体育比赛，不仅球员受不了，众多球迷朋友也十分渴望能看到比赛。球员渴望比赛不难理解，毕竟比赛给人分兴奋程度非长时间枯燥的训练可比。</p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/167ed9073c44497bb7921d58f43a23bb" img_width="365" img_height="495" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/769aea0cb1084994817e65edb754bf82" img_width="723" img_height="218" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>不过，球迷日盼夜盼的赛事终于要来了，中超公司于4月30日发了一个通知，将对各俱乐部的队内训练赛以及热身赛进行转播。通知要求各俱乐部在不影响正常训练的同时积极配合参与，这一决定也得到了不少球迷的鼓掌欢迎。“在没有比赛的日子里，能看到队内比赛和热身赛，也算是球迷的一种福利吧。中超公司也算是干了一件让球迷满意的事情。”“赶紧转吧，现在你别说是热身赛了，你播中学生比赛我都看。”从球迷的留言来看，大家可是对比赛的期盼是多么的热切。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/746c0ee6a0654d97890d1c3b9057fa66" img_width="640" img_height="427" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>诚然，在没有比赛看的日子，某些直播平台都一直复播旧比赛，此番中超公司也算作了一件好事，一是能满足球迷的观赛需求，二是能在转播方面增加一些收入。要知道，现在联赛一日未开，中超公司的损失就会逐渐增大，而对于俱乐部来说，也有一个展现良好形象的平台和机会，其实不少球迷对俱乐部的日常训练非常感兴趣，如果能拍一些球队日常训练的项目和技战术演练，相信也会得到球迷的喜爱。</p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/33ed5d8cbe09492e91fd4a24001536e9" img_width="626" img_height="472" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>而作为重点关注的国足热身赛也有很大的机会进行转播。目前，李铁率领的新一届国家队正在上海集训，据《北京青年报》的报道，本次集训练内容由基本的身体恢复、力量训练开始逐步注入“技战术元素”，同时兼顾耐力训练，训练强度也是由低向高。而在本次集训中，李铁也会安排两场热身赛以检验训练效果。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/e9eda778bdae48658c773ce9d896cb3b" img_width="640" img_height="427" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p><br></p><div class="pgc-img"><img src="https://p3.pstatp.com/large/dfic-imagehandler/8744eb3c-314a-4b36-92ac-96e1271882dd" img_width="1200" img_height="800" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>该报确认本次国足的热身对手将会是上海滩双雄上海申花和上海上港两支球队。而结合中超公司的通知，这两场比赛将有望转播，到时候李铁到底将国家队打造出怎样的效果到时候将揭晓。虽然国足在广州集训是分别打了两次热身赛，一场是8-0大胜中甲升班马沈阳建设，另一场是1-0小胜武汉卓尔，但这两场比赛球迷无缘相见。第二次在迪拜集训时有消息透露国足将与重庆、富力和深足进行热身，但最终还是流产了。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/db0475d37db9422fa44f3fa5ed3ad5c4" img_width="640" img_height="418" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>此番，与国足过招的无申花还是上港实力都非常强，申花在冬窗期引进了包括冯潇霆、曾诚、秦升、赵明剑等前国脚，而上港在保有奥斯卡、胡尔克、阿瑙托维奇、艾哈迈多夫等实力强劲的外援后还出手拿下了年度标王巴西强力前锋洛佩斯。两支球队阵容齐整，实力雄厚，作为2020重磅对决，值得期待。</p><p><br></p>'
      // 如果content没有标签, 则添加一个标签
      const regP = new RegExp('<.>', 'g')
      if (!regP.test(this.newsDetails.content)) {
        this.newsDetails.content = '<p>' + this.newsDetails.content + '</p>'
      }
      // 去除<br/>标签
      const regBr = new RegExp('<p( class="[a-zA-Z_-]+")?><br></p>', 'g')
      this.newsDetails.content = this.newsDetails.content.replace(regBr, '')
      // 开启省流量模式时, 去除img标签和video; 否则，不对img标签进行处理，
      if (this.noPicMode) {
        // 去除img标签
        const regImg = new RegExp('<img [^>]*>', 'g')
        this.newsDetails.content = this.newsDetails.content.replace(regImg, '')
        // 处理加载视频的div标签
        const regVideo = new RegExp('<div class="tt-video-box"[^>]*>[^<]*</div>', 'g')
        this.newsDetails.content = this.newsDetails.content.replace(regVideo, '')
      } else {
        // 未开启省流量模式, 检查是否存在视频
        const regVideoId = new RegExp('tt-videoid=\'[^\']*\'')
        const videoMatch = regVideoId.exec(this.newsDetails.content)
        // 存在视频
        if (videoMatch) {
          // 获取video ID
          const videoId = videoMatch[0].substr(11).replace(/'/g, '')
          console.log(videoId)
          // 获取新闻封面
          const regVideoPost = new RegExp('tt-poster=\'[^\']*\'')
          const videoPostMatch = regVideoPost.exec(this.newsDetails.content)
          const videoPost = videoPostMatch[0].substr(11).replace(/'/g, '')
          console.log(videoPost)
          this.$axios.post('https://afs7hx.toutiao15.com/getVideo', {
            videoId: videoId
          }).then(response => {
            if (response.status === 200) {
              const res = response.data
              const videoUrl = window.atob(res.data)
              const regVideo = new RegExp('<div class="tt-video-box"[^>]*>[^<]*</div>', 'g')
              const videoTag = '<video controls="controls" poster="' + videoPost + '"><source src="' + videoUrl + '" type="video/mp4"></video>'
              // const videoTag = '<video controls><source src="' + videoUrl + '" type="video/mp4"></video>'
              this.newsDetails.content = this.newsDetails.content.replace(regVideo, videoTag)
            } else {
              this.$toast('请求失败')
            }
          })
        } else {
          console.log('不存在视频')
        }
      }
    },
    // 评论,点赞,踩呈现数字转换
    transNumber (number) {
      return this.$transNumber(number)
    }
  },
  computed: {
    // 获取用户Id
    userId: function () {
      if (this.$store.state.user !== null && this.$store.state.user !== '') {
        return this.$store.state.user.username
      } else {
        return ''
      }
    },
    // 是否已开启省流量模式
    noPicMode: function () {
      return this.$store.state.noPicMode
    }
  },
  watch: {
    // "发布评论"按钮变色
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
  created () {
    // 获取新闻ID
    this.newsId = this.$route.params.news_id
    // 获取新闻封面图
    this.getNewsImage()
    // 获取新闻内容
    this.getNewsDetails()
    // console.log(this.newsId)
    // 判断用户是否已收藏
    this.getCollectionInfo()
    // 获取热评
    this.gethotComments()
  },
  mounted () {
    // 监听屏幕滚动
    window.addEventListener('touchmove', this.myTouchMove)
    window.addEventListener('touchstart', this.myTouch)
  }
}

</script>

<style lang="scss" scoped>
  #news-details {
    background-color: #f6f6f6;
    @include themify {
      background-color: themed('news-details-bg-color');
    }
  }

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

  .article-box {
    padding: 20px 17px 0 17px;
    background-color: white;
    // border-bottom: 1PX solid #e6e6e6;
   @include themify {
      background-color: themed('theme-bg-color');
    }
  }

  .article-title {
    font-size: 23px;
    margin-top: 0;
    text-align: justify;
  }

  .article-sub {
    height: 20px;
    // border: 1px solid;
    font-size: 15px;
    color: #888888;
    margin-bottom: 10px;
  }

  .news-time {
    padding-left: 15px;
  }

  .article-content {
    padding-bottom: 20px;

    /deep/ p {
      //   font-size: 17px;
      margin: 25px 0 25px 0;
      font-size: 18px;
      text-align: justify;
      line-height: 28px;
    }

    /deep/ .ql-align-center {
      text-align: center;
    }

    /deep/ img {
      max-width: 100%;
      display: block;
      margin: 25px auto;
    }

    /deep/ video {
      display: block;
      max-width: 100%;
      width: 90%;
      margin-left: auto;
      margin-right: auto;
    }
  }

  .comments-wrap {
    margin-top: 10px;
    padding-top: 13px;
    background-color: white;
    @include themify {
      background-color: themed('theme-bg-color');
    }

    .label {
      text-align: center;
      font-size: 18px;
      color: #F74444;

      margin-bottom: 20px;
    }
  }

  .more-comments {
    font-size: 17px;
    color: #66A2E4;
    text-align: center;
    padding-bottom: 10px;
    // background-color: white;
  }

  .comment-empty {
    text-align: center;
    font-size: 14px;
    padding-bottom: 20px;
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
    z-index: 9999;

    //textaret-wrap
    /deep/ .van-cell {
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
      // padding: auto
      flex: none;
      // height: 100%;
      padding: 0 15px;
      font-size: 17px;
      font-weight: bolder;
      line-height: 94px;
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
    height: 45px;
    // border-top: 1PX solid #e4e4e4;
    // z-index: 999;
    background-color: white;
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 30px 0 15px;
    box-sizing: border-box;

    // van-field 输入框
    .trigger-input {
      display: flex;
      min-width: 60%;
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

    //图标——评论,收藏
    .i-com,
    .i-star {
      display: block;
      font-size: 27px;
    }

    .i-com {
      position: relative;
      color: rgb(51, 51, 51);
      top: 1px;
      margin-left: -10px;

      //评论数
      .i-tag {
        // box-sizing: border-box;
        height: 12px;
        min-width: 10px;
        text-align: center;
        line-height: 10px;
        border-radius: 6px;
        font-size: 10px;
        position: absolute;
        background-color: #ee0a24;
        display: block;
        padding: 1px 2px 1px 2px;
        color: white;
        left: 15px;
        top: -5px;
      }
    }

    .i-star {
      font-weight: 600;
      //   color: rgb(170, 169, 169);
      text-shadow: 1px 0 1px rgb(211, 211, 211);
    }

    .star-off {
      color: #aaa9a9;
    }

    .star-on {
      color: #f0cb54;
    }
  }

  .footer {
    padding-top: 45px;
  }

  .fade-enter-active {
    transition: opacity .9s;
  }

  .fade-enter,
  .fade-leave-to {
    opacity: 0.3;
  }

  .loading {
    position: absolute;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    margin: auto;
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    background-color: white;
    @include themify{
      background-color: themed('theme-bg-color');
    }
  }

</style>
