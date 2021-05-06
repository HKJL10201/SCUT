<template>
<div>
    <draggable v-model="colors" @update="datadragEnd" :options = "{animation:500, handle: '.bd'}" class="drag-wrap">
                <transition-group>
                    <div v-for="element in colors.slice(0, 2)" :key="element.text" class = "drag-item">
                        {{element.text}}
                    </div>
                    <div v-for="element in colors.slice(2)" :key="element.text" class = "bd drag-item">
                        {{element.text}}
                    </div>
                    <div class="drag-item placeholder" v-for="index in 3" :key="'p' + index">
                    </div>
                    <!-- <div v-for="element in colors" :key="element.text" class = "drag-item">
                        {{element.text}}
                    </div> -->
                </transition-group>
    </draggable>
    <van-button @click="add">添加</van-button>
    <van-button @click="remove">移除</van-button>
</div>
</template>

<script>
export default {
  name: 'drag',
  //   components: {
  //     draggable
  //   }
  data () {
    return {
      msg: '这是测试组件',
      colors: [
        {
          text: 'Aquamarine'
        },
        {
          text: 'Hotpink'
        },
        {
          text: 'Gold'
        },
        {
          text: 'Crimson'
        },
        {
          text: 'Blueviolet'
        },
        {
          text: 'Lightblue'
        },
        {
          text: 'Cornflowerblue'
        },
        {
          text: 'Skyblue'
        },
        {
          text: 'Burlywood'
        }
      ],
      startArr: [],
      endArr: [],
      count: 0
    }
  },
  methods: {
    add () {
      const a = { text: 'bbb' }
      this.colors.push(a)
    },
    remove () {
      this.colors.splice(3, 1)
    },
    getdata (evt) {
      console.log(evt.draggedContext.element.text)
    },
    datadragEnd (evt) {
      evt.preventDefault()
      console.log('拖动前的索引 :' + evt.oldIndex)
      console.log('拖动后的索引 :' + evt.newIndex)
      console.log(this.colors)
    }
  }
}
</script>

<style lang="scss" scoped>
 .test{
        border:1px solid #ccc;
    }
    .drag-item{
        width: 50px;
        height: 50px;
        line-height: 50px;
        // margin: auto;
        position: relative;
        background: #ddd;
        margin-top:20px;
        margin-right: 30px;
        margin-left: 30px;
    }
    .ghostClass{
        opacity: 1;
    }
    .bottom{
        width: 200px;
        height: 50px;
        position: relative;
        background: blue;
        top:2px;
        left: 2px;
        transition: all .5s linear;
    }
    .drag-wrap {
        span {
            display: flex;
            flex-wrap: wrap;
        }
    }

    .placeholder {
    /* visibility: hidden; */
    height: 0 !important;
    border: 0 !important;
    padding: 0 !important;
    margin: 0 !important;
    box-shadow: none !important;
  }

</style>
