# -*- coding: utf-8 -*-
"""
文 件 名: ss_baseline.py
文件描述: https://blog.csdn.net/HSX501560987/article/details/108660043
作    者: HanKin
创建日期: 2024.07.22
修改日期：2024.07.22

Copyright (c) 2024 HanKin. All rights reserved.
"""
import requests
 
if __name__ == "__main__":
    url = 'https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D18%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.83 Safari/537.36'
    }
    page_text = requests.get(url=url, headers=headers).json()
    img_list = page_text['data']
    for img in img_list:
        img_url = img['url']
        img_name = img['utag']
        img_data = requests.get(url=img_url, headers=headers).content
        img_Path = 'pictures/' + img_name + '.jpg'
        with open(img_Path, 'wb') as fp:
            fp.write(img_data)
