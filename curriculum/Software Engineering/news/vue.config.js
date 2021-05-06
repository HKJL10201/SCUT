const path = require('path')
module.exports = {
  css: {
    loaderOptions: {
      postcss: {
        plugins: [
          require('postcss-pxtorem')({ // 这里是配置项，详见官方文档
            rootValue: 37.5,
            unitPrecision: 5,
            // 换算的基准值，即将“多少px”转换为1rem
            // 这里应该等同于<html>由于在使用lib-flexible后，将<html>的font-size设置为屏幕宽的十分之一，因此屏幕总宽变为了10rem.
            // selectorBlackList : ['van'], // 忽略转换正则匹配项
            propList: ['*']
          })
        ]
      },
      scss: {
        prependData: '@import "~@/scss/mixins.scss";'
      }
    }
  },
  chainWebpack: config => {
    const svgRule = config.module.rule('svg')
    svgRule.uses.clear()
    svgRule
      .test(/\.svg$/)
      .include
      .add(path.resolve(__dirname, './src/icons'))
      .end()
      .use('svg-sprite-loader')
      .loader('svg-sprite-loader')
      .options({
        symbolId: 'icon-[name]'
      })
  },
  devServer: {
    proxy: {
      '/api': {
        target: 'https://m.toutiao.com',
        changeOrigin: true,
        pathRewrite: {
          '^/api': ''
        }
      }
    }
  }
}
