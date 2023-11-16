# 目录相关函数
参考：https://blog.csdn.net/Dustinthewine/article/details/126694378
打开、读取、关闭一个普通文件可以使用 open()、read()、close()，而对于目录来说，可以使用 opendir()、readdir()和 closedir()来打开、读取以及关闭目录。

## 一、打开目录 opendir
opendir()函数用于打开一个目录，并返回指向该目录的句柄，供后续操作使用。opendir 是一个 C 库函数，opendir()函数原型如下所示：
```
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
```
函数参数和返回值含义如下：
name：指定需要打开的目录路径名，可以是绝对路径，也可以是相对路径。
返回值：成功将返回指向该目录的句柄，一个 DIR 指针（其实质是一个结构体指针），其作用类似于open函数返回的文件描述符fd，后续对该目录的操作需要使用该DIR指针变量；若调用失败，则返回NULL。

## 二、读取目录 readdir
readdir()用于读取目录，获取目录下所有文件的名称以及对应 inode 号。这里给大家介绍的 readdir()是一个 C 库函数（事实上 Linux 系统还提供了一个 readdir 系统调用），其函数原型如下所示：
```
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```
首先，使用该函数需要包含头文件<dirent.h>。
函数参数和返回值含义如下：
dirp：目录句柄 DIR 指针。
返回值：返回一个指向 struct dirent 结构体的指针，该结构体表示 dirp 指向的目录流中的下一个目录条目。在到达目录流的末尾或发生错误时，它返回 NULL。

Tips：“流”是从自然界中抽象出来的一种概念，有点类似于自然界当中的水流，在文件操作中，文件内容数据类似池塘中存储的水，N 个字节数据被读取出来或将 N 个字节数据写入到文件中，这些数据就构成了字节流。
“流”这个概念是动态的，而不是静态的。编程当中提到这个概念，一般都是与 I/O 相关，所以也经常叫做 I/O 流；但对于目录这种特殊文件来说，这里将目录块中存储的数据称为目录流，存储了一个一个的目录项（目录条目）。

struct dirent 结构体内容如下所示：
```
struct dirent {
 ino_t d_ino; /* inode 编号 */
 off_t d_off; /* not an offset; see NOTES */
 unsigned short d_reclen; /* length of this record */
 unsigned char d_type; /* type of file; not supported by all filesystem types */
 char d_name[256]; /* 文件名 */
};
```
对于 struct dirent 结构体，我们只需要关注 d_ino 和 d_name 两个字段即可，分别记录了文件的 inode 编号和文件名，其余字段并不是所有系统都支持，所以也不再给大家介绍，这些字段一般也不会使用到。

每调用一次 readdir()，就会从 drip 所指向的目录流中读取下一条目录项（目录条目），并返回 struct dirent结构体指针，指向经静态分配而得的 struct dirent 类型结构，每次调用 readdir()都会覆盖该结构。一旦遇到目录结尾或是出错，readdir()将返回 NULL，针对后一种情况，还会设置 errno 以示具体错误。

那如何区别究竟是到了目录末尾还是出错了呢，可通过如下代码进行判断：
```
error = 0;
direntp = readdir(dirp);

if (NULL == direntp) 
{
	if (0 != error) 
	{
		/* 出现了错误 */
	} 
	else 
	{
		/* 已经到了目录末尾 */
	} 
}
```
使用 readdir()返回时并未对文件名进行排序，而是按照文件在目录中出现的天然次序（这取决于文件系统向目录添加文件时所遵循的次序，及其在删除文件后对目录列表中空隙的填补方式）。

当使用 opendir()打开目录时，目录流将指向了目录列表的头部（0），使用 readdir()读取一条目录条目之后，目录流将会向后移动、指向下一个目录条目。这其实跟 open()类似，当使用 open()打开文件的时候，文件位置偏移量默认指向了文件头部，当使用 read()或 write()进行读写时，文件偏移量会自动向后移动。

## 三、rewinddir 函数
rewinddir()是 C 库函数，可将目录流重置为目录起点，以便对 readdir()的下一次调用将从目录列表中的第一个文件开始。

rewinddir 函数原型如下所示：
```
#include <sys/types.h>
#include <dirent.h>

void rewinddir(DIR *dirp);
```
首先，使用该函数需要包含头文件<dirent.h>。
函数参数和返回值含义如下：
dirp：目录句柄。
返回值：无返回值。

## 四、关闭目录 closedir 函数
closedir()函数用于关闭处于打开状态的目录，同时释放它所使用的资源，其函数原型如下所示：
```
#include <sys/types.h>
#include <dirent.h>

int closedir(DIR *dirp);
```
首先，使用该函数需要包含头文件<sys/types.h>和<dirent.h>。
函数参数和返回值含义如下：
dirp：目录句柄。
返回值：成功返回 0；失败将返回-1，并设置 errno。

## 五、readlink软链接函数
参考：https://www.python100.com/html/109671.html

readlink函数是unix/linux系统中的一个函数，用于读取符号链接的值。
```
int readlink(const char *path, char *buf, size_t bufsiz);
```
函数参数：
- path：符号链接的路径
- buf：用于接收符号链接值的缓冲区
- bufsiz：缓冲区buf的大小

readlink函数返回的是符号链接的值的长度，如果读取失败，则返回-1，errno表示错误类型。

### 读取程序自身路径
在程序中，我们可以使用readlink函数读取程序自身的路径。
代码见：readlink_example.c
程序解释：程序中使用readlink函数读取/proc/self/exe符号链接的值，即程序自身的路径。

### 判断文件是否为符号链接
在程序中，我们可以使用lstat函数和S_ISLNK宏判断文件是否为符号链接，如果是，则可以使用readlink函数读取符号链接值。

程序解释：程序使用lstat函数获取文件属性并判断是否为符号链接，如果是，则使用readlink函数读取符号链接值，并打印出来，如果不是，程序直接打印不是符号链接。