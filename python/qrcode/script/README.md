# 1、bat脚本的制作
编译的exe文件过大，足有318MB，因此想法是通过执行python命令直接运行py脚本来进行二维码解析。
从Anaconda Prompt中来看，属性目标获取执行命令。

# 2、使用vbs脚本隐藏cmd窗口
使用bat脚本会有cmd窗口弹出，但是研究只用vbs脚本，发现无法设置anaconda环境变量，因此想到使用vbs脚本调用bat脚本规避方案来解决。
https://blog.csdn.net/B11050729/article/details/131711612

# 3、二维码
企业微信离线能识别数字、字母、中文
微信只能在线识别，并且不能识别中文
使用小爱视觉离线只能识别数字、字母，不能识别中文
使用pyzbar离线能识别数字、字母、中文

但是部分二维码识别出来是一个网址，然后会自动跳转，这种只能联网在线使用。