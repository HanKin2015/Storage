# -*- coding: utf-8 -*-
"""
Created on Sat Sep 19 20:01:57 2020

@author: Administrator
"""

import requests
def test():
    s=requests.session()
    headers={
        'Accept': 'application/json, text/javascript, */*; q=0.01',
        'Accept-Encoding':'gzip, deflate',
        'Accept-Language':'zh-CN,zh;q=0.9',
        'Connection':'keep-alive',
        'Content-Length':'21',
        'Cookie': 'XSRF-TOKEN=eyJpdiI6Iks0SnBGeXJUSEc0ODJnc2t2d1UwN2c9PSIsInZhbHVlIjoiZE8weTJFVklraWppWWU3TFZrXC9hVGx3a0FMcXFTckFOaTJcL3RiMldcL2F2T1VOb0xSRm1WR2JXRDZJb01CUytJSUd3eW5STW50Tko2TExIV25Ca3VqeGc9PSIsIm1hYyI6IjBkZTVmOTFmNWU0MDhiYzBlMzE5MWIyNjk1Njc3NTViOGMzZDc3MGM4NTI4N2I5YmViZWYyNDA3NmNjNzM3MjgifQ%3D%3D; laravel_session=eyJpdiI6IjlCZUJoc0JWZnBxbndIWTY0dStJZmc9PSIsInZhbHVlIjoiTklQbSt5Slg2MG5mU3JFa3RKK1hPdmUwTnBCclRjdmllSnFzOUpOQTJZbURSK3NmM1NzSjF6TDB4VkZzSGRFU1RWWnpKRzhpOTh5azdTdENMVjR4Z1E9PSIsIm1hYyI6IjMxZTM1MThmYjI0MjNjNTFiMDE0YmI3MmE5ZWVjMDAxNWE0MjBiOGU2MWU1OTZmNzAyYzE2OTdlOWJiOGQzYjIifQ%3D%3D',
        'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
        'Host':'www.cszjxx.net',
        'Origin':'http://www.cszjxx.net',
        'Referer':'http://www.cszjxx.net/floorinfo/202004160830',
        'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.102 Safari/537.36',
        'X-Requested-With':'XMLHttpRequest'
    }
    s.headers.update(headers)
    data={
        'ywzh':'KF2005220376',
        'n':'6',
    }
    url='http://www.cszjxx.net/getxx'
    req=s.post(url=url,data=data).text
    print(req.encode('gbk').decode('unicode_escape'))
 
test()