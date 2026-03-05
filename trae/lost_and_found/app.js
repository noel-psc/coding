App({
  onLaunch() {
    // 初始化云开发
    if (wx.cloud) {
      wx.cloud.init({
        env: 'test-env-12345', // 测试环境 ID，实际使用时需要替换为自己的云开发环境 ID
        traceUser: true
      })
    }
    
    // 登录
    wx.login({
      success: res => {
        console.log('登录成功', res)
        // 调用登录云函数获取 openid
        wx.cloud.callFunction({
          name: 'login',
          success: res => {
            console.log('获取 openid 成功', res.result.openid)
            this.globalData.openid = res.result.openid
          },
          fail: err => {
            console.error('获取 openid 失败', err)
          }
        })
      }
    })
  },
  globalData: {
    userInfo: null,
    openid: null
  }
})