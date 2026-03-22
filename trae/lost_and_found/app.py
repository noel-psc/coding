#!/usr/bin/env python3
"""
电费查询脚本
用于查询宿舍电费信息并直接返回剩余电费
"""

import requests
import argparse
import json
import re
import os
import pickle
from PIL import Image
import io
from pytesseract import image_to_string
import getpass
from pathlib import Path

# 配置
BASE_URL = 'https://epay.sues.edu.cn'
LOGIN_PATH = '/epay/person/index'
QUERY_PATH = '/epay/wxpage/wanxiao/eleresult'
HOME_PATH = '/'

# Cookie存储配置（存储在当前项目目录下）
COOKIE_DIR = Path(__file__).parent / '.cache'
COOKIE_FILE = COOKIE_DIR / 'cookie.enc'

def ensure_cookie_dir():
    """确保cookie目录存在"""
    COOKIE_DIR.mkdir(parents=True, exist_ok=True)

def load_cookie():
    """
    加载保存的cookie
    """
    ensure_cookie_dir()
    if COOKIE_FILE.exists():
        try:
            with open(COOKIE_FILE, 'rb') as f:
                return pickle.load(f)
        except:
            return None
    return None

def save_cookie(cookies):
    """
    保存cookie
    """
    ensure_cookie_dir()
    with open(COOKIE_FILE, 'wb') as f:
        pickle.dump(cookies, f)

def recognize_captcha(image_content):
    """
    识别数字验证码
    
    Args:
        image_content: 图片内容
    
    Returns:
        str: 识别的验证码
    """
    try:
        img = Image.open(io.BytesIO(image_content))
        # 预处理图片以提高识别率
        img = img.convert('L')  # 转为灰度图
        img = img.point(lambda x: 0 if x < 128 else 255, '1')  # 二值化
        
        # 使用pytesseract识别
        captcha = image_to_string(img, config='--psm 7 -c tessedit_char_whitelist=0123456789')
        captcha = captcha.strip()
        print(f"识别的验证码: {captcha}")
        return captcha
    except Exception as e:
        print(f"验证码识别失败: {str(e)}")
        return None

def login(session, username, password):
    """
    登录系统
    
    Args:
        session: requests会话对象
        username: 用户名
        password: 密码
    
    Returns:
        bool: 登录是否成功
    """
    try:
        # 访问登录页面
        login_url = BASE_URL + LOGIN_PATH
        print(f"\n访问登录页面: {login_url}")
        response = session.get(login_url)
        
        print(f"登录页面状态码: {response.status_code}")
        
        # 提取CSRF Token
        csrf_token = None
        csrf_pattern = r'<meta name="_csrf" content="([^"]+)"/>'
        csrf_match = re.search(csrf_pattern, response.text)
        if csrf_match:
            csrf_token = csrf_match.group(1)
            print(f"CSRF Token: {csrf_token}")
        
        # 提取验证码图片URL
        captcha_pattern = r'<img[^>]+src="([^"]*imageCode[^"]*)"'
        captcha_match = re.search(captcha_pattern, response.text)
        
        captcha = None
        if captcha_match:
            captcha_url = captcha_match.group(1)
            if not captcha_url.startswith('http'):
                captcha_url = BASE_URL + captcha_url
            
            print(f"\n访问验证码图片: {captcha_url}")
            
            # 下载验证码图片
            captcha_response = session.get(captcha_url)
            
            # 识别验证码
            captcha = recognize_captcha(captcha_response.content)
        else:
            print("未找到验证码图片，尝试无验证码登录")
        
        # 提取登录表单
        form_pattern = r'<form[^>]+action="([^"]+)"'
        form_match = re.search(form_pattern, response.text)
        
        if form_match:
            form_action = form_match.group(1)
            if form_action.startswith('/'):
                form_action = BASE_URL + form_action
            elif not form_action.startswith('http'):
                form_action = BASE_URL + '/' + form_action
            
            print(f"\n提交登录表单: {form_action}")
            
            # 提取所有输入字段
            input_pattern = r'<input[^>]+name="([^"]+)"[^>]+value="([^"]*)"'
            input_matches = re.findall(input_pattern, response.text)
            
            print(f"输入字段: {input_matches}")
            
            # 构建表单数据
            form_data = {}
            for name, value in input_matches:
                form_data[name] = value
            
            # 添加用户名、密码和验证码
            form_data['j_username'] = username
            form_data['j_password'] = password
            if captcha:
                form_data['imageCodeName'] = captcha
            
            print(f"提交的表单数据: {form_data}")
            
            # 提交表单
            headers = {}
            if csrf_token:
                headers['X-CSRF-TOKEN'] = csrf_token
            
            login_response = session.post(form_action, data=form_data, headers=headers)
            print(f"登录请求状态码: {login_response.status_code}")
            
            # 检查是否登录成功
            if '登录' not in login_response.text and '错误' not in login_response.text:
                print("登录成功")
                
                # 访问主页以建立会话
                home_url = BASE_URL + HOME_PATH
                print(f"\n访问主页: {home_url}")
                home_response = session.get(home_url)
                print(f"主页状态码: {home_response.status_code}")
                
                # 保存cookie
                save_cookie(session.cookies.get_dict())
                return True
            else:
                print("登录失败，请检查用户名、密码或验证码")
                return False
        else:
            print("未找到登录表单")
            return False
    except Exception as e:
        print(f"登录失败: {str(e)}")
        return False

def query_electric_bill(sysid='4', roomid='4021', areaid='101', buildid='13'):
    """
    查询宿舍电费信息
    
    Args:
        sysid: 系统ID
        roomid: 房间号
        areaid: 电表区域
        buildid: 楼栋ID
    
    Returns:
        dict: 电费信息
    """
    try:
        # 创建会话对象
        session = requests.Session()
        
        # 尝试加载保存的cookie
        saved_cookies = load_cookie()
        if saved_cookies:
            print("使用保存的cookie")
            session.cookies.update(saved_cookies)
        else:
            # 第一次运行，询问用户名和密码
            print("第一次运行，需要登录")
            username = input("请输入用户名: ")
            password = getpass.getpass("请输入密码: ")
            
            # 登录
            if not login(session, username, password):
                return {
                    'retcode': -1,
                    'retmsg': '登录失败，请检查用户名、密码或验证码'
                }
        
        # 访问主页以建立会话
        home_url = BASE_URL + HOME_PATH
        print(f"\n访问主页: {home_url}")
        home_response = session.get(home_url)
        print(f"主页状态码: {home_response.status_code}")
        
        # 发送查询电费的请求
        query_url = BASE_URL + QUERY_PATH
        print(f"\n发送查询电费请求: {query_url}")
        
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36 Edg/146.0.0.0'
        }
        
        params = {
            'sysid': sysid,
            'roomid': roomid,
            'areaid': areaid,
            'buildid': buildid
        }
        
        print(f"请求参数: {params}")
        
        query_response = session.get(query_url, params=params, headers=headers)
        
        # 打印响应内容以便调试
        print(f"查询响应状态码: {query_response.status_code}")
        
        # 从HTML中提取剩余电量
        pattern = r'(\d+\.?\d*)\s*度'
        match = re.search(pattern, query_response.text)
        
        if match:
            rest_degree = float(match.group(1))
            return {
                'retcode': 0,
                'retmsg': '成功',
                'restElecDegree': rest_degree
            }
        else:
            return {
                'retcode': -1,
                'retmsg': '未找到剩余电量信息'
            }
    except Exception as e:
        return {
            'retcode': -1,
            'retmsg': f'错误: {str(e)}'
        }

def main():
    """
    主函数
    """
    parser = argparse.ArgumentParser(description='电费查询工具')
    parser.add_argument('--sysid', default='4', help='系统ID')
    parser.add_argument('--roomid', default='4021', help='房间号')
    parser.add_argument('--areaid', default='101', help='电表区域')
    parser.add_argument('--buildid', default='13', help='楼栋ID')
    
    args = parser.parse_args()
    
    result = query_electric_bill(
        sysid=args.sysid,
        roomid=args.roomid,
        areaid=args.areaid,
        buildid=args.buildid
    )
    
    if result.get('retcode') == 0:
        print(f"\n剩余电费: {result.get('restElecDegree', '未知')} 度")
    else:
        print(f"\n查询失败: {result.get('retmsg', '未知错误')}")

if __name__ == '__main__':
    main()