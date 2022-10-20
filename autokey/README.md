软件下载地址：https://www.autohotkey.com/


#  转义
对于一些特殊符号输出，如#、！等。需要用大括号{}转义，且一个大括号只能转义一个特殊符号。如下：
```
!9::
Send test@hankin{!}{!}{!}{:}{:}{enter}
return
```

# 注意
修改脚本后，需要右键托盘，选择“Reload This Script”重新加载。

# 开机启动
在任务计划中增加开机启动。

