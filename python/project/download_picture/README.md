# 爬虫图片

## 1、目标网站
https://ss.netnr.com/wallpaper#6

## 2、selenium新版本使用方式发生变化
D:\Github\Storage\python\project\crawler\test_chromedriver.py
https://www.cnblogs.com/lxmtx/p/17945756

## 3、曾经的方式已过时
目标网站为了防止爬虫，更改了网页设计。
参考：https://blog.csdn.net/HSX501560987/article/details/108660043
亲测有效：D:\Github\Storage\python\project\download_picture\ss_baseline.py
通过F12键，然后通过鼠标下滑在NetWork中看见对应的URL。

## 4、完整爬虫
通过多个网络链接发现，其中有个地方以18的数量增加，代表着18张图片的链接。
```
https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D0%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time

https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D18%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time

https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D36%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time

测试随便写成20也能行的通
https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D20%26count%3D18%26from%3D360chrome%26a%3DgetAppsByOrder%26order%3Dcreate_time

正在下载第17张壁纸=>>>网络游戏 魔兽争霸 兽人 部落......
正在下载第18张壁纸=>>>落日余晖 麦田 乡村......
正在下载壁纸数据json: https://cors.zme.ink/http%3A%2F%2Fwallpaper.apc.360.cn%2Findex.php%3Fc%3DWallPaper%26start%3D162%26count%3D18%26from%3D360chrome
%26a%3DgetAppsByOrder%26order%3Dcreate_time
正在下载第1张壁纸=>>>豹 雷电 闪电......
正在下载第2张壁纸=>>>奇幻梦境 城堡 欧洲建筑......
正在下载第3张壁纸=>>>公路......
正在下载第4张壁纸=>>>色彩 抽象 旋涡......
正在下载第5张壁纸=>>>野生动物 狮子......
正在下载第6张壁纸=>>>自然风光 湖泊 小木屋......
正在下载第7张壁纸=>>>一拳超人 琦玉老师......
正在下载第8张壁纸=>>>清纯 橘子 桔子 可爱......
正在下载第9张壁纸=>>>旅游胜地......
正在下载第10张壁纸=>>>静物写真......
正在下载第11张壁纸=>>>2019年7月......
正在下载第12张壁纸=>>>野生动物 狐狸......
正在下载第13张壁纸=>>>地球......
正在下载第14张壁纸=>>>城市夜景......
正在下载第15张壁纸=>>>卡通 线性图标......
正在下载第16张壁纸=>>>自然风光......
正在下载第17张壁纸=>>>落日余晖 盐湖 晚霞......
正在下载第18张壁纸=>>>动漫 泳装 比基尼......
process spend 589.021 s.
```

## 5、关于图片临时显示
使用PTL库的show函数调用本地图片查看器，需要手动关闭。
可以通过以非阻塞的方式使用，并调用pause函数暂停而不是sleep函数。


