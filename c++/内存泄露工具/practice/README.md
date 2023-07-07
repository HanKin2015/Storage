## 1、背景
在项目中使用了0长数组的结构体，但是不清楚如何正确是否内存，刚好拿来使用泄露工具进行校验。
代码见：D:\Github\Storage\c++\内存泄露工具\practice\demo.cpp

直接编译运行没有任何问题。

## 2、使用AddressSanitizer工具
详细见：D:\Github\GitBook\gitbook\C++\address_sanitizer.md

```
[root@ubuntu0006:~/kernel] #g++ k.cpp  -fsanitize=address
[root@ubuntu0006:~/kernel] #./a.out
bytes_per_transfer = 4096
- bytes_per_transfer = 4096
bytes_per_transfer = 4096
- bytes_per_transfer = 4096
bytes_per_transfer = 4096
- bytes_per_transfer = 4096
list size = 3
bytes_per_transfer = 4096
count 3
hejian 1 4096
hejian data_len 20, quirk 2 param_count 1
param endpoint 82
hejian data_len 20, quirk 2 param_count 1
param endpoint 82
hejian data_len 20, quirk 2 param_count 1
param endpoint 82

=================================================================
==2503==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 60 byte(s) in 3 object(s) allocated from:
    #0 0x7f672aab0602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x401a4a in main (/root/kernel/a.out+0x401a4a)
    #2 0x7f672a0d683f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x7f672aab079a in __interceptor_calloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x9879a)
    #1 0x401861 in main (/root/kernel/a.out+0x401861)
    #2 0x7f672a0d683f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

Indirect leak of 108 byte(s) in 3 object(s) allocated from:
    #0 0x7f672aab0602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x401416 in main (/root/kernel/a.out+0x401416)
    #2 0x7f672a0d683f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

SUMMARY: AddressSanitizer: 192 byte(s) leaked in 7 allocation(s).
```
看不出具体什么地方泄露，只晓得存在泄露问题。
但是能大概给出了首先有3个对象没有是否，然后是1个对象没有是否，最后还有3个对象。

修改后的代码见：D:\Github\Storage\c++\内存泄露工具\practice\demo_perfect.cpp






