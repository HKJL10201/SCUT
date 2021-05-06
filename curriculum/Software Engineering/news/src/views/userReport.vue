<template>
  <div class="user-report-wrap">
    <!-- 顶部栏 -->
    <div class="header">
      <div id="nav-bar">
          <div id="nav-left">
            <van-icon id="nav-left-icon" name="arrow-left" @click="$router.back()"/>
          </div>
        <span>使用报告</span>
      </div>
    </div>
    <div class="usertime"></div>
    <!-- 折线图 -->
    <div class="chart" ref="useTimeChart"></div>
    <!-- 饼图 -->
    <div class="chart" ref="userChannelChart">
    </div>
    <div class="chart" ref="newsWordCloud">
    </div>
    <div class="chart-wrap">
    </div>
  </div>
</template>

<script>
require('echarts-wordcloud')
export default {
  name: 'userReport',
  data () {
    return {
      userTimeList: [],
      userChannelChart: [],
      newsWordList: [],
      newsChannel: {
        __all__: '推荐',
        news_hot: '热点',
        news_society: '社会',
        news_entertainment: '娱乐',
        news_tech: '科技',
        news_military: '军事',
        news_sports: '体育',
        news_car: '汽车',
        news_finance: '财经',
        news_world: '国际',
        news_fashion: '时尚',
        news_travel: '旅游',
        news_discovery: '探索',
        news_baby: '育儿',
        news_regimen: '养生',
        news_story: '故事',
        news_essay: '美文',
        news_game: '游戏',
        news_history: '历史',
        news_food: '美食'
      },
      mostUseTime: '',
      mostBrowChannel: ''
    }
  },
  methods: {
    FontChart (res) {
      // 获取到屏幕的宽度
      var clientWidth =
          window.innerWidth ||
          document.documentElement.clientWidth ||
          document.body.clientWidth
      if (!clientWidth) return // 报错拦截：
      const fontSize = 37.5 * (clientWidth / 750)
      return res * fontSize
    },
    // 初始化使用时段折线图
    initUseTimeChart () {
      const myChart = this.$echarts.init(this.$refs.useTimeChart)
      const option = {
        title: {
          text: '使用时段统计',
          left: 'center',
          textStyle: {
            color: '#91bcc2'
          }
        },
        tooltip: {
          trigger: 'axis',
          // axisPointer: {
          //   type: 'cross',
          //   label: {
          //     backgroundColor: '#6a7985'
          //   }
          // },
          // formatter: '时段: {b}时 ~ <br/> c\n({d}%)'
          formatter: function (params, ticket, callback) {
            // return params
            console.log(params)
            return params[0].marker + '时段:' + params[0].name + '~' + (params[0].name + 1) + '时' +
            '<br/>浏览量:' + params[0].value
          }
        },
        xAxis: {
          type: 'category',
          // boundaryGap: false,
          data: this.userTimeList.map((item) => {
            return {
              value: item.time
            }
          }),
          axisLabel: {
            show: true,
            textStyle: {
              color: '#91bcc2'
            },
            lineStyle: {
              color: '#91bcc2'
            }
          }
        },
        yAxis: {
          type: 'value',
          axisLine: {
            lineStyle: {
              color: '#444444'
            }
          },
          axisLabel: {
            show: true,
            textStyle: {
              color: '#91bcc2'
            }
          },
          splitLine: {
            lineStyle: {
              color: '#444444'
            }
          }
        },
        grid: {
          left: '3%',
          right: '4%',
          // bottom: '3%',
          containLabel: true
        },
        series: [{
          name: '使用时段',
          itemStyle: {
            // color: '#73b9bc'
            normal: {
              color: '#91bcc2',
              label: {
                show: true,
                // fontSize: '20',
                fontSize: this.FontChart(0.2),
                color: '#6db0b9'
              }
            }
          },
          data: this.userTimeList.map((item) => {
            return {
              value: item.value
            }
          }),
          // 折线图
          type: 'line',
          stack: '总量',
          areaStyle: {}
        }]
      }
      myChart.setOption(option)
    },
    // 初始化用户频道饼图
    initUserChannelChart () {
      const myChart = this.$echarts.init(this.$refs.userChannelChart)
      const option = {
        color: ['#ED6161', '#61a0a8', '#8dc1a9', '#e69d87', '#df856a', '#8ec7cf',
          '#8db2da', '#73b9bc', '#7289ab', '#91bcc2', '#8ddada', '#e9a0b0', '#f8d790', 'DDA38F'],
        // title: {
        //   text: '频道浏览量',
        //   left: 'center',
        //   top: 5,
        //   textStyle: {
        //     color: '#66A2E4',
        //     fontSize: '30'
        //   }
        // },
        tooltip: {
          trigger: 'item',
          formatter: '浏览量: {c}次 ({d}%)',
          textStyle: {
            fontSize: this.FontChart(0.65)
          }
        },
        series: [{
          data: this.userChannelChart.map((item) => {
            return {
              name: item.channel,
              value: item.value
            }
          }),
          type: 'pie',
          radius: ['50%', '70%'],
          center: ['50%', '50%'],
          itemStyle: {
            emphasis: {
              shadowBlur: 10,
              shadowOffsetX: 0,
              shadowColor: 'rgba(0, 0, 0, 0.5)'
            }
          },
          avoidLabelOverlap: false,
          label: {
            normal: {
              // show: false,
              // position: 'center'
              textStyle: {
                // fontSize: '25'
                fontSize: this.FontChart(0.65)
              }
            },
            emphasis: {
              show: true,
              textStyle: {
                // fontSize: '30',
                fontSize: this.FontChart(1.05),
                fontWeight: 'bold'
              }
            }
          },
          labelLine: {
            normal: {
              length: this.FontChart(1.3)
            }
          }

        }]
      }
      myChart.setOption(option)
    },
    // 获取用户使用数据
    getUserRecord () {
      this.$axios.get('https://afs7hx.toutiao15.com/getTimeHistory', {
        params: {
          username: this.userId
        }
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          console.log(res.data)
          this.userTimeList = res.data
          this.initUseTimeChart()
        } else {
          console.log('请求失败')
          this.$toast('请求失败')
        }
      })
      console.log(this.userId)
      this.$axios.get('https://afs7hx.toutiao15.com/getChannelHistory', {
        params: {
          username: this.userId
        }
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          console.log(res)
          this.userChannelChart = res.data.map((item) => {
            return {
              channel: this.newsChannel[item.channel],
              value: item.value
            }
          })
          console.log(this.userChannelChart)
          // 处理
          this.initUserChannelChart()
          //
          this.getMostBrowChannel()
        } else {
          console.log('请求失败')
          this.$toast('请求失败')
        }
      })
      this.$axios.get('https://afs7hx.toutiao15.com/getWordList', {
        params: {
          username: this.userId
        }
      }).then(response => {
        if (response.status === 200) {
          const res = response.data
          console.log(res)
          if (res.code === 1) {
            this.newsWordList = res.data
            this.iniNewsWordCloud()
          } else {
            this.$toast(res.msg)
          }
        } else {
          this.$toast('请求失败')
        }
      })
    },
    getMostBrowTime () {
    },
    // 初始化词云
    iniNewsWordCloud () {
      const newsWordCloudChart = this.$echarts.init(this.$refs.newsWordCloud)
      const option = {
        series: [{
          type: 'wordCloud',
          shape: 'circle',
          left: 'center',
          top: 'center',
          width: '70%',
          height: '80%',
          right: null,
          bottom: null,
          // Text size range which the value in data will be mapped to
          sizeRange: [12, 60],
          // Text rotation range and step in degree. Text will be rotated randomly in range [-90, 90] by rotationStep 45
          rotationRange: [-90, 90],
          rotationStep: 45,
          gridSize: 8,
          drawOutOfBound: false,
          // Global text style
          textStyle: {
            normal: {
              fontFamily: 'sans-serif',
              fontWeight: 'bold',
              // Color can be a callback function or a color string
              color: function () {
                // Random color
                return 'rgb(' + [
                  Math.round(Math.random() * 160),
                  Math.round(Math.random() * 160),
                  Math.round(Math.random() * 160)
                ].join(',') + ')'
              }
            },
            emphasis: {
              shadowBlur: 10,
              shadowColor: '#333'
            }
          },
          // data: [{
          //   name: 'Farrah Abraham',
          //   value: 366
          // },
          // {
          //   name: 'Sam S Club',
          //   value: 10000
          // }, {
          //   name: 'Macys',
          //   value: 6181
          // }, {
          //   name: 'Amy Schumer',
          //   value: 4386
          // }, {
          //   name: 'Jurassic World',
          //   value: 4055
          // }, {
          //   name: 'Charter Communications',
          //   value: 2467
          // }, {
          //   name: 'Chick Fil A',
          //   value: 2244
          // }, {
          //   name: 'Planet Fitness',
          //   value: 1898
          // }, {
          //   name: 'Pitch Perfect',
          //   value: 1484
          data: this.newsWordList
        }]
      }
      newsWordCloudChart.setOption(option)
    },
    getMostBrowChannel () {
      let tmpName
      let tmpValue = 0
      for (let i = 0; i < this.userChannelChart.length; i++) {
        if (this.userChannelChart[i].value > tmpValue) {
          tmpValue = this.userChannelChart[i].value
          tmpName = this.userChannelChart[i].channel
        }
      }
      console.log(tmpValue)
      console.log(tmpName)
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
    }
  },
  mounted: function () {
    // 获取用户数据
    this.getUserRecord()
    // this.iniNewsWordCloud()
  }
}

</script>

<style scoped lang="scss">
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

  #nav-left {
    height: 100%;
    position: absolute;
    display: flex;
    align-items: center;
    left: 10px;

    @include themify {
      color: themed('nav-font-color');
    }

    span {
      font-size: 14px;
    }
  }

  #nav-left-icon {
    font-size: 25px;
    font-weight: bolder;

    &:hover {
      cursor: pointer;
    }
  }

  .user-report-wrap {
    background-color: #2e2e2e;
    // min-height: 100%;
    // height:inherit;
    position: absolute;
    top:0; bottom: 0;  left: 0; right: 0; // 设置成0
  }

  .header {
    padding-top: 40px;
  }

  .chart-wrap {
  }

  .chart {
      height: 250px;
      width: 100%;
      color: #6db0b9;
      color: #df856a;
      color: #8ddada;
      color: #e9a0b0;
      color: #91bcc2;
      color: #dd6b66;
      color: #f8d790;
      color: #222222;
      color: #8ec7cf;

  }

</style>
