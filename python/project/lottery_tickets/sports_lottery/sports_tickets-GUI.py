# -*- coding: utf-8 -*-
"""
文 件 名: lottery_tickets-GUI.py
文件描述: 福利彩票分析工具
作    者: HanKin
创建日期: 2021.06.08
修改日期：2022.08.15

1.获取历史数据
2.产生今日推荐数字
3.统计每个数字的次数和概率

Copyright (c) 2022 HanKin. All rights reserved.
"""

import pandas as pd

url = 'https://www.lottery.gov.cn/kj/kjlb.html?plw'
#url = 'http://www.12365auto.com/zlts/'
url = 'http://datachart.500.com/dlt/history/newinc/history.php?start=22063&end=22092'
url = 'https://webapi.sporttery.cn/gateway/lottery/getHistoryPageListV1.qry?gameNo=350133&provinceId=0&pageSize=30&isVerify=1&pageNo=3'
#table_data = pd.read_html(io=url, header=0, encoding='utf-8')[0]
json_data = pd.read_json(url, encoding='utf-8')
#print(table_data.shape)
print(json_data.shape)
print(json_data['value'][0])




