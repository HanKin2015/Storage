# 很奇怪
aclocal
autoconf
automake --add-missing
./configure

需要创建一个src文件夹，将源代码放入其中，否则执行automake命令怎么都不会成功，报错：
```
[root@ubuntu0006:~/cmake/autoconf_automake/example1] #automake --add-missing
Makefile.am: error: required file './NEWS' not found
Makefile.am: error: required file './README' not found
Makefile.am: error: required file './AUTHORS' not found
Makefile.am: error: required file './ChangeLog' not found
```

修改目录结构后，执行成功：
```
[root@ubuntu0006:~/cmake/autoconf_automake/example1/src] #make
gcc -DPACKAGE_NAME=\"project\" -DPACKAGE_TARNAME=\"project\" -DPACKAGE_VERSION=\"1.0\" -DPACKAGE_STRING=\"project\ 1.0\" -DPACKAGE_BUGREPORT=\"you@example.com\" -DPACKAGE_URL=\"\" -DPACKAGE=\"project\" -DVERSION=\"1.0\" -I.     -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.c
mv -f .deps/main.Tpo .deps/main.Po
gcc -DPACKAGE_NAME=\"project\" -DPACKAGE_TARNAME=\"project\" -DPACKAGE_VERSION=\"1.0\" -DPACKAGE_STRING=\"project\ 1.0\" -DPACKAGE_BUGREPORT=\"you@example.com\" -DPACKAGE_URL=\"\" -DPACKAGE=\"project\" -DVERSION=\"1.0\" -I.     -g -O2 -MT log.o -MD -MP -MF .deps/log.Tpo -c -o log.o log.c
mv -f .deps/log.Tpo .deps/log.Po
gcc  -g -O2   -o myprogram main.o log.o
[root@ubuntu0006:~/cmake/autoconf_automake/example1/src] #./myprogram
hello automake, autoconf
```

创建必需的文件： 在软件包的根目录中创建 NEWS、README、AUTHORS 和 ChangeLog 文件。这些文件可以包含相应的信息，例如软件包的变更历史、使用说明、作者列表等。