const Mock = require('mockjs')

const Random = Mock.Random
// 新闻列表

// const newsList = {
//   'data|5': [{
//     item_id: '@id',
//     title: '@ctitle(10, 26)',
//     publish_time: '@datetime(\'yyyy-MM-dd HH:mm\')',
//     source: 'cname',
//     comment_cont: '',
//     image_lis: []
//   }]
// }

// 新闻列表
const newsList = function (info) {
  console.log(info)
  const newsList = []
  for (let i = 0; i < 5; i++) {
    const imgList = []
    const imgCount = Math.floor(Math.random() * 4)
    // console.log('图片数' + imgCount)
    for (let i = 0; i < imgCount; i++) {
      imgList.push('https://p3.pstatp.com/list/pgc-image/3b5b6a65f2b84faa922f84ce2d196ad5')
    }
    const newsItem = {
      item_id: Random.id(),
      title: Random.ctitle(10, 26),
      publish_time: Random.datetime('yyyy-MM-dd HH:mm'),
      source: Random.cword(3, 7),
      comment_count: Random.natural(0, 3000),
      image_list: imgList
    }
    newsList.push(newsItem)
  }
  return newsList
}
// mock新闻列表
Mock.mock(/\/news_list.*/, 'get', newsList)

// 新闻详情
const newsDetails = function (info) {
  console.log(info)
  const tmp = {
    title: Random.ctitle(10, 26),
    source: Random.cword(3, 7),
    publish_time: Random.datetime('yyyy-MM-dd HH:mm'),
    content: '<p>受疫情的影响，现在全世界的体育运动都遭到重大打击，国内CBA停播、中超联赛迟迟未开，欧洲五大联赛和NBA也陷入停摆，目前仍没有开赛日期，而法甲直接宣布结束了。长时间没有体育比赛，不仅球员受不了，众多球迷朋友也十分渴望能看到比赛。球员渴望比赛不难理解，毕竟比赛给人分兴奋程度非长时间枯燥的训练可比。</p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/167ed9073c44497bb7921d58f43a23bb" img_width="365" img_height="495" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/769aea0cb1084994817e65edb754bf82" img_width="723" img_height="218" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>不过，球迷日盼夜盼的赛事终于要来了，中超公司于4月30日发了一个通知，将对各俱乐部的队内训练赛以及热身赛进行转播。通知要求各俱乐部在不影响正常训练的同时积极配合参与，这一决定也得到了不少球迷的鼓掌欢迎。“在没有比赛的日子里，能看到队内比赛和热身赛，也算是球迷的一种福利吧。中超公司也算是干了一件让球迷满意的事情。”“赶紧转吧，现在你别说是热身赛了，你播中学生比赛我都看。”从球迷的留言来看，大家可是对比赛的期盼是多么的热切。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/746c0ee6a0654d97890d1c3b9057fa66" img_width="640" img_height="427" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>诚然，在没有比赛看的日子，某些直播平台都一直复播旧比赛，此番中超公司也算作了一件好事，一是能满足球迷的观赛需求，二是能在转播方面增加一些收入。要知道，现在联赛一日未开，中超公司的损失就会逐渐增大，而对于俱乐部来说，也有一个展现良好形象的平台和机会，其实不少球迷对俱乐部的日常训练非常感兴趣，如果能拍一些球队日常训练的项目和技战术演练，相信也会得到球迷的喜爱。</p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/33ed5d8cbe09492e91fd4a24001536e9" img_width="626" img_height="472" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>而作为重点关注的国足热身赛也有很大的机会进行转播。目前，李铁率领的新一届国家队正在上海集训，据《北京青年报》的报道，本次集训练内容由基本的身体恢复、力量训练开始逐步注入“技战术元素”，同时兼顾耐力训练，训练强度也是由低向高。而在本次集训中，李铁也会安排两场热身赛以检验训练效果。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/e9eda778bdae48658c773ce9d896cb3b" img_width="640" img_height="427" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p><br></p><div class="pgc-img"><img src="https://p3.pstatp.com/large/dfic-imagehandler/8744eb3c-314a-4b36-92ac-96e1271882dd" img_width="1200" img_height="800" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>该报确认本次国足的热身对手将会是上海滩双雄上海申花和上海上港两支球队。而结合中超公司的通知，这两场比赛将有望转播，到时候李铁到底将国家队打造出怎样的效果到时候将揭晓。虽然国足在广州集训是分别打了两次热身赛，一场是8-0大胜中甲升班马沈阳建设，另一场是1-0小胜武汉卓尔，但这两场比赛球迷无缘相见。第二次在迪拜集训时有消息透露国足将与重庆、富力和深足进行热身，但最终还是流产了。</p><p> </p><div class="pgc-img"><img src="https://p3.pstatp.com/large/pgc-image/db0475d37db9422fa44f3fa5ed3ad5c4" img_width="640" img_height="418" inline="0" alt="球迷有福！国足大战上港申花或将转播，2020高水平对决值得期待" onerror="javascript:errorimg.call(this);"><p class="pgc-img-caption"></p></div><p>此番，与国足过招的无申花还是上港实力都非常强，申花在冬窗期引进了包括冯潇霆、曾诚、秦升、赵明剑等前国脚，而上港在保有奥斯卡、胡尔克、阿瑙托维奇、艾哈迈多夫等实力强劲的外援后还出手拿下了年度标王巴西强力前锋洛佩斯。两支球队阵容齐整，实力雄厚，作为2020重磅对决，值得期待。</p><p><br></p>',
    comment_count: Random.natural(8990, 12000)
  }
  return tmp
}

Mock.mock(/\/news_details\/((?!\/).)*$/, 'get', newsDetails)

// 热门评论
const hotComments = function (info) {
  console.log(info)
  const commentsList = []
  for (let i = 0; i < 6; i++) {
    const tmp = {
      user: {
        user_id: Random.id(),
        avatar_url: 'http://sf6-ttcdn-tos.pstatp.com/img/pgc-image/724d143d084d4a00a053f5010f7d4759~120x256.image',
        name: Random.cword(3, 10)
      },
      user_like: false,
      user_oppose: false,
      comment_id: Random.id(),
      text: Random.csentence(3, 50),
      like_count: Random.natural(0, 13000),
      oppose_count: Random.natural(0, 300),
      // oppose_count: 0,

      reply_count: Random.natural(0, 30),
      create_time: Random.datetime('yyyy-MM-dd HH:mm')
    }
    commentsList.push(tmp)
  }
  return commentsList
}

Mock.mock(/\/news_details\/.*\/hot_comments/, 'get', hotComments)

// 点赞/取消点赞 踩/取消踩
const commentHandle = function (info) {
  console.log(info)
  return 'yes'
}

Mock.mock(/\/news_details\/.*\/comments\/.*\/./, 'post', commentHandle)
Mock.mock(/\/news_details\/.*\/comments\/.*\/./, 'delete', commentHandle)

// 收藏/取消收藏
const collectionHandle = function (info) {
  console.log(info)
  return 'yes'
}

Mock.mock(/\/users\/.*\/collections/, 'post', collectionHandle)
Mock.mock(/\/users\/.*\/collections\/.*/, 'delete', collectionHandle)
// Mock.mock('https://afs7hx.toutiao15.com/collectNews', 'post', collectionHandle)

// 发布评论
const addReply = function (info) {
  console.log(info)
  return 'yes'
}

Mock.mock(/\/news_details\/.*\/comments/, 'post', addReply)
