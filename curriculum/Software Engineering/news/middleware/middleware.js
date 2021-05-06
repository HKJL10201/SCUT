// 项目中间件

let express = require('express');
let app = express();

const Random = express.Random

app.all('*', function(req, res, next){
    // 任何网址都可以访问
    res.header("Access-Control-Allow-Origin", "*");
    // 允许的请求方式
    res.header("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");
    // X-Requested-With， 是普通请求，还是ajax请求
    res.header("Access-Control-Allow-Headers","X-Requested-With");
    res.header("Content-Type", "application/json;charset=utf-8");
    next();
})



app.get('/xx',(req,res)=>{
    let _n = {
        a:'第一个接口 demo'
    }
    res.send( _n )
})

//指定条目数
const tips = [ '生活是不公平的，你要去适应它。',
'送人玫瑰，手流余香。',
'我们有不同的籍贯、不同的年龄、不同的习惯、不同的经历，但有一点我们是相同的，那就是都有一颗：爱心。',
'锦上添花固然好,雪中送炭更可贵。',
'伸出您的友爱之手,让更多的孩子重返校园。',
'如果你陷入困境，那不是你父母的过错，不要将你理应承担的责任转嫁给他人，而要学着从中吸取教训。',
'爱心一片,真情永远。',
'聆听心声,实现愿望。',
'走出学校后的生活不像在学校一样有学期之分，也没有暑假之说。没有几位老板乐于帮你发现自我，你必须依靠自己去完成。',
'电视中的许多场景决不是真实的生活。在现实生活中，人们必须埋头做自己的工作，而非像电视里演的那样天天泡在咖啡馆里。',
'善待你所厌恶的人，因为说不定哪一天你就会为这样的一个人工作。',
'人生应该如蜡烛一样，从顶燃到底，一直都是光明的。 —— 萧楚女',
'人生的价值，即以其人对于当代所做的工作为尺度。 —— 徐玮',
'路是脚踏出来的，历史是人写出来的。人的每一步行动都在书写自己的历史。 —— 吉鸿昌',
'春蚕到死丝方尽，人至期颐亦不休。一息尚存须努力，留作青年好范畴。 —— 吴玉章',
'但愿每次回忆，对生活都不感到负疚 —— 郭小川',
'人的一生可能燃烧也可能腐朽，我不能腐朽，我愿意燃烧起来！ —— 奥斯特洛夫斯基',
'你若要喜爱你自己的价值，你就得给世界创造价值。 —— 歌德',
'社会犹如一条船，每个人都要有掌舵的准备。 —— 易卜生',
'人生不是一种享乐，而是一桩十分沉重的工作。 —— 列夫·托尔斯泰',
'人生的价值，并不是用时间，而是用深度去衡量的。 —— 列夫·托尔斯泰',
'生活只有在平淡无味的人看来才是空虚而平淡无味的。 —— 车尔尼雪夫斯基',
'一个人的价值，应该看他贡献什么，而不应当看他取得什么。 —— 爱因斯坦',
'人只有献身于社会，才能找出那短暂而有风险的生命的意义。 —— 爱因斯坦',
'芸芸众生，孰不爱生？爱生之极，进而爱群。 —— 秋瑾',
'生活真象这杯浓酒，不经三番五次的提炼呵，就不会这样可口！ —— 郭小川',
'充满着欢乐与斗争精神的人们，永远带着欢乐，欢迎雷霆与阳光。 —— 赫胥黎',
'春风吹柳,雨润大地。',
'为了生活中努力发挥自己的作用，热爱人生吧。 —— 罗丹',
'希望是附丽于存在的，有存在，便有希望，有希望，便是光明。 —— 鲁迅',
'沉沉的黑夜都是白天的前奏。 —— 郭小川',
'当一个人用工作去迎接光明，光明很快就会来照耀着他。 —— 冯学峰',
'东天已经到来，春天还会远吗？ —— 雪莱',
'过去属于死神，未来属于你自己。 —— 雪莱',
'世间的活动，缺点虽多，但仍是美好的。 —— 罗丹',
'辛勤的蜜蜂永没有时间悲哀。 —— 布莱克',
'希望是厄运的忠实的姐妹。 —— 普希金',
'当你的希望一个个落空，你也要坚定，要沉着！ —— 朗费罗',
'先相信你自己，然后别人才会相信你。 —— 屠格涅夫',
'不要慨叹生活底痛苦！---慨叹是弱者...... —— 高尔基',
'宿命论是那些缺乏意志力的弱者的借口。 —— 罗曼·罗兰',
'春回人间,真情奉献。',
'私心胜者，可以灭公。 —— 林逋',
'人人好公，则天下太平；人人营私，则天下大乱。 —— 刘鹗',
'自私自利之心，是立人达人之障。 —— 吕坤',
'如烟往事俱忘却，心底无私天地宽。 —— 陶铸',
'常求有利别人，不求有利自己。 —— 谢觉哉',
'一切利己的生活，都是非理性的，动物的生活。 —— 列夫·托尔斯泰',
'人的理性粉碎了迷信，而人的感情也将摧毁利己主义。 —— 海涅',
'无私是稀有的道德，因为从它身上是无利可图的。 —— 布莱希特',
'君子喻于义，小人喻于利。 —— 孔丘',
'不戚戚于贫贱，不汲汲于富贵。 —— 陶渊明',
'富贵不淫贫贱乐，男儿到此是豪雄。 —— 程颢',
'清贫，洁白朴素的生活，正是我们革命者能够战胜许多困难的地方！ —— 方志敏',
'三军可夺帅也,匹夫不可夺志也。 —— 孔丘',
'志不强者智不达。 —— 墨翟',
'燕雀安知鸿鹄之志哉！ —— 陈涉',
'志当存高远。 —— 诸葛亮',
'老骥伏枥，志在千里；烈士暮年，壮心不已。 —— 曹操',
'燕雀戏藩柴，安识鸿鹄游。 —— 曹植',
'穷且益坚，不坠青云之志。 —— 王勃',
'大鹏一日同风起，扶摇直上九万里。 —— 李白',
'古之立大事者，不惟有超世之才，亦必有坚忍不拔之志。 —— 苏轼',
'生当作人杰，死亦为鬼雄，至今思项羽，不肯过江东。 —— 李清照',
'壮心未与年俱老，死去犹能作鬼雄。 —— 陆游',
'故立志者，为学之心也；为学者，立志之事也。 —— 王阳明',
'贫不足羞，可羞是贫而无志。 —— 吕坤',
'我们以人们的目的来判断人的活动。目的伟大，活动才可以说是伟大的。 —— 契诃夫',
'毫无理想而又优柔寡断是一种可悲的心理。 —— 培根',
'生活的理想，就是为了理想的生活。 —— 张闻天',
'人，只要有一种信念，有所追求，什么艰苦都能忍受，什么环境也都能适应。 —— 丁玲',
'理想的人物不仅要在物质需要的满足上，还要在精神旨趣的满足上得到表现。 —— 黑格尔',
'一个能思想的人，才真是一个力量无边的人。 —— 巴尔扎克',
'一个没有受到献身的热情所鼓舞的人，永远不会做出什么伟大的事情来。 —— 车尔尼雪夫斯基',
'共同的事业，共同的斗争，可以使人们产生忍受一切的力量。 —— 奥斯特洛夫斯基',
'我从来不把安逸和快乐看作是生活目的本身---这种伦理基础，我叫它猪栏的理想。 —— 爱因斯坦',
'在一个人民的国家中还要有一种推动的枢纽，这就是美德。 —— 孟德斯鸠',
'人不能象走兽那样活着，应该追求知识和美德。 —— 但丁',
'勿以恶小而为之，勿以善小而不为。惟贤惟德，能服于人。 —— 刘备',
'不患位之不尊，而患德之不崇；不耻禄之不伙，而耻智之不博。 —— 张衡',
'土扶可城墙，积德为厚地。 —— 李白',
'行一件好事，心中泰然；行一件歹事，衾影抱愧。 —— 神涵光',
'入于污泥而不染、不受资产阶级糖衣炮弹的侵蚀，是最难能可贵的革命品质。—— 周恩来',
'一个人最伤心的事情无过于良心的死灭。 —— 郭沫若',
'害羞是畏惧或害怕羞辱的情绪，这种情绪可以阻止人不去犯某些卑鄙的行为。 —— 斯宾诺莎',
'应该热心地致力于照道德行事，而不要空谈道德。 —— 德谟克利特',
'感情有着极大的鼓舞力量，因此，它是一切道德行为的重要前提。 —— 凯洛夫',
'没有伟大的品格，就没有伟大的人，甚至也没有伟大的艺术家，伟大的行动者。 —— 罗曼·罗兰',
'理智要比心灵为高，思想要比感情可靠。 —— 高尔基',
'顶级培训网 让我们携手一起成长 ',
'人类被赋予了一种工作，那就是精神的成长。 —— 列夫·托尔斯泰',
'人在智慧上应当是明豁的，道德上应该是清白的，身体上应该是清洁的。 —— 契诃夫',
'良心是由人的知识和全部生活方式来决定的。 —— 马克思',
'不念居安思危，戒奢以俭；斯以伐根而求木茂，塞源而欲流长也。 —— 魏徵',
'历览前贤国与家，成由勤俭破由奢。 —— 李商隐',
'把“德性”教给你们的孩子：使人幸福的是德性而非金钱。这是我的经验之谈。在患难中支持我的是道德，使我不曾自杀的，除了艺术以外也是道德。 —— 贝多芬',
'如果道德败坏了，趣味也必然会堕落。——狄德罗',
'我愿证明，凡是行为善良与高尚的人，定能因之而担当患难。 —— 贝多芬',
'装饰对于德行也同样是格格不入的，因为德行是灵魂的力量和生气。 —— 卢梭',
'我深信只有有道德的公民才能向自己的祖国致以可被接受的敬礼。 —— 卢梭',
'懒人图库-网页素材下载站 - 学会偷懒，并懒出境界是提高工作效率最有效的方法！',
'对于事实问题的健全的判断是一切德行的真正基础。 —— 夸美纽斯',
'德行的实现是由行为，不是由文字。 —— 夸美纽斯',
'霸祖孤身取二江，子孙多以百城降。豪华尽出成功后，逸乐安知与祸双？ —— 王安石',
'阴谋陷害别人的人，自己会首先遭到不幸。 —— 伊索',
'奢则妄取苟取，志气卑辱；一从俭约，则于人无求，于己无愧，是可以养气也。 —— 罗大经',
'侈则多欲。君子多欲则念慕富贵，枉道速祸。 —— 司马光',
'顶级培训网 让我们携手一起成长 ',
'知耻近乎勇。 —— 孔丘',
    '辱，莫大于不知耻。 —— 王通'
]

// 生成长度为length的Id
function genID (length) {
    return Number(Math.random().toString().substr(3,length) + Date.now()).toString(36);
}

// 生成10000以内 的随机数
function genNum (){
    return Math.floor(Math.random() * 10000);
}
// 生成长度为length的文字
function genTitle (length) {
    let index = Math.floor(Math.random() * tips.length);
    if (tips[index].length >= length) {
        return tips[index].substr(0, length);
    }
    else {
        let curlen = length
        let len = tips[index].length
        let str = ''
        while (curlen > 0) {
            if (len >= curlen ) {
                return  str + tips[index].substr(0, len);
            }
            else {
                str += tips[index]
                curlen -= len
                index = (index + 1) % tips.length;
                len = tips[index].length
            }
        }
        return str;
    }
    return '';
}

app.get('/reply-lists',(req,res)=>{
    let _n = {
        a:'reply-list'
    }
    let _reply = {
        list:[
            {
                user:{
                    name:"楼主",
                    ifLZ:true
                },
                up:200,
                down:10,
                replySentence:"要切实发挥大项目、大企业的牵引作用，着力支持点多面广的小微企业和个体工商户复商复市，带动产业链上下游、大中小企业协同复工复产达产。",
                // 是否点赞
                replyLike: true,
                replyLikeNum:200,
                // 是否踩
                replyTrample: true, 
                replyTrampleNum: 10, 
                createTime:  "03-22 16:05"
            },
            {
                user:{
                    name:"小明",
                    ifLZ:false
                },
                up:188,
                down:10,
                replySentence:"好,要切实发挥大项目、大企业的牵引作用，着力支持点多面广的小微企业和个体工商户复商复市，带动产业链上下游、大中小企业协同复工复产达产。",
                // 是否点赞
                replyLike: true,
                replyLikeNum:188,
                // 是否踩
                replyTrample: true, 
                replyTrampleNum: 10, 
                createTime:  "03-22 16:05"
            },
            {
                user:{
                    name:"小红",
                    ifLZ:false
                },
                up:188,
                down:10,
                replySentence:"好",
                // 是否点赞
                replyLike: true,
                replyLikeNum:188,
                // 是否踩
                replyTrample: true, 
                replyTrampleNum: 10, 
                createTime:  "03-22 16:05"
            },
            {
                user:{
                    name:"小刚",
                    ifLZ:false
                },
                up:188,
                down:10,
                replySentence:"好!!要切实发挥大项目、大企业的牵引作用，着力支持点多面广的小微企业和个体工商户复商复市，带动产业链上下游、大中小企业协同复工复产达产。",
                // 是否点赞
                replyLike: true,
                replyLikeNum:188,
                // 是否踩
                replyTrample: true, 
                replyTrampleNum: 10, 
                createTime:  "03-22 16:05"
            },
            {
                user:{
                    name:"小华",
                    ifLZ:false
                },
                up:188,
                down:10,
                replySentence:"好",
                // 是否点赞
                replyLike: true,
                replyLikeNum:188,
                // 是否踩
                replyTrample: true, 
                replyTrampleNum: 10, 
                createTime:  "03-22 16:05"
            }
        ]
    }
    let _reply_list = []
    for (let i = 0; i < 9; i ++) {
        const reply = {
            news_id: genID(36),
            comment_id: genID(36),
            user_avatar_url: 'http://www.kevinbeason.com/smallpt/sky.png',
            user_id: genID(36),
            username: genTitle(3 + i % 2),
            comment: genTitle(35 + i),
            create_time: '2020-04-12 23:59',
            like_count: genNum(),
            user_like: false,
            oppose_count: genNum(),
            user_oppose: false
        }
        _reply_list.push(reply)
    }
    // res.send( _reply )
    res.send(_reply_list)
})

app.get('/my_favorite',(req,res) => {
    let _news_collect_list = []
    for (let i =0; i < 8; i ++) {
        let img_url = [];
        const img_num = Math.round(Math.random() * 3);   //衡获取0或1的随机整数。
        // console.log(img_num)
        if (img_num  > 1) {
            img_url.push('http://www.kevinbeason.com/smallpt/nightsky.png')
            img_url.push('http://www.kevinbeason.com/smallpt/nightsky.png')
            img_url.push('http://www.kevinbeason.com/smallpt/nightsky.png')
        }
        else if (img_num > 0) {
            img_url.push('http://www.kevinbeason.com/smallpt/nightsky.png')
        }
        else {
            img_url = []
        }
        // console.log('  ' + img_url.length)
        const _news_collection = {
            id: genID(36),
            news_id: genID(36),
            news_img_url: img_url,
            news_title: genTitle(i +  8),
            create_time: '2020-04-12 23:59',
            source: genTitle(4)
        }
        _news_collect_list.push(_news_collection)
    }
    res.send( _news_collect_list)
})

app.get('/my_comment',(req,res)=>{
    let _n = {
        a:'reply-list'
    }
    let _my_comment_list = []
    for (let i = 0; i < 9; i ++) {
        const _my_comment = {
            news_id: genID(36),
            news_title: genTitle(i + 20),
            others_comment_id: genID(36),
            user_id: genID(36),
            username: genTitle(3 + i % 2),
            others_comment: genTitle(65 + i),
            create_time: '2020-04-12 23:59',
            my_comment: genTitle(45 + i),
            my_comment_id: genID(36)
        }
        _my_comment_list.push(_my_comment)
    }
    res.send(_my_comment_list)
})

app.get('/my_thumb_up',(req,res)=>{
    console.log( req.query)
    let _my_thumb_up_list = []
    for (let i = 0; i < 9; i ++) {
        const _my_thumb_up = {
            news_id: genID(36),
            news_title: genTitle(i + 20),
            user_id: genID(36),
            // username: genTitle(3 + i % 2),
            author: genTitle(3 + i % 2),
            create_time: '2020-04-12 23:59',
            content: genTitle(45 + i),
            id: genID(36)
        }
        _my_thumb_up_list.push(_my_thumb_up)
    }
    res.send(_my_thumb_up_list)
})


app.listen(3344,()=>{
    console.log('启动！')
})

