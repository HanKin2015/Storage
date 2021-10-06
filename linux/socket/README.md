# socket通信


忘性真的大，20210113已经忘记的差不多了。


下一步计划：
使用json进行通信，将消息规范化。

使用使用脚本可以进行通信。


使用shell脚本反复跑窗口化
while true
do
    echo {\"method\":\"windows_maximsize\"} | socat - unix-connect:/run/hankin/client/socket.[1536366701440]
    sleep  5
done

这个153xxx修改为具体/run/hankin/client/socke路径socket的值

