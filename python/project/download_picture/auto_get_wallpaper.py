# -*- coding: utf-8 -*-
"""
文 件 名: auto_get_wallpaper.py
文件描述: 自动下载图片壁纸（https://ss.netnr.com/wallpaper）
备    注：需要记录一下上次下载的位置，否则重复下载图片不可取
作    者: HanKin
创建日期: 2024.07.22
修改日期：2024.07.22

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import requests
from PIL import Image
from io import BytesIO
import psutil
import re
import subprocess

#伪造浏览器访问
HEADERS = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

# 睡眠等待时间
SLEEP_TIME = 2
 
def download_ss_wallpaper(url, save_file_path="./"):
    """下载图片(https://ss.netnr.com/wallpaper)
    :param url: 图片信息记录地址
    :param save_file_path: 保存目录路径
    :return null
    """
    
    page_text = requests.get(url=url, headers=HEADERS).json()
    img_list = page_text['data']
    wallpaper_index = 1
    for img in img_list:
        img_url = img['url']
        img_name = img['utag']
        print('正在下载第{}张壁纸=>>>{}......'.format(wallpaper_index, img_name))
        
        # 使用requests发送get请求
        response = requests.get(url=img_url, headers=HEADERS)
        
        # 检查请求是否成功
        if response.status_code == 200:
            # 获取图片内容
            img_data = response.content

            # 保存图片
            img_path = 'pictures/' + img_name + '.jpg'
            with open(img_path, 'wb') as save_img:
                save_img.write(img_data)
        else:
            print("无法获取图片")
        time.sleep(SLEEP_TIME)
        wallpaper_index += 1
    return

def main():
    """主函数
    """
    
    init_url = "https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D0%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time"
    # 使用正则表达式匹配start%3D0%26count位置的0
    pattern = r'start%3D(\d+)%26count'
    match = re.search(pattern, init_url)
    
    if match:
        # 获取匹配到的数字
        start_num = match.group(1)
        # 将数字修改为其他值（例如36）
        new_start_num = '36'
        # 替换URL中的数字
        new_url = re.sub(pattern, f'start%3D{new_start_num}%26count', init_url)
        print(new_url)
    else:
        print("未找到匹配的数字")
        return
    
    for i in range(10): # 18 * 10 = 180张壁纸
        # 替换URL中的数字
        new_url = re.sub(pattern, 'start%3D{}%26count'.format(i*18), init_url)
        print("正在下载壁纸数据json: {}".format(new_url))
        download_ss_wallpaper(new_url)

def debug():
    """调试
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    

