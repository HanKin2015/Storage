from selenium import webdriver
import time
import os
import threading
import simplejson as json
from browsermobproxy import Server
import requests
from selenium.webdriver.chrome.options import Options
 
#Browsermob-proxy的路径
server=Server(r"D:\Python3.7\browser-proxy.bat\browsermob-proxy-2.1.4\bin\browsermob-proxy.bat")
server.start()#启动browsermob-proxy
proxy=server.create_proxy()
chrome_options=Options()
 
#获取游览器对象，设置无界面模式
chrome_options.add_argument('--proxy-server={0}'.format(proxy.proxy))
chrome_options.add_argument('--headless')#无头模式，不开启游览器界面
chrome_options.add_argument('--disable-gpu')
chrome_options.add_argument('--incognito')
driver=webdriver.Chrome(chrome_options=chrome_options)#启用谷歌游览器
 
#获取音乐的信息
def getDownloadUrls(name):
    
    musicUrl='http://tool.liumingye.cn/music/?page=audioPage&type=migu&name='+str(name)
    proxy.new_har('music',options={'captureHeaders':True,'captureContent':True})
    driver.get(musicUrl)#请求网站
    time.sleep(3)#等待页面加载完成，必须要延时，不然获取不到数据
    lists=[]
    #获取3页数据一共60首歌
    for i in range(3):
        index=0
        result=proxy.har#获取所有请求网址
        for entry in result['log']['entries']:
            url=entry['request']['url']
            #找对应的网址，我们要的是，search网址的
            if "app.onenine.cc/m/api/search" in url:
                index+=1
                '''
                因为每点击下一页都会产生一个新的‘search',
                而proxy每次都会把所有的请求获取到,所以上一个的’search‘也会获取到
                所以要判断排除掉，只获取最新的’search'
                '''
                if index>i:
                    content = entry['response']['content']
                    text=content['text']
                    data=json.loads(text)['data']
                    lists.extend(data['list']) #这里就是获取到的json数据.每一次添加20首歌曲的信息进去
                
        #滑到底部
        js="window.scrollTo(0,10000)"#滑动滚动条的js代码，如果元素不在页面上显示，是找不到的，所以滑动，让下一页的按钮显示出来
        driver.execute_script(js)#执行·js代码
        #点击下一页，获取更多歌曲
        nextBtn=driver.find_element_by_css_selector('#player>div.aplayer-more')#找到下一页的按钮
        nextBtn.click()#发送点击事件
        time.sleep(1)#延时1秒等待数据加载
    return lists
 
#用于下载音乐代码
def download(path,musicName,folder,ext):
    
    r=requests.get(path)
    f=open(folder+'/'+musicName+ext,'wb')
    f.write(r.content)
    f.close()
 
#在lists例表中提取音乐的下载地址和歌曲名字
def downloadMusic(name,type,lists):
    '''
    name：歌手名字，为每一个歌手都新建一个文件夹
    type:表示要下载何种音质
    lists:获取的音乐数据列表
    '''
    isExists=os.path.exists(name)
    if not isExists:
        os.makedirs(name)
    musicName=''
    path=''
    ext=''
    for item in lists:
        for key,value in item.items():
            ext='.mp3'
            key=str(key)
            if key=='name':
                musicName=value
            elif key=='artist':
                musicName=musicName+'-'+value
            elif key=='url_m4a' and type==0:#m4a表示流畅
                path=value
            elif key=='url_128' and type==1:#128是标准
                path=value
            elif key=='url_320' and type==2:#320是高品质
                path=value
            elif key=='url_flac'and type==3:#flac表示无损
                path=value
                ext='.flac'
 
            if len(path)!=0:
                #每一首歌开启一个线程去下载
                t = threading.Thread(target=download,args=(path,musicName,name,ext))
                t.start()
                t.join()
                path=''
                musicName=''
 
if __name__=='__main__':
    
    signer=input("输入歌手名字:")
    lists=getDownloadUrls(signer)
    print('获取完成,开始下载音乐')
    downloadMusic(signer,0,lists)#0表示下载流畅音质的
    print('下载结束')