<div align="center">
<img height=150 src="https://github.com/HanKin2015/Storage/blob/master/python/udev/upan_auto_copy/img/icon.jpg" />
</div>
<p align="center">
<span >中文</span>
<span> | </span>
<a href="README_EN.md">English</a>
</p>
<p align="center"><span>跨平台的U盘自动拷贝</span></p>



<div align="center">

[![Download Counts](https://img.shields.io/github/downloads/HanKin2015/Storage/total?style=flat)](https://github.com/HanKin2015/Storage/releases)
[![Stars Count](https://img.shields.io/github/stars/HanKin2015/Storage?style=flat)](https://github.com/HanKin2015/Storage/stargazers) [![Forks Count](https://img.shields.io/github/forks/HanKin2015/Storage.svg?style=flat)](https://github.com/HanKin2015/Storage/network/members)
[![LICENSE](https://img.shields.io/badge/license-gpl-green?style=flat)](https://github.com/HanKin2015/Storage/blob/master/LICENSE)

[![Windows Support](https://img.shields.io/badge/Windows-0078D6?style=flat&logo=windows&logoColor=white)](https://github.com/HanKin2015/Storage/releases)
[![Windows Support](https://img.shields.io/badge/MACOS-adb8c5?style=flat&logo=macos&logoColor=white)](https://github.com/HanKin2015/Storage/releases)
[![Linux Support](https://img.shields.io/badge/linux-1793D1?style=flat&logo=linux&logoColor=white)](https://github.com/HanKin2015/Storage/releases)
</div>

## 介绍
![Demo](screenshot/upan_auto_copy_v1.0.0.gif)

upan_auto_copy是一款跨平台的**U盘自动拷贝**稳定性测试脚本工具。

## ✨特点
- 使用简单，自带中文分词、拼音、补全
- 毫秒级搜索响应
- 低CPU、内存资源占用
- 轻量安装包
- 简单大方

## 待改进
- 目前只拷贝单个文件，可扩展拷贝文件夹
- 是否可考虑简单大方的UI

## 编译打包
- 搭建python3开发环境 (https://m.runoob.com/python3/python3-install.html)
- 运行 `python upan_auto_copy.py`
- 运行 `python upan_auto_copy.py -u D`
- 打包 `pyinstaller.exe --version-file=doc/file_version_info.txt -i doc/dog.ico -F upan_auto_copy.py`


## 下载
点击 [release page](https://github.com/HanKin2015/Storage/releases).


## 架构
![arch](doc/arch.jpg)


## 感谢
- 菜鸟教程 https://m.runoob.com/python3/
- python3 https://www.python.org/


## LICENSE
[GPL](https://github.com/HanKin2015/Storage/blob/master/python/udev/upan_auto_copy/LICENSE)