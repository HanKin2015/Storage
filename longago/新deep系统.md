http://blog.sina.com.cn/s/blog_605f5b4f0101847z.html
修改/etc/hosts之后正常情况应该是保存之后立即生效的，但是有时不是。使用uname-a 可以查看hostname是多少，就可以知道是否修改生效了。如果没有
这时的策略有：
1） 重启机器
2） 重启服务
     Ubuntu: $sudo/etc/init.d/networking restart
     Gentoo: /etc/init.d/net.eth0restart
3）使用hostname命令
       hostname 定义的主机名

hostname与/etc/hosts的关系

很多人一提到更改hostname首先就想到修改/etc/hosts文件，认为hostname的配置文件就是/etc/hosts。其实不是的。

hosts文件的作用相当如DNS，提供IP地址到hostname的对应。早期的互联网计算机少，单机hosts文件里足够存放所有联网计算机。不过随着互联网的发展，这就远远不够了。于是就出现了分布式的DNS系统。由DNS服务器来提供类似的IP地址到域名的对应。具体可以manhosts。

Linux系统在向DNS服务器发出域名解析请求之前会查询/etc/hosts文件，如果里面有相应的记录，就会使用hosts里面的记录。/etc/hosts文件通常里面包含这一条记录

127.0.0.1   localhost.localdomain  localhost
hosts文件格式是一行一条记录，分别是IP地址 hostnamealiases，三者用空白字符分隔，aliases可选。


scp从服务器下载文件到本地或从本地上传文件到服务器
原创 2016年09月19日 15:40:07 12453
  1、从服务器下载文件
  scp username@servername:/remote_path/filename ~/local_destination
  
   2、上传本地文件到服务器
  scp ~/local_path/local_filename username@servername:/remote_path  
    
  3、从服务器下载整个目录
      scp -r username@servername:/remote_path/remote_dir/ ~/local_destination
  
  4、上传目录到服务器
      scp  -r ~/local_dir username@servername:/remote_path/remote_dir




      http://www.jb51.net/LINUXjishu/43356.html


      关于gcc: error trying to exec 'cc1plus': execvp: 没有那个文件或目录
原创 2016年10月30日 12:36:11 1065
gcc: error trying to exec ‘cc1plus’: execvp: 没有那个文件或目录

解决问题：

apt-get install build-essential
apt-get install g++
1
2
原来我装的是gcc或许是g++与其并不兼容 
重新安装了g++