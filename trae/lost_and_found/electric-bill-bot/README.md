# NoneBot 电费查询插件

一个用于查询宿舍电费余额的NoneBot插件。

## 功能

- 自动登录学校官网
- OCR识别验证码
- 查询宿舍电费余额
- 支持多用户
- Cookie持久化存储

## 安装

使用uv安装依赖：

```bash
uv install
```

或使用pip：

```bash
pip install -r requirements.txt
```

## 使用方法

### 1. 设置账号

```
设置电费账号 用户名 密码
```

### 2. 查询电费

```
电费查询
```

或指定参数：

```
电费查询 系统ID 房间号 区域ID 楼栋ID
```

## 配置

在NoneBot的配置文件中添加以下配置：

```python
# 默认查询参数
electric_bill_default_sysid = "4"
electric_bill_default_roomid = "4021"
electric_bill_default_areaid = "101"
electric_bill_default_buildid = "13"
```

## 依赖

- nonebot2 >= 2.0.0
- nonebot-adapter-onebot >= 2.0.0
- requests
- Pillow
- pytesseract

## 注意事项

1. 需要安装Tesseract OCR引擎
2. 用户名和密码会存储在本地，请注意安全
3. Cookie会定期过期，需要重新登录

## 许可证

MIT License