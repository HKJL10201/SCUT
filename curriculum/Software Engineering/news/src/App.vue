<template>
  <div id="app">
    <router-view />
  </div>
</template>

<style lang="scss">
  #app {
    min-height: 100%;
    font-family: Microsoft YaHei;
    // background-color: #f6f6f6;
    @include themify {
      background-color: themed('theme-bg-color');
      color: themed('theme-font-color');
    }

    position: relative;
  }

  // body {
  //   background-color: #383838;
  // }

</style>
