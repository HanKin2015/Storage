# -*- coding: utf-8 -*-
"""
文 件 名: matplotlib_example.py
文件描述: matplotlib库画图
备    注: 
作    者: HanKin
创建日期: 2023.11.28
修改日期：2023.11.28

Copyright (c) 2023 HanKin. All rights reserved.
"""
import matplotlib.pyplot as plt


months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
sales = [100, 200, 150, 400, 300, 350]

# 创建绘制图表数据
plt.plot(months, sales)

plt.xlabel('Months')    # 设置X轴
plt.ylabel('Sales')     # 设置Y轴
plt.title('Sales Data') # 设置图表名称

plt.show()

