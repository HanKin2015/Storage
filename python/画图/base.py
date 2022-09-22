# -*- coding: utf-8 -*-
"""
文 件 名: base.py
文件描述: 一些基本的绘图常用语句（https://blog.csdn.net/Gou_Hailong/article/details/120089602）
作    者: HanKin
创建日期: 2022.09.20
修改日期：2022.09.20

Copyright (c) 2022 HanKin. All rights reserved.
"""
import matplotlib.pyplot as plt			# 导入模块

plt.style.use('ggplot')					# 设置图形的显示风格
fig=plt.figure(1)						# 新建一个 figure1
fig=plt.figure(figsize=(12,6.5),dpi=100,facecolor='w')
fig.patch.set_alpha(0.5)				# 设置透明度为 0.5
font1 = {'weight' : 60, 'size' : 10}	# 创建字体，设置字体粗细和大小
ax1.set_xlim(0,100)						# 设置 x 轴最大最小刻度
ax1.set_ylim(-0.1,0.1)					# 设置 y 轴最大最小刻度
plt.xlim(0,100)  						# 和上面效果一样
plt.ylim(-1,1)
ax1.set_xlabel('X name',font1)			# 设置 x 轴名字
ax1.set_ylabel('Y name',font1)			# 设置 y 轴名字
plt.xlabel('aaaaa')						# 设置 x 轴名字
plt.ylabel('aaaaa')						# 设置 y 轴名字
plt.grid(True)					 		# 增加格网
plt.grid(axis="y")						# 只显示横向格网
plt.grid(axis="x")						# 只显示纵向格网
ax=plt.gca()							# 获取当前axis,
fig=plt.gcf()							# 获取当前figures
plt.gca().set_aspect(1)					# 设置横纵坐标单位长度相等
plt.text(x,y,string)					# 在 x,y 处加入文字注释
plt.gca().set_xticklabels(labels, rotation=30, fontsize=16) # 指定在刻度上显示的内容
plt.xticks(ticks, labels, rotation=30, fontsize=15)   # 上面两句合起来
plt.legend(['Float'],ncol=1,prop=font1,frameon=False)	# 设置图例 列数、去掉边框、更改图例字体
plt.title('This is a Title')			# 图片标题
plt.show()								# 显示图片，没这行看不见图
plt.savefig(path, dpi=600)				# 保存图片，dpi可控制图片清晰度
plt.rcParams['font.sans-serif'] = ['SimHei']  	# 添加这条可以让图形显示中文
mpl.rcParams['axes.unicode_minus'] = False		# 添加这条可以让图形显示负号
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')				#设置图片的右边框和上边框为不显示
# 子图
ax1=plt.subplot(3,1,1)
ax1.scatter(time,data[:,1],s=5,color='blue',marker='o') # size, color, 标记
ax1=plt.subplot(3,1,2)

# 控制图片边缘的大小
plt.subplots_adjust(left=0, bottom=0, right=1, top=1, hspace=0.1,wspace=0.1)

# 设置坐标刻度朝向，暂未成功
plt.rcParams['xtick.direction'] = 'in'
ax = plt.gca()
ax.invert_xaxis() 
ax.invert_yaxis()
