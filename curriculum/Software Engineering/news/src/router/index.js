import Vue from 'vue'
import VueRouter from 'vue-router'
import newsList from '../views/newsList.vue'
import settings from '../views/settings.vue'
import newsDetails from '../views/newsDetails.vue'
import myCenter from '@/views/myCenter'
import changePassword from '@/views/changePassword'
import changeUserInfo from '@/views/changeUserInfo'
import loginPage from '@/views/loginPage'
import registerPage from '@/views/registerPage'
import commentsDetails from '@/views/commentsDetails'
import changePwProtection from '@/views/changePwProtection'
import forgetPassword from '@/views/forgetPassword'
import reply from '@/views/reply'
import myThumbUp from '@/views/myThumbUp'
import myComment from '@/views/myComment'
import myCollection from '@/views/myCollection'
import userReport from '@/views/userReport'
import drag from '@/views/drag'

import store from '@/store'

Vue.use(VueRouter)

const routes = [
  // 首页-新闻列表
  {
    path: '/',
    name: 'index',
    // component: Settings
    // component: Test
    redirect: '/news_list'
    // redirect: '/login'
    // redirect: '/drag'
  },
  // 新闻列表页
  {
    path: '/news_list',
    name: 'newsList',
    component: newsList
  },
  // 新闻详情页
  {
    path: '/news_details/:news_id',
    name: 'newsDetails',
    component: newsDetails
  },
  // 评论详情
  {
    path: '/news_details/:news_id/comments',
    name: 'commentsDetails',
    component: commentsDetails
  },
  // 应用设置页
  {
    path: '/my_center/settings',
    name: 'settings',
    component: settings
  },
  // 个人中心页
  {
    path: '/my_center',
    name: 'myCenter',
    component: myCenter
  },
  // 用户信息修改页
  {
    path: '/my_center/change_info',
    name: 'changeUserInfo',
    component: changeUserInfo,
    meta: {
      requireAuth: true
    }
  },
  // 修改密码(通过原密码)
  {
    path: '/change_password',
    name: 'changePassword',
    component: changePassword,
    meta: {
      requireAuth: true
    }
  },
  // 设置密保问题
  {
    path: '/change_pw_protection',
    name: 'changePwProtection',
    component: changePwProtection,
    meta: {
      requireAuth: true
    }
  },
  // 忘记密码页
  {
    path: '/forget_password',
    name: 'forgetPassword',
    component: forgetPassword
  },
  // 我的点赞
  {
    path: '/my_center/thumb_up_comments',
    name: 'myThumbUp',
    component: myThumbUp,
    meta: {
      requireAuth: true
    }
  },
  // 我的评论
  {
    path: '/my_center/comments',
    name: 'myComment',
    component: myComment,
    meta: {
      requireAuth: true
    }
  },
  // 我的收藏
  {
    path: '/my_center/collection',
    name: 'myCollection',
    component: myCollection,
    meta: {
      requireAuth: true
    }
  },
  // 登录页
  {
    path: '/login',
    name: 'loginPage',
    component: loginPage
  },
  // 注册页
  {
    path: '/register',
    name: 'register',
    component: registerPage
  },
  // 评论回复
  {
    path: '/news_details/:news_id/comments/:comment_id',
    // path: '/reply',
    name: 'reply',
    component: reply
    // meta: {
    //   requireAuth: true
    // }
  },
  // 使用报告页
  {
    path: '/my_center/user_report',
    name: 'userReport',
    component: userReport,
    meta: {
      requireAuth: true
    }
  },
  {
    path: '/drag',
    name: 'drag',
    component: drag
  }

  //
  // {
  //   path: '*',
  //   redirect: '/news_list'
  // }

  // {
  //   path:'/about',
  //   name: 'About',
  //   route level code-splitting
  //   this generates a separate chunk (about.[hash].js) for this route
  //   which is lazy-loaded when the route is visited.
  //   component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  // }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

router.beforeEach((to, from, next) => {
  if (to.matched.some(record => record.meta.requireAuth)) { // 需要登录验证
    if (store.getters.ifLogin) { // 已登录
      next()
    } else { // 未登录
      // 跳转到登录页
      console.log('未登录')
      next({
        path: '/login',
        query: {
          redirect: to.fullPath // 在完成登录后，回到登录前的页面
        }
      })
    }
  } else { // 不需要登录验证
    next()
  }
  // let isLogin = window.sessionStorage.getItem()
})

export default router
