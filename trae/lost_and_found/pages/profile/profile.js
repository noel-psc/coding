Page({
  data: {
    userInfo: {}
  },

  onLoad() {
    this.getUserInfo()
  },

  getUserInfo() {
    // 模拟用户信息
    this.setData({
      userInfo: {
        nickName: '上工程大学生',
        avatarUrl: 'https://trae-api-cn.mchost.guru/api/ide/v1/text_to_image?prompt=user%20avatar%20placeholder&image_size=square'
      }
    })
  },

  navigateToMyPosts() {
    wx.navigateTo({
      url: '/pages/my-posts/my-posts'
    })
  }
})