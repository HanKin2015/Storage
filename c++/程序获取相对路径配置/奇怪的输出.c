logcat 中没有冒号输出原始日志：
[Wed Jan  1 08:02:32 2020] ceca: tx len: 2 data: 40 8f
[Wed Jan  1 08:03:12 2020] ceca: tx len: 2 data: 40 8f
^C
130|console:/ # logcat | grep ceca
01-01 08:00:33.234     0     0 I kernel  : [   31.088759@3] ceca tx len: 2 data: 40 8f
01-01 08:00:33.400     0     0 I kernel  : [   31.254557@1] ceca tx len: 2 data: 40 8f

加了两个 hejian：
01-01 08:01:13.821     0     0 I kernel  :  [   72.677290@0] hejian ceca: tx hejian len: 10 data: 40 47 42 38 36 30 41 56 36 43
01-01 08:01:14.710     0     0 I kernel  :  [   73.566332@1] hejian ceca: tx hejian len: 2 data: 40 8f
^C
130|console:/ # dmesg | grep ceca
[   60.038262] hejian ceca: tx hejian len: 2 data: 40 8f
[   62.994247] hejian ceca: tx hejian len: 2 data: 40 8f

加了一个 hejian：
[   29.437372] ceca: tx hejian len: 2 data: 40 8f
[   29.878291] ceca: tx hejian len: 2 data: 40 8f
console:/ # ^C
130|console:/ # logcat | grep ceca
01-01 08:00:22.291     0     0 I kernel  : [   20.147358@2] ceca tx hejian len: 2 data: 40 8f
01-01 08:00:25.271     0     0 I kernel  : [   23.127327@3] ceca tx hejian len: 2 data: 40 8f
00 04

原因：**logcat 读取内核环形缓冲区的时候，对 kernel 日志行做了简单的文本预处理**，属于 Android logd 对内核日志的解析逻辑：
`logd` 在解析内核消息时，会做简单分隔，把类似 `tag: xxx` 的冒号替换成空格，用来拆分日志 TAG 和 message。

> 
> 只在 logcat 查看内核缓冲区日志才会出现；**dmesg 是直接读内核 ringbuffer 原始数据，不会修改文本，冒号保留**

不确认这个是不是真的？？