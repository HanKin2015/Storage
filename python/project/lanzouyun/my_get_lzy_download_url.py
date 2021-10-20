# -*- coding: utf-8 -*-
"""
文 件 名: my_get_lzy_download_url.py
文件描述: 获取蓝奏云下载直连链接
备    注: 演示一下什么是最简单的爬虫，尴尬打脸了，爬虫失败
作    者: HanKin
创建日期: 2021.10.19
修改日期：2021.10.19

Copyright (c) 2021 HanKin. All rights reserved.
"""

import  requests
import  bs4

#网站
g_urls = [
            ["https://wwe.lanzoui.com/{}","div.d > div", 0]
         ]

#伪造浏览器访问
g_headers = {
                'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36',
            }

#超时参数
g_timeout = 2

# 获取文件名
def crawl(target):
    result = []
    for url, regex, index in g_urls:
        target_url = url.format(target)
        html = ""
        try:
            html = requests.get(target_url, headers=g_headers, timeout=g_timeout)
            #print(html)
        except Exception:
            print('wrong')
            return None
    
        soup = bs4.BeautifulSoup(html.text, "html.parser")
    
        content = soup.select(regex)
        #print(content)
        if content and len(content) > index :
            result.append(content[index].get_text().strip())
    return result

# 获取嵌套的下载页面
def get_html(url):
    html = requests.get(url, headers=g_headers, timeout=g_timeout)
    soup = bs4.BeautifulSoup(html.text, "html.parser")
    download_url = 'https://www.lanzoui.com' + soup.find('iframe')['src']
    return download_url

def main():
    result = crawl('iabrphqxs0j')
    print(result)
    
    download_url = get_html('https://wwe.lanzoui.com/iabrphqxs0j')
    print(download_url)
    
    try:
        html = requests.get(download_url, headers=g_headers, timeout=g_timeout)
    except Exception:
        print('wrong')
        return

    # 将编码格式改为utf-8
    html.encoding='utf-8'
    soup = bs4.BeautifulSoup(html.text, "html.parser")

    print(soup)

    content = soup.select('div#go.load > a')
    for link in soup.find_all('span'): 
        #print(link.get('href'))
        print(link)
    print(content)
    if content:
        print(content)

if __name__ == '__main__':
    main()



"""
还是被上了一课。。。
中间的网址无法静态获取。。。

<!-- file pages1 -->
<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<script type="text/javascript" src="/includes/js/jquery.js"></script>
<link href="/img/tf.css" rel="stylesheet" type="text/css">
</head>
<body>
<div id="outime">地址超时，请刷新</div>

<div class="load" id="go">
文件加载中...
</div>
<script type="text/javascript">
		var ajaxdata = '?ctdf';
		var postdown = 'AWdaZAg5V2ZWX1doAjIAPFY_aV2MEblBhBjYGOQJuBj5SdAAjWjoOawRkBGEGZlViBGpTZVcxAzAGNw_c_c';
		$.ajax({
			type : 'post',
			url : '/ajaxm.php',
			data : { 'action':'downprocess','signs':ajaxdata,'sign':postdown,'ves':1,'websign':'','websignkey':'PTdR' },
			//data : { 'action':'downprocess','sign':sign,'sign':sign,'ves':1},
			dataType : 'json',
			success:function(msg){
				var date = msg;
				if(date.zt == '1'){
										$("#go").html("<a href="+date.dom+"/file/"+ date.url +" target=_blank rel=noreferrer><span class=txt>电信下载</span><span class='txt txtc'>联通下载</span><span class=txt>普通下载</span></a>");
					setTimeout('$("#outime").css("display","block");',1800000);
									}else{
					$("#go").html("网页超时，请刷新");
				};
				
			},
			error:function(){
				$("#go").html("获取失败，请刷新");
			}
	
		});
</script>
</body>
"""







