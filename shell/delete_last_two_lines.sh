# 1、文件的MD5值是根据文件内容来计算的
因此md5值跟系统无关，跟md5sum命令版本无关。
```
[root@ubuntu0006:~/cmake] #vi x         # 写入123
[root@ubuntu0006:~/cmake] #md5sum x
ba1f2511fc30423bdbb183fe33f3dd0f  x
[root@ubuntu0006:~/cmake] #vi y         # 写入123
[root@ubuntu0006:~/cmake] #md5sum y
ba1f2511fc30423bdbb183fe33f3dd0f  y

更换系统
[admin@HANKIN tmp]$ vi k                # 写入123
[admin@HANKIN tmp]$ md5sum k
ba1f2511fc30423bdbb183fe33f3dd0f  k
```

# 2、删除文件末尾两行
起因xml文件末尾倒数第二行是来进行区分文件的唯一标识checksum，末尾一行是空行，因此需要删除这两行。
```
能自我编辑
sed -i '$d' file.txt
sed -i '$d' file.txt

只能借助其他文件进行转存
head -n -2 file.txt > temp.txt
mv temp.txt file.txt

head -n -2 x > l && md5sum l
head -n -2 x | md5sum
```


