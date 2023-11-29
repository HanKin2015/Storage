# 命令步骤详解
automake 是一个用于生成 Makefile 的工具，它与 autoconf 一起使用，用于简化软件包的构建过程。以下是使用 automake 工具的一般步骤：

1、创建 Makefile.am 文件： 在软件包的每个子目录中创建一个名为 Makefile.am 的文件，该文件描述了该目录中源文件的组织结构和构建规则。

2、编辑 Makefile.am 文件： 在 Makefile.am 文件中，使用 automake 的语法来定义源文件、目标文件、编译选项等构建规则。这包括诸如 bin_PROGRAMS（可执行程序）、lib_LTLIBRARIES（共享库）和 include_HEADERS（头文件）等变量的设置。

3、创建 configure.ac 文件： 如果还没有 configure.ac 文件，需要创建一个并使用 autoconf 来生成 configure 脚本。

4、运行 aclocal： 在命令行中，使用 aclocal 命令来收集 autoconf 所需的宏定义文件。例如：
```
aclocal
```

5、运行 automake： 在命令行中，使用 automake 命令来处理 Makefile.am 文件并生成 Makefile.in 文件。例如：
```
automake --add-missing
```

6、运行 autoconf： 如果 configure.ac 文件发生了变化，需要再次运行 autoconf 来更新 configure 脚本。

7、运行 configure 脚本： 使用生成的 configure 脚本来配置软件包以适应特定的系统。

8、构建软件包： 一旦配置完成，可以使用标准的构建工具（如 make）来构建软件包。

automake 的主要目的是简化 Makefile 的编写过程，使得软件包的构建规则更易于维护和移植。

简洁：
```
aclocal
autoconf
automake --add-missing
./configure
```

## 存在小bug
```
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #ll
总用量 20
drwxr-xr-x 3 root root 4096 11月 27 15:32 ./
drwxr-xr-x 4 root root 4096 11月 27 15:31 ../
-rw-r--r-- 1 root root  129 11月 27 15:31 configure.ac
-rw-r--r-- 1 root root 1595 11月 27 15:32 README.md
drwxr-xr-x 2 root root 4096 11月 27 15:33 src/
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #aclocal
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #ll
总用量 68
drwxr-xr-x 4 root root  4096 11月 27 15:40 ./
drwxr-xr-x 4 root root  4096 11月 27 15:31 ../
-rw-r--r-- 1 root root 42141 11月 27 15:40 aclocal.m4
drwxr-xr-x 2 root root  4096 11月 27 15:40 autom4te.cache/
-rw-r--r-- 1 root root   129 11月 27 15:31 configure.ac
-rw-r--r-- 1 root root  1595 11月 27 15:32 README.md
drwxr-xr-x 2 root root  4096 11月 27 15:33 src/
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #autoconf
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #ll
总用量 208
drwxr-xr-x 4 root root   4096 11月 27 15:40 ./
drwxr-xr-x 4 root root   4096 11月 27 15:31 ../
-rw-r--r-- 1 root root  42141 11月 27 15:40 aclocal.m4
drwxr-xr-x 2 root root   4096 11月 27 15:40 autom4te.cache/
-rwxr-xr-x 1 root root 141513 11月 27 15:40 configure*
-rw-r--r-- 1 root root    129 11月 27 15:31 configure.ac
-rw-r--r-- 1 root root   1595 11月 27 15:32 README.md
drwxr-xr-x 2 root root   4096 11月 27 15:33 src/
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #automake --add-missing
configure.ac:3: installing './compile'
configure.ac:2: installing './install-sh'
configure.ac:2: installing './missing'
src/Makefile.am: installing './depcomp'
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #ll
总用量 208
drwxr-xr-x 4 root root   4096 11月 27 15:41 ./
drwxr-xr-x 4 root root   4096 11月 27 15:31 ../
-rw-r--r-- 1 root root  42141 11月 27 15:40 aclocal.m4
drwxr-xr-x 2 root root   4096 11月 27 15:41 autom4te.cache/
lrwxrwxrwx 1 root root     32 11月 27 15:41 compile -> /usr/share/automake-1.15/compile*
-rwxr-xr-x 1 root root 141513 11月 27 15:40 configure*
-rw-r--r-- 1 root root    129 11月 27 15:31 configure.ac
lrwxrwxrwx 1 root root     32 11月 27 15:41 depcomp -> /usr/share/automake-1.15/depcomp*
lrwxrwxrwx 1 root root     35 11月 27 15:41 install-sh -> /usr/share/automake-1.15/install-sh*
lrwxrwxrwx 1 root root     32 11月 27 15:41 missing -> /usr/share/automake-1.15/missing*
-rw-r--r-- 1 root root   1595 11月 27 15:32 README.md
drwxr-xr-x 2 root root   4096 11月 27 15:41 src/
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #cp src/Makefile.in .
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #./configure
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking for gcc... gcc
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables...
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether gcc accepts -g... yes
checking for gcc option to accept ISO C89... none needed
checking whether gcc understands -c and -o together... yes
checking for style of include used by make... GNU
checking dependency style of gcc... gcc3
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: creating src/Makefile
config.status: executing depfiles commands
[root@ubuntu0006:~/cmake/autoconf_automake/example2] #cd src/
[root@ubuntu0006:~/cmake/autoconf_automake/example2/src] #make
gcc -DPACKAGE_NAME=\"project\" -DPACKAGE_TARNAME=\"project\" -DPACKAGE_VERSION=\"1.0\" -DPACKAGE_STRING=\"project\ 1.0\" -DPACKAGE_BUGREPORT=\"you@example.com\" -DPACKAGE_URL=\"\" -DPACKAGE=\"project\" -DVERSION=\"1.0\" -I.     -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.c
mv -f .deps/main.Tpo .deps/main.Po
gcc  -g -O2   -o myprogram main.o
[root@ubuntu0006:~/cmake/autoconf_automake/example2/src] #./myprogram
hello world!
```