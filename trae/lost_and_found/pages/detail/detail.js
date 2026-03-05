Page({
  data: {
    item: {}
  },

  onLoad(options) {
    const id = options.id
    this.loadItemDetail(id)
  },

  async loadItemDetail(id) {
    wx.showLoading({
      title: '加载中...'
    })
    
    try {
      const db = wx.cloud.database()
      const result = await db.collection('lost_and_found').doc(id).get()
      
      // 转换数据格式以匹配前端显示
      const item = {
        id: result.data._id,
        title: result.data.title,
        description: result.data.description,
        location: result.data.location,
        time: result.data.time,
        category: result.data.type,
        publisher: '用户', // 实际项目中可以从用户信息中获取
        contact: result.data.contact,
        image: result.data.images && result.data.images.length > 0 ? result.data.images[0] : 'https://trae-api-cn.mchost.guru/api/ide/v1/text_to_image?prompt=lost%20and%20found&image_size=square_4_3'
      }
      
      this.setData({
        item: item
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

  contactPublisher() {
    const { contact, publisher } = this.data.item
    
    if (contact) {
      wx.showModal({
        title: '联系发布者',
        content: `是否拨打 ${publisher} 的电话：${contact}？`,
        success: (res) => {
          if (res.confirm) {
            wx.makePhoneCall({
              phoneNumber: contact
            })
          }
        }
      })
    } else {
      wx.showToast({
        title: '暂无联系方式',
        icon: 'none'
      })
    }
  }
})