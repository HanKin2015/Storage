# 1、qt+c语言打包成单个exe文件

## 1-1、图标说明
- 在程序中需要写成相对路径，但这样会存在调试程序时没有图标，需要拷贝文件到D:\Users\User\My Document\build-capture_hj-Desktop_Qt_5_14_2_MinGW_64_bit-Release文件夹中
- 打包的时候需要将图标拷贝到d:\test\文件夹中，否则打包的时候会提示报错
- 写成绝对路径打包时不会打包进文件中，它只会打包d:\test\文件夹下的东西

## 1-2、打包步骤
- 将现有的项目在QT Creater中用release方式编译成test.exe
- 将release中生成的.exe文件拷贝到新的空文件夹中，我在这里拷贝到了d:\test\test.exe中
- 在QT安装菜单中找到QT5.8 for DeskTop工具（Qt 5.14.2(MinGW 7.3.0 64-bit)），运行。即Dos窗口
- 输入命令:cd /d d:\test\，然后使用windeployqt工具命令:windeployqt test.exe
- 这里就得到了完全程序发布集合
- 下载QT程序打包工具Enigma Virtual Box（单机版虚拟文件打包工具(Enigma Virtual Box)9.50汉化去广告版.exe），安装完成后点击运行
- 主程序文件名称浏览选择exe文件，然后添加整个文件夹（添加文件夹递归），添加文件夹确定
- 在【Files Options】中选择勾选文件虚拟化，勾选压缩文件
- 点击process（打包）运行开始打包，成功后生成一个独立的.exe可执行程序（大约40秒）。

# 2、更新日志

## 20201016
- 打开关闭摄像头
- 拍照
- 保存图片

## 20230118
- 摄像头格式分辨率切换
- 添加状态栏显示
- 自动切换摄像头格式分辨率

## 20230209
- 图标
- 自动切换时摄像头异常处理
- 多个摄像头切换
- 添加菜单栏
- 解决软件窗口关闭后继续执行问题，重写退出事件
- 增加简易日志文件打印

## 20240516
未能生成dump文件，但是这个不重要，重要的是生成pdb文件了，能正常进行调试程序了。
https://blog.csdn.net/LiHong333/article/details/129798322
可能只需要下载cv2pdb即可。

MINGW能否和MSVC一样产生pdb文件。原因是编译器选择错误。
- 使用gflags.exe软件挂载capture_hj.exe程序，设置调试器为windbg
- 运行release版本程序
- windbg输入g命令继续运行
- 复现崩溃问题
- 复制capture_hj.exe文件，cv2pdb capture_hj.exe生成pdb文件
- 加载pdb文件进行调试，kb命令输入堆栈

# 3、未来期望
- 解决软件打开时的黑屏框
- 虽然实现了多个摄像头切换，但是后面的分辨率和格式并不是当前摄像头的参数
- 增加摄像头状态日志打印
- 修改白城次数变量类型为longlong
- 增加udp消息发送机制

# 4、参考
https://github.com/aeagean/QtCamera
https://blog.csdn.net/taw19960426/article/details/122277059