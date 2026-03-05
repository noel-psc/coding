Page({
  data: {
    myPosts: []
  },

  onLoad() {
    this.loadMyPosts()
  },

  async loadMyPosts() {
    const app = getApp()
    if (!app.globalData.openid) {
      wx.showToast({
        title: '登录失败，请重新启动小程序',
        icon: 'none'
      })
      return
    }

    wx.showLoading({
      title: '加载中...'
    })
    
    try {
      const db = wx.cloud.database()
      const result = await db.collection('lost_and_found')
        .where({ openid: app.globalData.openid })
        .orderBy('createdAt', 'desc')
        .get()
      
      // 转换数据格式以匹配前端显示
      const formattedPosts = result.data.map(item => ({
        id: item._id,
        title: item.title,
        description: item.description,
        location: item.location,
        time: item.time,
        category: item.type,
        publisher: '我',
        image: item.images && item.images.length > 0 ? item.images[0] : 'https://trae-api-cn.mchost.guru/api/ide/v1/text_to_image?prompt=lost%20and%20found&image_size=square_4_3'
      }))
      
      this.setData({
        myPosts: formattedPosts
      })
    } catch (err) {
      console.error('加载数据失败', err)
      wx.showToast({
        title: '加载失败，请重试',
        icon: 'none'
      })
    } finally {
      wx.hideLoading()
    }
  },

  editPost(e) {
    const id = e.currentTarget.dataset.id
    wx.showToast({
      title: '编辑功能开发中',
      icon: 'none'
    })
  },

  async deletePost(e) {
    const id = e.currentTarget.dataset.id
    wx.showModal({
      title: '确认删除',
      content: '确定要删除这条发布吗？',
      success: async (res) => {
        if (res.confirm) {
          wx.showLoading({
            title: '删除中...'
          })
          
          try {
            const db = wx.cloud.database()
            await db.collection('lost_and_found').doc(id).remove()
            
            // 更新本地数据
            const myPosts = this.data.myPosts.filter(item => item.id !== id)
            this.setData({
              myPosts: myPosts
            })
            
            wx.hideLoading()
            wx.showToast({
              title: '删除成功',
              icon: 'success'
            })
          } catch (err) {
            wx.hideLoading()
            console.error('删除失败', err)
            wx.showToast({
              title: '删除失败，请重试',
              icon: 'none'
            })
          }
        }
      }
    })
  },

  navigateToPublish() {
    wx.switchTab({
      url: '/pages/publish/publish'
    })
  }
})