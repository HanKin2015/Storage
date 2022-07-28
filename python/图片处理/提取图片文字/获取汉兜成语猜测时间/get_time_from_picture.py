# -*- coding: utf-8 -*-
"""
文 件 名: get_time_frome_picture.py
文件描述: 从汉兜分享图片中获取花费时间
作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

from aip import AipOcr
import time
import os
import pandas as pd
import cv2
import numpy as np

# 新建一个AipOcr对象
config = {
    'appId': '26809185',
    'apiKey': 'FS7LVrhVp7ijY1fXVzuVtmHO',
    'secretKey': 'y9VscUnmWLZbTxBhULuqbdhYvwgA2j4d'
}
client = AipOcr(**config)

def adjust_brightness(image_path):
    """
    调整亮度
    """

    img = cv2.imread(image_path, 0)
    print(np.shape(img))
    kernel = np.ones((1,1), np.uint8)
    dilate = cv2.dilate(img, kernel, iterations=1)
    cv2.imwrite('./tmp.png', dilate)

def get_file_content(file_path):
    """
    读取图片
    """
    
    adjust_brightness(file_path)
    with open('./tmp.png', 'rb') as fp:
        return fp.read()

def img_to_str(image_path):
    """
    识别图片里的文字
    """

    image = get_file_content(image_path)

    # 调用通用文字识别，图片参数为本地图片
    result = client.basicGeneral(image)
    print(result)
    #result = {'words_result': [{'words': '汉兜'}, {'words': 'handle.antfu.me'}, {'words': 'yang'}, {'words': 'me'}, {'words': 'tu'}, {'words': '扬'}, {'words': '眉'}, {'words': '吐'}, {'words': '气'}, {'words': 'i'}, {'words': 'fei'}, {'words': 'dan'}, {'words': 'da'}, {'words': '鸡'}, {'words': '飞'}, {'words': '蛋'}, {'words': '打'}, {'words': 'gong'}, {'words': 'ren'}, {'words': '工'}, {'words': '人'}, {'words': '阶'}, {'words': '级'}, {'words': 'rd'}, {'words': 'bd'}, {'words': 'fu'}, {'words': 'ch u'}, {'words': '入'}, {'words': '不'}, {'words': '敷'}, {'words': '出'}, {'words': 'tian'}, {'words': 'bai'}, {'words': '蓝'}, {'words': '天'}, {'words': '白'}, {'words': '云'}, {'words': 'luan'}, {'words': 'n'}, {'words': 'zha'}, {'words': '杂'}, {'words': '乱'}, {'words': '颜'}, {'words': '章'}, {'words': 'zuo'}, {'words': 'lin'}, {'words': '左'}, {'words': '邻'}, {'words': '右'}, {'words': '舍'}, {'words': '二百零七日·无提示·2分11秒'}], 'words_result_num': 51, 'log_id': 1551928621594558466}

    #print(type(result), len(result))
    day_index = '零'; idiom = ''; spent_time = '0分0秒'
    if 'words_result' in result:
        idiom = result['words_result'][-5]['words']
        idiom += result['words_result'][-4]['words']
        idiom += result['words_result'][-3]['words']
        idiom += result['words_result'][-2]['words']
        print(idiom)
        day_index, no_tips, spent_time = result['words_result'][-1]['words'].split('·')
        #print(day_index, no_tips, spent_time)
    else:
        print('image_path: {}, result: {}'.format(image_path, result))

    # 结果拼接返回
    #if 'words_result' in result:
    #    return '\n'.join([w['words'] for w in result['words_result']])
    return day_index, idiom, spent_time

dict = {
    '零': 0,
    '一': 1,
    '二': 2,
    '三': 3,
    '四': 4,
    '五': 5,
    '六': 6,
    '七': 7,
    '八': 8,
    '九': 9
}
def chinese_to_number(chinese):
    """
    将中文数字转换成阿拉伯数字
    """
    
    num = 0
    tmp = 0
    flag = False
    for idx in range(len(chinese)):
        if not flag:
            tmp = 1
        if chinese[idx] == '百':
            num += tmp * 100;
            flag = False
        elif chinese[idx] == '十':
            num += tmp * 10;
            flag = False
        elif chinese[idx] == '日':
            if flag:
                num += tmp
            break
        elif chinese[idx] == '廿':
            num += 20
            flag = False
        else:
            tmp = dict[chinese[idx]]
            flag = True
        #print('tmp = {}, num = {}'.format(tmp, num))
    #print(chinese, num)
    return num

def time_to_seconds(spent_time):
    """
    时间转换成秒数
    """

    pos = spent_time.find('分')
    minute = spent_time[:pos]
    second = spent_time[pos+1:-1]
    #print(minute, second)
    return int(minute)*60+int(second)


def save_to_csv(data):
    """
    将解析结果保存到csv文件
    """
    
    df = pd.DataFrame(data, columns=['day_index', 'idiom', 'spent_time'])
    df.to_csv('./result.csv', index=False, header=True)

def processing(pic_dir):
    """
    """
    
    data = []
    failed_cnt = 0
    for root, dirs, files in os.walk(pic_dir):
        for file in files:
            pic_path = '{}/{}'.format(root, file)
            day_index, idiom, spent_time = img_to_str(pic_path)
            # 需要睡眠等待，否则会报错image_path: D:\将要上传到百度网盘\智慧小游戏/汉兜 百零八日.png, result: {'error_code': 18, 'error_msg': 'Open api qps request limit reached'}
            time.sleep(3)
            if idiom == '':
                failed_cnt += 1
            day_index = chinese_to_number(day_index)
            spent_time = time_to_seconds(spent_time)
            data.append([day_index, idiom, spent_time])
    print('failed count: {}'.format(failed_cnt))
    save_to_csv(data)
    
def main():
    """
    主函数
    """
    
    pic_dir = r'D:\将要上传到百度网盘\智慧小游戏'
    processing(pic_dir)

def debug():
    """
    调试
    """
    
    pic_dir = r'D:\将要上传到百度网盘\智慧小游戏'
    #print(img_to_str(r'D:\将要上传到百度网盘\智慧小游戏\汉兜 七十四日.png'))
    print(img_to_str('./test.png'))
    return 
    
    nums = []
    for root, dirs, files in os.walk(pic_dir):
        for file in files:
            pic_path = '{}/{}'.format(root, file)
            #print(file[3:-4])
            num = chinese_to_number(file[3:-4])
            nums.append(num)
    if len(nums) != len(set(nums)):
        print('chinese transfer to number has error')
    else:
        print('please person confirm chinese transfer to number is ringt')
    
    print(time_to_seconds('15分23秒'))

if __name__ == '__main__':
    print('******** starting ********')
    start_time = time.time()

    debug()
    #main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
