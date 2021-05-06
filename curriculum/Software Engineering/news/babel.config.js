module.exports = {
  presets: [
    '@vue/cli-plugin-babel/preset'
  ],
  plugins: [
    // ['import', {
    //   libraryName: 'mint-ui',
    //   // libraryDirectory: 'es',
    //   style: true
    // }, 'mint-ui'],
    ['component',
      {
        libraryName: 'mint-ui',
        style: true
      }
    ]
  ]
}
