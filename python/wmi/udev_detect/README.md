# usb设备拔插监控工具

### 编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/udev_detect.ico -w -F src/udev_detect_tray.py`

## 20230216
- 工具主体完成，功能基本实现

## 20230223
- 增加新设备接入打印设备信息

## 下一步计划
- 增加弹框
- 集成exe文件
- 放置在托盘上

## 艰难的实现qq或者微信的托盘消息
https://blog.csdn.net/qq_45662588/article/details/121012593
上面博文缺少一个ui_CNoticeList.h文件，导致无法执行，最终还是在github上面搜索相关变量找到另外一个项目。
https://github.com/nodbrag/QTStudyDemo/tree/8911d43083ff00ac44b4e3d6a41dbeee8cce2704/Qt/18QQTooTip/QQTooTip

其实阅读博文的文章也应该能实现，最终在c++转python过程中还是比较顺畅的，qt几乎无修改迁移。

## QQ ToolTip
在开发时发现窗口默认高度很重要，目前只能通过QWidget.height()获取真实高度，太小了会使QLabel的高度不固定的变大变小。

## QSystemTrayIcon::showMessage: Wrong icon size (32x32), please add standard one: 40x40
win10系统有这个报错，也可能是python版本高些的问题，3.9.13。win7系统使用3.7.4无这个报错。

## 又出现314MB的情况
这个导致怎么进行排查呢，通过代码并没有看出来。
果然是resource_convert_to_pyfile.py文件搞的鬼，单独将这个文件生成exe文件发现有311MB。

如果只去掉numpy也会有104MB，还是选择这个文件不进行import吧。

## 未读消息提示框过大
发现去掉鼠标光标在提示框内显示后，鼠标进入不了。增加一个判断变量已解决。