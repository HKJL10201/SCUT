<template>
  <div>
    <!-- <van-row>
      <van-col span="21">
      </van-col>
    </van-row> -->
    <div id="nav-bar">
      <router-link to="/my_center">
        <van-icon id="nav-left-icon" name="contact" @click="test" />
      </router-link>
      <span>新闻门户</span>
    </div>
    <div id="news-channel">
      <div id="add-channel" @click="popChannelList = true">
        <van-icon name="plus" color="#66A2E4" />
      </div>
      <!-- "修改频道"弹出层 -->
      <van-overlay :show="popChannelList" @click="saveMyChannelList">
        <div id="channel-pick-box" @click.stop>
          <div>
            <div id="channel-top-bar">
              <div id="pick-box-title">感兴趣的栏目</div>
              <div id="channel-modify-button" @click="channelModify = !channelModify" v-show='!channelModify'>编辑</div>
              <div id="channel-modify-button" @click="channelModify = !channelModify" v-show='channelModify'>完成</div>
            </div>
            <div class="pick-tips" v-show="!channelModify">点击进入栏目</div>
            <div class="pick-tips" v-show="channelModify">点击移除频道</div>
          </div>
          <!-- 已添加频道列表 -->
          <!-- 点击进入频道 -->
          <div id="user-like-channel-list" class="channel-list" v-show="!channelModify">
            <!-- 点击跳转频道 -->
            <div class="channel-item like-channel-item channel-like-skip" v-for="(item,  index) in userChannelList.slice(0,2)"
              :key="'fixs' + index" @click="skipToChannel(index, item)">
              {{item}}
            </div>
            <div class="channel-item like-channel-item channel-like-skip" v-for="(item,  index) in userChannelList.slice(2)"
              :key="'s' + index" @click="skipToChannel(index + 2, item)">
              {{item}}
            </div>
            <div class="channel-item channel-placeholder forbidmove" v-for="index in 3" :key="'p' + index">
            </div>
          </div>
          <!--拖拽排序 -->
          <draggable v-model="userChannelList" @update="dataDragEnd"  animation="500" filter='.forbidmove' draggable=".moveable"

            id="user-like-channel-list" class="channel-list" v-show="channelModify">
            <!-- 可移动排序的列表 -->
            <transition-group>
              <!-- <div class="channel-item like-channel-item forbidmove" v-for="(item,  index) in fixedUserChannelList" -->
              <div class="channel-item like-channel-item forbidmove" v-for="(item,  index) in userChannelList.slice(0,2)"
              :key="'fix' + index">
              {{item}}
              </div>
              <!-- <div class="channel-item like-channel-item moveable" v-for="(item,  index) in changeableUserChannelList" -->
              <div class="channel-item like-channel-item moveable" v-for="(item,  index) in userChannelList.slice(2)"
                :key="'m' + index" @click="removeChannel(index + 2)">
                <van-icon class="channel-modify-icon" name="cross"></van-icon>
                <span>{{item}}</span>
              </div>
              <div class="channel-item channel-placeholder forbidmove" v-for="index in 3" :key="'p' + index">
              </div>
            </transition-group>
          </draggable>
          <!-- 点击移除 -->
          <!-- <div id="user-like-channel-list" class="channel-list" v-show="channelModify">
            <div class="channel-item like-channel-item" v-for="(item,  index) in userChannelList.slice(0,2)"
              :key="'fs' + index">
              {{item}}
            </div>
            <div class="channel-item like-channel-item" v-for="(item,  index) in userChannelList.slice(2)"
              :key="'m' + index" @click="removeChannel(index + 2)">
              <van-icon class="channel-modify-icon" name="cross"></van-icon>
              <span>{{item}}</span>
            </div>
            <div class="channel-item channel-placeholder" v-for="index in 3" :key="'p' + index">
            </div>
          </div> -->
          <van-divider />
          <div class="pick-tips">
            点击增加频道
          </div>
          <!-- 未添加频道列表 -->
          <div id="ignore-channel-list" class="channel-list">
            <div class="channel-item ignore-channel-item" v-for="(item, index) in ignoreChannelList" :key="index"
              @click="addChannel(index)">
              <van-icon class="channel-modify-icon" name="plus"></van-icon>
              <span>{{item}}</span>
            </div>
            <div class="channel-item channel-placeholder" v-for="index in 3" :key="'pl' + index">
            </div>
          </div>
        </div>
      </van-overlay>
      <van-tabs id="nav-channel" color="#66A2E4" @click="changeChannel">
        <!-- 每一项以key作为标签页标题, 以下标index作为其索引(name)-->
        <!-- <van-tab v-for="(value, key, index) in newsChannel" :title="key" :name="index" :key="value"> -->
        <!-- <van-tab v-for="(item, index) in userChannelList" :title="item" :name="item" :key="index"> -->
        <van-tab v-for="(item, index) in userChannelList" :title="item" :name="index" :key="index">
        </van-tab>
        <!-- <van-tab v-for="(item, index) in changeableUserChannelList" :title="item" :name="index + 2" :key="index + 2"> -->
        <!-- </van-tab> -->
      </van-tabs>
    </div>
    <!-- 新闻列表 -->
    <div>
      <van-list v-model="loading" :finished="finished" finished-text="已到底部" @load="onLoadNewsList">
        <router-link class="news-card-cell" v-for="(item, index) in newsList" :key="index + ':' + item.item_id"
          :to="{ name:'newsDetails', params:{ news_id: item.item_id,  news_image: item.image_list } }">
          <!-- :to="/news_details/ + item.item_id"> -->
          <!-- 纯文字新闻 -->
          <div class="news-card card-words" v-if="hasImage(item) === 0">
            <div class="skip">
              <div class="news-info">
                <h3 class="news-title">
                  {{item.title}}
                </h3>
                <div class="news-detail">
                  <span class="news-source">{{ item.source }}</span>
                  <span class="news-comments">{{ transNumber(item.comment_count) + '评论' }}</span>
                  <span class="news-time">{{ transTime(item.publish_time) }}</span>
                </div>
              </div>
            </div>
          </div>
          <!-- 单图 -->
          <div class="news-card card-one-pic" v-else-if="hasImage(item) === 1 || hasImage(item) === 2">
            <div class="skip">
              <div class="news-info">
                <h3 class="news-title">
                  {{item.title}}
                </h3>
                <div class="news-detail">
                  <span class="news-source">{{ item.source }}</span>
                  <span class='news-comments'>{{ transNumber(item.comment_count) + '评论' }}</span>
                  <span class='news-time'>{{ transTime(item.publish_time) }}</span>
                </div>
              </div>
              <div class="news-image" v-if="!noPicMode">
                <img :src="item.image_list[0]" alt="测试">
              </div>
            </div>
          </div>
          <!-- 三图新闻 -->
          <div class="news-card card-three-pics" v-else>
            <div class="skip">
              <h3 class="news-title">
                {{item.title}}
              </h3>
              <div class="news-image" v-if="!noPicMode">
                <img :src="item.image_list[0]" alt="测试">
                <img :src="item.image_list[1]" alt="测试">
                <img :src="item.image_list[2]" alt="测试">
              </div>
              <div class="news-detail">
                <span class="news-source">{{ item.source }}</span>
                <span class="news-comments">{{ transNumber(item.comment_count) + '评论'}}</span>
                <span class="news-time">{{ transTime(item.publish_time) }}</span>
              </div>
            </div>
          </div>
        </router-link>
      </van-list>
    </div>
  </div>
</template>

<script>
export default {
  name: 'newsList',
  components: {

  },
  data () {
    return {
      // userId: 124233523,
      newsSource: '新华网',
      newsTime: '2小时前',
      newsComments: '0',
      newsList: [],
      loading: false, // 标记新闻列表加载
      finished: false, // 标记新闻列表加载
      list: [],
      popChannelList: false, // 弹出频道选择框
      // userChannelList: ['推荐', '热点', '社会', '娱乐', '科技', '军事',
      //   '体育', '财经', '国际'
      // ], // 用户感兴趣的频道'
      userChannelList: ['推荐', '热点'],
      ignoreChannelList: ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'], // 用户忽略的频道
      // changeableUserChannelList: ['社会', '娱乐', '科技', '军事',
      // '体育', '财经', '国际'],
      // fixedUserChannelList: ['推荐', '热点'],
      channelModify: false,
      curNewsChannel: '__all__',
      newsChannel: {
        推荐: '__all__',
        热点: 'news_hot',
        社会: 'news_society',
        娱乐: 'news_entertainment',
        科技: 'news_tech',
        军事: 'news_military',
        体育: 'news_sports',
        汽车: 'news_car',
        财经: 'news_finance',
        国际: 'news_world',
        时尚: 'news_fashion',
        旅游: 'news_travel',
        探索: 'news_discovery',
        育儿: 'news_baby',
        养生: 'news_regimen',
        故事: 'news_story',
        美文: 'news_essay',
        游戏: 'news_game',
        历史: 'news_history',
        美食: 'news_food'
      }
    }
  },
  methods: {
    test () {
      console.log('this is click test')
    },

    // 导航栏选中项高亮
    hightLightChannel (index) {
      // 获得了index，根据index把该元素的css属性改变
      var oLis = document.getElementsByClassName('van-tab__text')
      for (let i = 0; i < oLis.length; i++) {
        if (i === index) {
          // oLis[i].style.color = '#66A2E4'
          const dataTheme = document.body.getAttribute('data-theme')
          oLis[i].style.fontWeight = 'bolder'
          if (dataTheme === 'dark') {
            oLis[i].style.setProperty('color', '#5c7f95', 'important')
          } else if (dataTheme === 'default') {
            oLis[i].style.setProperty('color', '#66A2E4', 'important')
          } else if (dataTheme === 'red') {
            oLis[i].style.setProperty('color', '#ED6161', 'important')
          } else if (dataTheme === 'khaki') {
            oLis[i].style.setProperty('color', '#dddaa9', 'important')
          }
        } else {
          // oLis[i].style.color = '#646566'
          // 此处降低优先级, 使颜色为CSS样式设定的颜色
          oLis[i].style.setProperty('color', '#646566')
          oLis[i].style.fontWeight = 'normal'
        }
      }
    },

    // 更改频道 (传入选中项的标识符——对应name——传入值为列表下标，选中项的标题——对应title)
    changeChannel (name, title) {
      this.hightLightChannel(name) // 高亮选中项
      this.curNewsChannel = this.newsChannel[title] // 获取该频道对应的value
      this.newsList = [] // 清空新闻列表
      this.loading = true
      this.onLoadNewsList()
      const channelItemInPop = document.getElementsByClassName('channel-like-skip')
      // channelItemInPop[name]
      // console.log(name)
      for (let i = 0; i < channelItemInPop.length; i++) {
        if (i === name) {
          channelItemInPop[i].classList.add('channel-item-cur')
        } else {
          channelItemInPop[i].classList.remove('channel-item-cur')
        }
      }
      // console.log(channelItemInPop)
    },
    // 保存用户感兴趣的频道列表
    saveMyChannelList () {
      // 判断是否已登录
      if (!this.$store.getters.ifLogin) { // 未登录,本地保存
        this.channelModify = false
        this.popChannelList = false
        return
      }
      const list = []
      for (let i = 0; i < this.userChannelList.length; i++) {
        list.push(this.newsChannel[this.userChannelList[i]])
        // console.log(this.newsChannel[this.userChannelList[i]])
      }
      console.log(list)
      this.$axios.post('https://afs7hx.toutiao15.com/modifyMyChannels', {
        username: this.userId,
        channels: list
      }).then(response => {
        if (response.status === 200) {
          console.log('请求成功')
        }
      })
      this.channelModify = false
      this.popChannelList = false
    },
    // 修改呈现时间
    transTime (dateTime) {
      return this.$transTime(dateTime)
    },
    // 修改评论显示数字
    transNumber (comments) {
      return this.$transNumber(comments)
    },
    // 加载新闻列表项
    onLoadNewsList () {
      this.$axios.post('https://afs7hx.toutiao15.com/getNewsListByChannel', {
        channel: this.curNewsChannel
      })
      // this.$axios.get('/news_list', {
      //   params: {
      //     channel: this.curNewsChannel
      //   }
      // })
        .then(response => {
          const tmpList = response.data
          console.log(tmpList)
          if (tmpList) {
            this.newsList.push.apply(this.newsList, tmpList) // 添加新闻项
            this.loading = false // 加载结束
          } else {
            this.loading = false
            this.finished = true
          }
        })
    },
    // 获取新闻列表
    getNewsList () {
      this.$axios.get('/news_list').then(response => {
        this.newsList = response.data
      })
    },
    // 判断新闻是否有图片封面
    hasImage (newsItem) {
      return newsItem.image_list.length
    },
    // 获取用户喜爱的新闻频道
    getUserChannel () {
      // this.$axios.get('/user/' + this.userId + '/favo_channel/')
      //   .then(response => {
      //     this.userChannelList = response.data
      //   })
      this.$axios.get('https://afs7hx.toutiao15.com/getMyChannels', {
        params: {
          username: this.userId
        }
      }).then(response => {
        let tmp
        if (response.status === 200) {
          tmp = response.data.data
        } else {
          console.log('请求失败')
          // 默认的用户喜爱频道列表
          tmp = ['__all__', 'news_hot', 'news_society', 'news_entertainment', 'news_tech', 'news_military',
            'news_sports', 'news_finance', 'news_world'
          ]
        }
        console.log('获取到的频道' + tmp)
        // 初始化用户感兴趣的频道列表
        this.initUserChannelList(tmp)
        // 初始化用户忽略的频道
        this.initIgnoreChannelList()
        // this.initCurChannel()
      })
    },
    // 增添用户感兴趣的频道
    addChannel (index) {
      setTimeout(() => {
        // 从隐藏的频道列表中移除
        const tmp = this.ignoreChannelList.splice(index, 1)
        // 向感兴趣频道里增添
        this.userChannelList.push(tmp[0])
        // 发起请求
      }, 200)
    },
    // 移除用户感兴趣的频道
    removeChannel (index) {
      setTimeout(() => {
        if (index === this.userChannelList.length - 1 &&
            this.newsChannel[this.userChannelList[index]] === this.curNewsChannel) {
          this.initCurChannel()
        }
        const tmp = this.userChannelList.splice(index, 1)
        this.ignoreChannelList.push(tmp[0])
      }, 200)
    },
    // 跳转至选中频道 (选中项下标, 名称)
    skipToChannel (index, item) {
      this.changeChannel(index, item)
      setTimeout(() => {
        this.popChannelList = false
        const vantabs = document.getElementsByClassName('van-tab')
        vantabs[index].click()
      }, 200)
    },
    // 初始化用户感兴趣的频道列表
    initUserChannelList (tmp) {
      console.log('测试: ' + tmp)
      // 获取用户喜爱的频道(对应的key)
      // this.userChannelList = Object.keys(this.newsChannel).filter(k => {
      //   for (let i = 0; i < tmp.length; i++) {
      //     if (this.newsChannel[k] === tmp[i]) {
      //       return k
      //     }
      //   }
      // })
      console.log(this.userChannelList)
      for (let i = 2; i < tmp.length; i++) {
        this.userChannelList.push(Object.keys(this.newsChannel).find((k) => this.newsChannel[k] === tmp[i]))
      }
    },
    // 初始化用户忽略的频道列表
    initIgnoreChannelList () {
      this.ignoreChannelList = Object.keys(this.newsChannel).filter(k => {
        let exist = 0
        for (let i = 0; i < this.userChannelList.length; i++) {
          if (k === this.userChannelList[i]) {
            exist = 1
          }
        }
        if (exist === 0) {
          return k
        }
      })
    },
    // 初始选中栏目
    initCurChannel () {
      // this.curNewsChannel = '__all__',
      const channelsDOM = document.getElementsByClassName('van-tab')
      console.log(channelsDOM)
      console.log(channelsDOM[0])
      channelsDOM[0].click()
    },

    dataDragEnd (evt) {
      evt.preventDefault()
      console.log('拖动前的索引 :' + evt.oldIndex)
      console.log('拖动后的索引 :' + evt.newIndex)
      console.log(this.userChannelList)
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
    curNewsChannel: function (value) {
      // this.newsChannel[]

    }
  },
  created: function () {
    // 初始化用户感兴趣的频道和忽略的频道
    this.getUserChannel()
  },
  mounted: function () {
    this.$nextTick(() => {
      // 初始化选中栏目
      this.initCurChannel()
    })
  }
}

</script>

<style lang="scss" scoped>
  #nav-bar {
    height: 40px;
    color: white;
    background-color: #66A2E4;
    text-align: center;
    line-height: 40px;
    position: relative;

    @include themify {
      background-color: themed('nav-bg-color');
      color: themed('nav-font-color');
    }
  }

  #nav-left-icon {
    position: absolute;
    left: 20px;
    top: 50%;
    transform: translate(0, -50%);
    font-size: 25px;

    // color: white !important;
    @include themify {
      color: themed('nav-font-color') !important;
    }
  }

  #nav-left-icon:hover {
    cursor: pointer;
  }

  #nav-bar span {
    font-size: 18px;
  }

  #news-channel {
    position: relative;
  }

  #add-channel {
    position: absolute;
    right: 0;
    background-color: white;
    z-index: 99;
    /* width: 44px; */
    width: 12%;
    height: 44px;
    text-align: center;
    line-height: 44px;
    box-shadow: -10px 0px 6px -3px rgba(255, 255, 255, 0.589);

    @include themify {
      background-color: themed('add-channel-but');
      color: themed('add-channel-but');
      box-shadow: themed('add-channel-box-shadow');
    }
  }

  #add-channel .van-icon-plus {
    font-size: 30px;
    top: 7px;
    font-weight: bolder;
    /* border-left: 1px */
    /* text-shadow: 0 0 3px 3px rgba(130, 188, 241, 0.589); */

    @include themify {
      color: themed('van-tabs__line-color') !important;
    }

  }

  #nav-channel {
    position: relative;
    /* width: 331px; */
    width: 88%;
  }

  .van-overlay {
    z-index: 9999;
    display: flex;
  }

  #channel-pick-box-wrap {
    display: flex;
  }

  #channel-pick-box {
    box-sizing: border-box;
    margin: auto;
    height: 360px;
    width: 300px;
    background-color: rgb(252, 250, 250);
    // box-shadow: 1px 1px 1px;
    border-radius: 5px;
    padding: 10px 15px;

    @include themify {
      background-color: themed('channel-pick-pop-bg-color');
      color: themed('channel-pick-pop-font-color');
    }
  }

  #channel-top-bar {
    display: flex;
    align-items: center;
    justify-content: space-between;
  }

  #channel-modify-button {
    border: 1px solid #66A2E4;
    color: #66A2E4;
    padding: 3px 7px;
    border-radius: 5px;

    @include themify {
      border: 1px solid themed('van-tabs__line-color');
      color: themed('van-tabs__line-color');
    }
  }

  .channel-list {
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-wrap: wrap;
    /* padding: 30px; */

    span {
      display: flex;
      flex-wrap: wrap;
      justify-content: space-between;
      align-items: center;
    }
  }

  #pick-box-title {
    font-size: 17px;
    font-weight: bold;
    margin-bottom: 10px;
  }

  .pick-tips {
    margin-bottom: 3px;
  }

  .channel-item {
    padding: 5px 0;
    box-sizing: border-box;
    border: 1Px solid #f0f0f0;
    margin: 5px 0;
    box-shadow: 1px 1px 3px 1px rgba(218, 218, 218, 0.575);
    width: 57px;
    text-align: center;
    display: flex;
    align-items: center;
    justify-content: center;
    border-radius: 10px;

    @include themify {
      box-shadow: themed('channel-item-box-shadow');
      border: themed('channel-item-bd');
    }

    &:active {
      @include themify {
        box-shadow: themed('channel-item-checked-box-shadow');
      }

      // box-shadow: 1px 1px 5px 3px rgba(202, 229, 247, 0.61)
    }

    .channel-modify-icon {
      font-size: 10px;
      font-weight: bold;
      margin-right: 4px;
      color: #bbbbbb;
    }
  }

  .channel-item-cur {
    @include themify {
      color: themed('van-tabs__line-color');
    }
  }

  .channel-placeholder {
    /* visibility: hidden; */
    height: 0 !important;
    border: 0 !important;
    padding: 0 !important;
    margin: 0 !important;
    box-shadow: none !important;
  }

  .van-tabs {
    // van-tab-wrap边框

    // /deep/ .van-tabs__wrap {
    /deep/ [class*=van-hairline]::after {
      @include themify {
        border: themed('van-tabs__wrap-bd') !important;
      }
    }

    /* van-tab标题 */
    /deep/ .van-tab__text {
      font-size: 21px;

      @include themify {
        // color: themed('van-tab__text-color');
        color: themed('van-tab__text-color') !important;
      }
    }

    /* van-tab底部选中条 */
    /deep/ .van-tabs__line {
      width: 50px !important;

      // background-color: #ED6161 !important;
      @include themify {
        background-color: themed('van-tabs__line-color') !important;
      }
    }

    /deep/ .van-tabs__nav {
      background-color: white;

      @include themify {
        background-color: themed('van-tabs__nav-color');
        color: themed('nav-font-color');
      }
    }
  }

  #block {
    background-color: #66A2E4;
    height: 300px;
    width: 300px;
    box-shadow: inset -5px 0px 10px -5px #000;
  }

  .news-card {
    /* border: 1px solid; */
    border-bottom: 1px solid #f5f7f9;
    padding: 12px;

    @include themify {
      border-bottom: themed('news-card-bd-bottom');
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
      color: themed('news-title-color');
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
