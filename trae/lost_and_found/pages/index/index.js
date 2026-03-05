Page({
  data: {
    items: [],
    searchText: '',
    activeCategory: 'all',
    hasMore: true,
    page: 1
  },

  onLoad() {
    this.loadItems()
  },

  async loadItems() {
    wx.showLoading({
      title: '加载中...'
    })
    
    try {
      const db = wx.cloud.database()
      let query = db.collection('lost_and_found').orderBy('createdAt', 'desc')
      
      // 根据分类筛选
      if (this.data.activeCategory !== 'all') {
        query = query.where({ type: this.data.activeCategory })
      }
      
      const result = await query.get()
      
      // 转换数据格式以匹配前端显示
      const formattedItems = result.data.map(item => ({
        id: item._id,
        title: item.title,
        description: item.description,
        location: item.location,
        time: item.time,
        category: item.type,
        publisher: '用户', // 实际项目中可以从用户信息中获取
        image: item.images && item.images.length > 0 ? item.images[0] : 'https://trae-api-cn.mchost.guru/api/ide/v1/text_to_image?prompt=lost%20and%20found&image_size=square_4_3'
      }))
      
      this.setData({
        items: formattedItems
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

  onSearchInput(e) {
    this.setData({
      searchText: e.detail.value
    })
  },

  selectCategory(e) {
    this.setData({
      activeCategory: e.currentTarget.dataset.category,
      page: 1,
      items: []
    })
    this.loadItems()
  },

  navigateToDetail(e) {
    const id = e.currentTarget.dataset.id
    wx.navigateTo({
      url: `/pages/detail/detail?id=${id}`
    })
  },

  loadMore() {
    // 模拟加载更多
    setTimeout(() => {
      this.setData({
        hasMore: false
      })
    }, 1000)
  }
})