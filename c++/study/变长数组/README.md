# 1、结构体长度计算
```
struct bulk_cache_list_param {
    uint32_t endpoint;
    uint8_t no_transfers;
    uint32_t bytes_per_transfer;
};
struct usb_redir_extend_bulk_cache_packet {
    struct bulk_cache_list_param *param;
    uint32_t quirk;
    uint8_t param_count;
};

sizeof(struct usb_redir_extend_bulk_cache_packet) = 16
```
结构体中包含了指针类型的成员变量，指针类型的大小在不同的系统中可能会有所不同，但通常是4个字节或8个字节。当前系统是8个字节。
因此只需要看`struct bulk_cache_list_param *`指针的长度，无需关心结构体本身的长度，由于结构体对齐，则：
8
4 1
= 16

```
struct bulk_cache_list_param {
    uint32_t endpoint;
    uint8_t no_transfers;
    uint32_t bytes_per_transfer;
};
struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    struct bulk_cache_list_param *param;
    uint8_t param_count;
};

sizeof(struct usb_redir_extend_bulk_cache_packet) = 24
```
由于结构体对齐：
4
8
1
= 24

# 2、取消结构体对齐
在C语言中，结构体对齐是由编译器自动完成的，目的是为了优化内存访问速度和对齐要求。如果您想取消结构体对齐，可以使用编译器提供的特定选项或指令。

在GCC编译器中，可以使用#pragma pack(n)指令来取消结构体对齐，其中n表示对齐字节数。例如，如果您想取消对齐，可以使用#pragma pack(1)指令。

在Visual C++编译器中，可以使用#pragma pack(push,1)和#pragma pack(pop)指令来取消结构体对齐。这些指令将当前对齐设置推入堆栈，并将对齐设置为1字节，然后在完成后将对齐设置还原为之前的值。

需要注意的是，取消结构体对齐可能会影响程序的性能和可移植性，因此应该谨慎使用。

只需要在main函数之前加一行#pragma pack(1)即可。

第1节的两种结构体长度将会都是13字节，直接全部加起来即可。

# 3、结构体的0长数组及使用
详解：https://blog.csdn.net/psr1999/article/details/129043655

结构体中的0长数组是指数组长度为0的数组，它的定义方式为在数组声明时不指定数组长度，例如：
```
struct example {
    int arr[0];
};
```

