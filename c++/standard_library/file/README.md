# 文件相关函数

## 1、statfs函数
参考：https://www.python100.com/html/3XX0A8HF7S73.html

### 1-1、简介
statfs指的是获取文件系统状态的系统调用函数，通过该函数可以获取文件系统的状态信息。
```
#include <sys/statfs.h>
int statfs(const char *path, struct statfs *buf);
```

该函数接受两个参数：
- path：需要获取状态信息的文件系统挂载点路径。
- buf：返回存储状态信息的缓冲区地址，该参数为结构体类型指针。
该函数返回值为0表示执行成功，否则执行失败。

### 1-2、statfs结构体
在使用statfs函数时，需要传递一个结构体指针作为参数，用于保存获取到的文件系统状态信息。该结构体的定义如下：
```
struct statfs {
  long f_type;      /* 文件系统类型 */
  long f_bsize;     /* 文件系统块大小 */
  long f_blocks;    /* 文件系统总块数 */
  long f_bfree;     /* 文件系统空闲块数 */
  long f_bavail;    /* 文件系统非特权空闲块数 */
  long f_files;     /* 文件系统总文件数 */
  long f_ffree;     /* 文件系统空闲文件数 */
  fsid_t f_fsid;    /* 文件系统ID */
};
```

### 1-3、statfs问题
在使用statfs函数时，需要注意以下问题：
- 文件系统类型的判断要使用<sys/mount.h>中定义的宏。
- inux系统中，每个进程最多可以有128个文件描述符，因此需要注意文件描述符的数量。
- 通过realloc函数来扩展动态分配的缓冲区大小。

### 1-4、statfs与statvfs的区别
statfs函数和statvfs函数都是用来获取文件系统状态的信息，它们的函数签名一样，但是返回的结构体类型不同。statfs返回的是struct statfs结构体，而statvfs返回的是struct statvfs结构体。

两者的主要区别在于结构体中的一些字段定义不同，例如：f_blocks和f_bfree在statfs结构体中的类型为long，而在statvfs结构体中的类型为fsblkcnt_t（文件系统块数类型）；f_bsize在statfs结构体中的类型为long，而在statvfs结构体中的类型为fsblksize_t（文件系统块大小类型）。

因为两个函数返回的信息有所不同，所以在使用时需要根据需求选择合适的函数。

## 2、statvfs函数
参考：https://www.python100.com/html/3L1O5B9OB16E.html

### 2-1、简介
statvfs是一个用来检查文件系统状态的函数，其定义如下:
```
int statvfs(const char *path, struct statvfs *buf);
```
其中，path表示要查询的文件系统路径，buf是一个结构体指针，用于存储查询结果。

statvfs函数会返回0表示成功，非零表示错误。如果调用出错，则可以通过errno来查找出错原因。

### 2-2、常用的结构体类型
在使用statvfs函数时，需要用到statvfs结构体类型。这个结构体的定义如下:
```
struct statvfs {
    unsigned long  f_bsize;    /* 文件系统块大小 */
    unsigned long  f_frsize;   /* 文件系统中第一个块的大小 */
    fsblkcnt_t     f_blocks;   /* 文件系统中总块数 */
    fsblkcnt_t     f_bfree;    /* 文件系统中空闲块数 */
    fsblkcnt_t     f_bavail;   /* 文件系统中非超级用户可获取的块数 */
    fsfilcnt_t     f_files;    /* 文件系统中总文件数 */
    fsfilcnt_t     f_ffree;    /* 文件系统中空闲文件数 */
    fsfilcnt_t     f_favail;   /* 文件系统中非超级用户可获取的文件数 */
    unsigned long  f_fsid;     /* 文件系统标识ID */
    unsigned long  f_flag;     /* mount flags */
    unsigned long  f_namemax;  /* 文件名的最大长度 */
};
```

