# 问题现象
在安装deb文件后，发现软链接链接出现异常。
```
正常情况下：
lrwxrwxrwx  1 root root         15 4月  28 10:12 libtest.so -> libzhj.so.1.0.0*
lrwxrwxrwx  1 root root         15 4月  27 21:24 libzhj.so.1 -> libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:14 libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:23 libzhj.so.1.0.0.bak*
-rwxr-xr-x  1 root root       8888 4月  27 21:25 libzhj.so.1.0.0.z*

然后安装deb文件后：
lrwxrwxrwx  1 root root         17 4月  28 10:42 libtest.so -> libzhj.so.1.0.0.z*
lrwxrwxrwx  1 root root         15 4月  27 21:24 libzhj.so.1 -> libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:14 libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:23 libzhj.so.1.0.0.bak*
-rwxr-xr-x  1 root root       8888 4月  27 21:25 libzhj.so.1.0.0.z*

期望的结果是：
lrwxrwxrwx  1 root root         30 4月  28 10:43 libtest.so -> /usr/local/lib/libzhj.so.1.0.0*
lrwxrwxrwx  1 root root         15 4月  27 21:24 libzhj.so.1 -> libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:14 libzhj.so.1.0.0*
-rwxr-xr-x  1 root root       8888 4月  27 21:23 libzhj.so.1.0.0.bak*
-rwxr-xr-x  1 root root       8888 4月  27 21:25 libzhj.so.1.0.0.z*
```

# 排查过程
使用dpkg -e解压deb包DEBIAN信息，然后在里面找到软件安装脚本，查看软件执行的步骤，发现并没有太多问题，唯一可疑点是ldconfig命令。
deb包见：D:\Github\Storage\linux\神奇的软链接\test

# ldconfig命令
ldconfig命令是Linux系统中的一个工具，用于更新共享库缓存。共享库缓存是一个索引，它包含了系统中所有共享库的信息，包括库的名称、版本和路径等。当系统需要加载共享库时，它会首先查找共享库缓存，如果找到了对应的库，则直接加载，否则会报错。

ldconfig命令的作用是将新安装的共享库添加到共享库缓存中，或者更新已有的共享库缓存。它会扫描指定的目录，查找其中的共享库，并将它们的信息添加到共享库缓存中。ldconfig命令还可以通过指定参数来控制共享库缓存的更新方式，例如指定-r参数可以将共享库缓存的路径修改为指定的路径。

ldconfig命令的常用选项包括：
```
-v：显示详细的输出信息。
-n：不更新缓存文件，仅打印出将要更新的信息。
-p：打印出当前系统中所有已缓存的共享库信息。
-X：清除缓存文件中的所有共享库信息。
```

在执行 ldconfig 命令时，如果同一个文件有两种不同的命名方式，那么 ldconfig 可能会将软链接的路径更新为其中一种命名方式。这是因为 ldconfig 会根据共享库的 SONAME（Shared Object Name）来确定共享库的版本和名称，而不是根据文件名或软链接名来确定。

共享库的 SONAME 是在编译共享库时指定的，它通常包含共享库的主版本号和次版本号，例如 libfoo.so.1。当一个程序链接到共享库时，它会使用 SONAME 来确定共享库的版本和名称，而不是使用文件名或软链接名。

因此，如果同一个共享库有两种不同的命名方式，ldconfig 可能会将软链接的路径更新为其中一种命名方式，以便程序能够正确地链接到共享库。这种情况下，软链接的路径可能会发生变化，但是共享库的版本和名称不会发生变化。

如果您需要使用软链接来链接共享库，建议使用共享库的 SONAME 来命名软链接，以避免 ldconfig 更新软链接的路径。另外，如果您需要更改共享库的命名方式，建议先卸载旧版本的共享库，再安装新版本的共享库，以避免出现命名冲突的问题。

# 获取SONAME
要获取共享库的 SONAME，可以使用以下命令：
```
readelf -a <共享库文件名> | grep SONAME
```

其中，readelf 命令用于显示 ELF（Executable and Linkable Format）文件的信息，-a 选项表示显示所有信息，grep SONAME 命令用于过滤出包含 SONAME 的行。

例如，要获取 libfoo.so.1 的 SONAME，可以使用以下命令：
```
readelf -a libfoo.so.1 | grep SONAME
```

输出结果应该类似于：
```
0x000000000000000e (SONAME)             Library soname: [libfoo.so.1]
```

其中，Library soname 后面的字符串就是共享库的 SONAME。

注意，如果共享库没有指定 SONAME，那么上述命令将不会输出任何结果。在编译共享库时，可以使用 -soname 选项来指定共享库的 SONAME，例如：
```
gcc -shared -Wl,-soname,libfoo.so.1 -o libfoo.so.1.0.0 foo.o bar.o
```

这个命令将编译 foo.o 和 bar.o 两个目标文件，并生成名为 libfoo.so.1.0.0 的共享库文件，并将其 SONAME 设置为 libfoo.so.1。

# ldconfig命令工作流程
ldconfig 在更新缓存文件时会按照一定的顺序搜索共享库，并选择其中一个命名方式记录在缓存文件中。在搜索共享库时，ldconfig 会按照以下顺序搜索：

- 在 /etc/ld.so.conf 文件中指定的目录中搜索共享库。
- 在 /etc/ld.so.conf.d 目录中的配置文件中指定的目录中搜索共享库。
- 在默认的共享库搜索路径中搜索共享库，包括 /lib、/usr/lib、/usr/local/lib 等目录。

在搜索共享库时，ldconfig 会按照字母顺序搜索目录中的文件，并选择其中一个命名方式记录在缓存文件中。如果目录中有多个命名方式相同的共享库，ldconfig 会选择其中一个共享库记录在缓存文件中。

因此，如果同一个共享库有两个不同的命名方式，ldconfig 会选择其中一个命名方式记录在缓存文件中，具体选择哪个命名方式取决于搜索顺序和文件名的字母顺序。如果您需要使用软链接来链接共享库，建议使用共享库的 SONAME 来命名软链接，以避免 ldconfig 更新软链接的路径。

个人见解：
按照字母排序进行建立软链接，会慢慢替换之前链接好的软链接，因此最终会选择名字的ASCII值最大的那一个。

# 发现ldconfig命令没有管理我自己编译的so文件
如果您的共享库文件已经被正确安装到 ldconfig 管理的目录中，并且 ldconfig 命令也已经更新了共享库缓存，但是 ldconfig -p 命令仍然没有搜索到您的共享库文件，可能是因为您的共享库文件没有正确命名。在 ldconfig 管理的目录中，共享库文件的命名方式应该为 lib<name>.so.<version>，其中 <name> 是共享库的名称，<version> 是共享库的版本号。例如，如果您的共享库名称为 libfoo.so，版本号为 1.0.0，那么共享库文件应该命名为 libfoo.so.1.0.0。

发现需要严格按照此命名规则。

# 最后的问题
俺直接执行test/DEBIAN/postinst文件存在问题，即会链接到不期望的文件上面，直接执行ldconfig也是。
但是但是如果我打包成deb包后按照却是正常的。。。

百思不得其解。

# 重大发现
发现/usr/local/lib中的软链接并不是手动创建的，而是ldconfig命令执行后自己创建的。
如当前目录只有自己编译的文件libzhj.so.1.0.0，执行ldconfig后会创建一个软链接libtest.so -> libzhj.so.1.0.0。
因为文件libzhj.so.1.0.的SONAME是libtest.so。


