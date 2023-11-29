# -*- coding: utf-8 -*-
"""
文 件 名: seaborn_example.py
文件描述: seaborn库画图
备    注: pip install -U seaborn -i http://pypi.douban.com/simple --trusted-host pypi.douban.com
作    者: HanKin
创建日期: 2023.11.28
修改日期：2023.11.28

1.seaborn.distplot() – 绘制单变量分布图
2.seaborn.jointplot() – 绘制双变量关系图
3.seaborn.pairplot() – 绘制多变量关系图
4.seaborn.barplot() – 绘制条形图
5.seaborn.countplot() – 绘制计数图
6.seaborn.boxplot() – 绘制箱线图
7.seaborn.violinplot() – 绘制小提琴图
8.seaborn.heatmap() – 绘制热力图
9.seaborn.lineplot() – 绘制线图
10.seaborn.scatterplot() – 绘制散点图

Copyright (c) 2023 HanKin. All rights reserved.
"""
import seaborn
import matplotlib.pyplot as plt

def barplot_example():
    """柱状图
    """
    months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
    sales = [100, 200, 150, 400, 300, 350]


    plt.xlabel('Year')
    plt.ylabel('Sales')
    plt.title('Sales by Year (Heatmap)')

    seaborn.barplot(x=months,y=sales)  # 使用seaborn配置柱状图的X轴和Y轴
    plt.show()

def scatterplot_example():
    """散点图
    """
    months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
    sales = [100, 200, 150, 400, 300, 350]


    plt.xlabel('Year')
    plt.ylabel('Sales')
    plt.title('Sales by Year (Heatmap)')

    seaborn.scatterplot(x=months,y=sales)  # 使用seaborn配置散点图的X轴和Y轴
    plt.show()

def histplot_example():
    """直方图
    """
    months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
    sales = [100, 200, 150, 400, 300, 350]


    plt.xlabel('Year')
    plt.ylabel('Sales')
    plt.title('Sales by Year (Heatmap)')

    seaborn.histplot(x=months,y=sales,kde=True)  # 使用seaborn配置直方图的X轴和Y轴
    plt.show()

def pointplot_example():
    """点线图
    """
    months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
    sales = [100, 200, 150, 400, 300, 350]


    plt.xlabel('Year')
    plt.ylabel('Sales')
    plt.title('Sales by Year (Heatmap)')

    seaborn.pointplot(x=months,y=sales,)  # 使用seaborn配置点线图的X轴和Y轴
    plt.show()

histplot_example()

import pandas as pd
data=pd.read_excel(r"D:\data.xlsx")
seaborn.histplot(x="months",kde=True,data=data)
plt.show()