# -*- coding: utf-8 -*-
"""
文 件 名: the_fun_of_python_library.py
文件描述: python库的乐趣
参    考: https://mp.weixin.qq.com/s/NKTpF-Zc_3dWPeBxULNMMw
作    者: HanKin
创建日期: 2022.12.30
修改日期：2022.12.30

Copyright (c) 2022 HanKin. All rights reserved.
"""
import time
import pyqrcode  
import png
import os
from pyqrcode import QRCode  
import cowsay
import pyttsx3
import calendar
import speedtest 
import stylecloud
import workbook
import matplotlib.pyplot as plt

def generate_qr_code():
    """生成二维码
    pip install pyqrcode
    pip install pypng
    """

    inpStr = "www.baidu.com"
    qrc = pyqrcode.create(inpStr)  
    qrc.png("baidu.png", scale=6) 

def strange_image():
    """画图，奇怪的图片
    pip install cowsay
    """

    #print(cowsay.trex('鸡'))
    print(cowsay.cow('美'))
    # 除此之外还有很多
    # beavis, cheese, daemon, cow, dragon, ghostbusters, kitty, meow, milk, pig,
    # stegosaurus, stimpy, trex, turkey, turtle, tux。

def play_game():
    """自带小游戏
    pip install freegames
    """

    # 查看所有游戏名称
    os.system('python -m freegames list')
    # 运行指定游戏
    os.system('python -m freegames.ant')

def word_to_voice():
    """文字转语音
    pip install pyttsx3
    """

    engine = pyttsx3.init()
    engine.say('你咋这么帅!')
    engine.runAndWait()  

def download_progressbar():
    """下载进度条
    """
    
    total = 132 # 可以用os获取文件大小
    for i in range(1, 101):
        time.sleep(0.3)
        print(f'\r共{total}MB, 已下载{i}MB, {int(i / total * 100)}%.', end='')

def show_calendar():
    """显示日历
    """
    
    year =int(input("请输入年份："))
    month = int(input("请输入月份："))
    print(calendar.month(year, month))

def test_network_speed():
    """测网速
    pip install speedtest-cli
    """

    print("准备测试ing...")
     
    # 创建实例对象
    test = speedtest.Speedtest()
    # 获取可用于测试的服务器列表
    test.get_servers()
    # 筛选出最佳服务器
    best = test.get_best_server()
     
    print("正在测试ing...")
     
    # 下载速度 
    download_speed = int(test.download() / 1024 / 1024)
    # 上传速度
    upload_speed = int(test.upload() / 1024 / 1024)
     
    # 输出结果
    print("下载速度：" + str(download_speed) + " Mbits")
    print("上传速度：" + str(upload_speed) + " Mbits")
    
def word_cloud():
    """词云 https://github.com/minimaxir/stylecloud
    pip install stylecloud
    """
    
    stylecloud.gen_stylecloud(file_path='./data/text.txt',icon_name="fas fa-dragon",output_name='dragon.png')

def generate_rand_data():
    """生成随机数据
    pip install faker
    pip install workbook
    
    安装的workbook有问题，咋使用的是python2风格
    SyntaxError: Missing parentheses in call to 'print'. Did you mean print("*** \033[31m" + title + "\033[0m ***")?
    """
    
    wb = workbook.Workbook()
    sheet = wb.worksheets[0]
    sheet.title = 'pd练习'
     
    li = ['序号', '姓名', '年龄', '性别', '健康程度', '国家']
    di = {'中国': 'zh_CN', '美国': 'en_US', '法国': 'fr_FR', '日本': 'ja_JP'}
     
    with open('new_message.xlsx', mode='w', encoding='utf-8') as f:
        for num, item in enumerate(li, 1):
            sheet.cell(1, num).value = item
     
        for num, i in enumerate(range(2, 502), 1):
            country = random.choice(['中国', '美国', '法国', '日本'])
            gender = random.choice(['男', '女'])
     
            fk = Faker(locale=di[country])
            sheet.cell(i, 1).value = num
            sheet.cell(i, 2).value = fk.name_male() if gender == '男' else fk.name_female()
            sheet.cell(i, 3).value = random.randint(14, 66)
            sheet.cell(i, 4).value = gender
            sheet.cell(i, 5).value = round(random.random(), 2)
            sheet.cell(i, 6).value = country
     
    wb.save('new_message.xlsx')

def draw_pie_chart():
    """绘制饼图
    """
    
    Partition = 'Teams A','Teams B','Teams C','Teams D'
    sizes = [250,100,150,200]
    fig1, ax1 = plt.subplots()
    ax1.pie(sizes, labels=Partition, autopct='%1.1f%%',shadow=True, startangle=90)
    ax1.axis('equal')
    plt.show()

def main():
    """主函数
    """
    
    #generate_qr_code()
    #strange_image()
    #play_game()
    #word_to_voice()
    #download_progressbar()
    #show_calendar()
    #test_network_speed()
    #word_cloud()
    #generate_rand_data()
    generate_rand_data()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

