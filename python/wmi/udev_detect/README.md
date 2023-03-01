# usb设备拔插监控工具

### 编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i img/udev_detect.ico -w -F src/upan_auto_copy.py`

## 20230216
- 工具主体完成，功能基本实现

## 20230223
- 增加新设备接入打印设备信息

## 下一步计划
- 增加弹框
- 集成exe文件
- 放置在托盘上

