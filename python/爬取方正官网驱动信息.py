# -*- coding: utf-8 -*-
"""
Created on Tue May 26 19:15:25 2020

@author: Administrator
"""

#!/usr/bin/python
 
from bs4 import BeautifulSoup
import requests
import xlwt
 
def getHouseList(url):
    house =[]
    headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.71 Safari/537.1 LBBROWSER'}
    #get从网页获取信息
    res = requests.get(url, headers=headers)
    #解析内容
    soup = BeautifulSoup(res.content, 'html.parser')
    #房源title
    housename_divs = soup.find_all('div',class_='bdl-body')
    if (not housename_divs):
        return house
    #print(housename_divs)
    for housename_div in housename_divs:
        #print(housename_div)
        housename_as=housename_div.find_all('td')
        if (not housename_as):
            return house
        #print(housename_as)
        return housename_as[1]
        for housename_a in housename_as:
            housename=[]
            #标题
            housename.append(housename_a.get_text())
            #print(housename_a.get_text())
            house.append(housename)
    return house
 
#爬取房屋详细信息：所在区域、套内面积
def houseinfo(url):
    headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.71 Safari/537.1 LBBROWSER'}
    res = requests.get(url,headers=headers)
    soup = BeautifulSoup(res.content,'html.parser')
    msg =[]
    #所在区域
    areainfos = soup.find_all('span',class_='info')
    for areainfo in areainfos:
        #只需要获取第一个a标签的内容即可
        area = areainfo.find('a')
        if(not area):
            continue
        hrefStr = area['href']
        if(hrefStr.startswith('javascript')):
            continue
        msg.append(area.get_text())
        break
    #根据房屋户型计算套内面积
    infolist = soup.find_all('div',id='infoList')
    num = []
    for info in infolist:
        cols = info.find_all('div',class_='col')
        for i in cols:
            pingmi = i.get_text()
            try:
                a = float(pingmi[:-2])
                num.append(a)
            except ValueError:
                continue
    msg.append(sum(num))
    return msg
 
#将房源信息写入excel文件
def writeExcel(excelPath,houses):
    workbook = xlwt.Workbook()
    #获取第一个sheet页
    sheet = workbook.add_sheet('git')
    row0=['网页编号', '驱动名称']
    for i in range(0,len(row0)):
        sheet.write(0,i,row0[i])
    for i in range(0,len(houses), 2):
        print(i)
        house = houses[i]
        #print(house)
        #for j in range(0,len(house)):
        #    sheet.write(i+1,j,house[j])
        sheet.write(int(i/2) + 1,0, houses[i+1])
        sheet.write(int(i/2) + 1,1, house)
        #sheet.write(i+1,1, house[1])

    workbook.save(excelPath)
 
#主函数
def main():
    data = []
    #经过测试发现网页范围300-589
    for i in range(0, 1000):
        print('-----分隔符',i,'-------')
        url='http://www.foundertech.com/drivers/list_'+str(i)+'.html'
        houses =getHouseList(url)
        print(houses)
        for house in houses:
            print(house)
        if (not houses):
            continue
        houses.append(str(i))
        print(houses)
        data.extend(houses)
    writeExcel('d:/house1.xls', data)
 
if __name__ == '__main__':
    main()