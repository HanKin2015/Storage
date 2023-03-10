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

## QQ ToolTip
在开发时发现窗口默认高度很重要，目前只能通过QWidget.height()获取真实高度，太小了会使QLabel的高度不固定的变大变小。