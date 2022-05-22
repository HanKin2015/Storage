参考：https://blog.csdn.net/a849992683/article/details/90030326

在真实项目中，往往要进行图片的传输和视频的传输，但因为用户上传的图片和视频所占用的大小问题而导致占用服务器的空间多，并且用户访问这些图片的时候因为图片或视频太大而长时间加载，所以要对用户上传的视频和图片进行压缩，减少服务器的占用空间和加载时间。


使用了是ffmpeg对视频进行压缩，这个是一个非常好用的工具，Linux和windows都有,在Linux中可以使用apt install ffmpeg进行安装(我用的是Ubuntu的系统,所以使用apt进行安装,如果用的是Centos的用对应的yum进行安装就行了)

ffmpeg -i 1.mp4 -r 10 -pix_fmt yuv420p -vcodec libx264 -preset veryslow -profile:v baseline  -crf 23 -acodec aac -b:a 32k -strict -5 147fss.mp4

-i 输入的视频文件
-r 每一秒的帧数,一秒10帧大概就是人眼的速度
-pix_fmt 设置视频颜色空间 yuv420p网络传输用的颜色空间 ffmpeg -pix_fmts可以查看有哪些颜色空间选择
-vcodec 软件编码器，libx264通用稳定
-preset 编码机预设 编码机预设越高占用CPU越大 有十个参数可选 ultrafast superfast veryfast(录制视频选用) faster fast medium(默认) slow slower veryslow(压制视频时一般选用) pacebo
-profile:v 压缩比的配置 越往左边压缩的越厉害，体积越小 baseline(实时通信领域一般选用，画面损失越大) Extended Main(流媒体选用) High(超清视频) High 10 High 4:2:2 High 4:4:4(Predictive)
-level:v 对编码机的规范和限制针对不通的使用场景来操作,也就是不同分辨率设置不同的值(这个我没有设置，因为这个要根据不同的分辨率进行设置的,具体要去官方文档查看)
-crf 码率控制模式 用于对画面有要求，对文件大小无关紧要的场景 0-51都可以选择 0为无损 一般设置18 - 28之间 大于28画面损失严重
-acodec 设置音频编码器


左边为未压缩过的原视频文件，右边为压缩过的视频文件，可见帧宽度与帧高度都没发生过改变，只是修改了数据速率，总比特率等的这些信息，源文件帧速率为每秒12帧，现在压缩成了每秒10帧，人眼是没办法分别出12帧与10帧的区别的，我测试过原视频和压缩后的视频观看上是没有却别的，声轨也听不出。