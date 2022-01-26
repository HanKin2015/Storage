'''
世界上流量最大的网站有哪些，也许我们都能脱口而出，比如 Google，YouTube，Facebook 还有 PxxnHub 等等，今天我们就通过多个维度来看看，那些叱咤全球的流量网站！

图片
数据获取




首先我们还是先抓取数据，目标网站是如下地址

https://www.visualcapitalist.com/the-50-most-visited-websites-in-the-world/

该页面有如下一个表格，里面罗列的全球流量前50的网站，我们就抓取这个数据。

get_data.py:14: UserWarning: No parser was explicitly specified, so I'm using the best available HTML parser for this system ("lxml"). This usually isn't a problem, but if you run this code on another
 system, or in a different virtual environment, it may use a different parser and behave differently.

The code that caused this warning is on line 14 of the file get_data.py. To get rid of this warning, pass the additional argument 'features="lxml"' to the BeautifulSoup constructor.
'''

import requests
import pandas as pd
from bs4 import BeautifulSoup

# 使用 requests 访问页面，通过 BeautifulSoup 解析网页
headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36"}

res = requests.get("https://www.visualcapitalist.com/the-50-most-visited-websites-in-the-world/", headers=headers)

soup = BeautifulSoup(res.text, features="lxml")
tbody = soup.find("table").find("tbody")
tr_list = tbody.find_all("tr")
data_list = []
for tr in tr_list:
    tds = tr.find_all("td")
    tmp = []
    for td in tds:
        tmp.append(td.text)
    data_list.append(tmp)
print(data_list)

# 整理成 DataFrame 形式
df = pd.DataFrame(data_list)
df.rename(columns={0:'Rank',1:'WebSite',2:'Traffic', 3:'Country', 4:'Type'},inplace=True)
df['new_Traffic'] = df['Traffic'].apply(lambda x: x.split("B")[0] if "B" in x else float(x.split("M")[0])/1000)
print(df)

# 转换下格式，保存成csv文件
web_name = df['WebSite'].values.tolist()
newdf = pd.DataFrame(np.repeat(df.values,24,axis=0))
newdf.columns = df.columns
newdf['date'] = ''
for i, r in newdf.iterrows():

    print(r['WebSite'])
    tag = 0
    ni = 0
    for j in web_name[::-1]:
        if r['WebSite'] == j:
            print(tag)
            print(ni)
            r['date'] = d_list[tag:]
            ni += 1
        tag += 1
newdf=newdf[['WebSite','Type','new_Traffic', 'date']]
newnew = newdf.rename(columns={'WebSite':'name','Type': 'type', 'new_Traffic':'value'})
newnew.to_csv('newdf.csv', index=0)