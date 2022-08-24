# 1、获取代理IP地址
get_proxy_ip.py
通过爬虫技术爬取网上代理IP

# 2、将图片转换成bs64编码，然后再通过编码转换成图片
icon2py.py
生成icon.py文件

转换成图片
```
from icon import icon_img
logo_file_path = './logo.ico'
def _generate_icon_(self):
	'''将二进制图标转换为图片文件
	'''
	tmp = open(logo_file_path, "wb+")
	tmp.write(base64.b64decode(icon_img))
	tmp.close()
```

# 3、ftp服务器操作
upload_ftp.py
download_ftp.py

# 4、可视化窗口tkinter
visualized_window.py
使用tkinter库编写

# 5、文件读写
write_read_file.py

# 6、引入自定义的库方法
```
# 增加libary库的搜索路径
sys.path.append('../../../libary/')
# 导入自定义的Entry库
from entrywithplaceholder import EntryWithPlaceholder
```

