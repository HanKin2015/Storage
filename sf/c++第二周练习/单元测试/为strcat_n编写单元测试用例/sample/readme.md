# 单元测试考题

## 待测函数介绍

### 1. 函数参考实现

```cpp
int strcat_n(char *dst, size_t size, const char *src)
{
    assert(dst && src);
    assert((dst < src && (dst + size) < src)
        || (dst > src && (src + size) < dst));

    size_t dst_len = strlen(dst);
    if (!size || dst_len >= size - 1) {
        return -1;
    }

    //由于不同的C库strncat处理空间不足时有不同的行为，这里算出长度后memcpy
    size_t src_len = strlen(src);
    size_t rest = size - dst_len;

    if (rest > src_len) {
        memcpy(dst + dst_len, src, src_len);
        dst[dst_len + src_len] = '\0';
        return 0;
    } else {
        memcpy(dst + dst_len, src, rest - 1);
        dst[size - 1] = '\0';
        return -1;
    }
}
```

### 2. 函数说明

函数strcat_n把字符串src拷贝到dst的字符串末尾，把两个字符串连接到一起。

size是内存块dst总共能容纳的字符个数（包括'\0'）。当dst空间不足时，将切断拷贝到dst
中的字符串，保证连接后的字符串末尾有'\0'结束，并且返回-1。

当dst的空间足够容纳src时，复制src到dst末尾，连成一个完整字符串，并返回0

## 测试案例编写要求

上述strcat_n函数实现是一种参考实现，也存在一些其它的实现方式，这些实现方式有些是正确的，有些可能是错误的，或者存在缺陷。

本题要求为strcat_n设计单元测试案例，尽可能测出各种strcat_n实现当中可能存在的缺陷。

## 单测框架接口说明

本题采用的测试框架是个精简的C单元测试框架，和gtest的使用方式比较相似。

完成题目要求，需要用到的主要是5个宏：

### 1. UT_CASE

UT_CASE定义一个测试案例，每个测试案例运行过程中，如果出现错误(比如UT_ASSERT和UT_EXPECT发现不满足要求)，则终止本案例后续代码的运行。但不影响其他案例的执行。

定义一个单元测试案例：

```cpp
UT_CASE(case_name)
{
    char buf[20] = "hello";
    UT_EXPECT(0, strcat_n(buf, sizeof(buf), " world"));
    UT_EXPECT(11, strlen(buf));
    UT_ASSERT(strcmp(buf, "hello world") == 0);
}
```

### 2. UT_SETUP

UT_SETUP用于测试环境的构建。每当一个单元测试案例开始前，都会自动调用UT_SETUP中的代码，构建本案例运行过程中需要使用到的资源。

例如：

```cpp
UT_SETUP()
{
    memset(s_buf, 0, sizeof(s_buf));
}

```

### 3. UT_TEARDOWN

UT_TEARDOWN用于测试环境的清理。每当一个单元测试案例结束，都会自动调用UT_TEARDOWN中的代码，清理本案例运行过程(包括UT_SETUP运行过程)中分配的资源。

例如：

```cpp
UT_TEARDOWN()
{
}
```

### 4. UT_ASSERT

UT_ASSERT用于测试结果的检查。

UT_ASSERT(x): 检查表达式x值是否为真，如果不为真，这报告错误；

例如：

```cpp
UT_ASSERT(strcmp(buf, "hello world") == 0);
```

### 5. UT_EXPECT

UT_EXPECT用于测试结果的检查。

UT_EXPECT(expect, actual): 检查表达式actual的执行结果是否等于expect，如果不等于expect,则报告错误；

例如：

```cpp
UT_EXPECT(0, strcat_n(buf, sizeof(buf), "hello"));
```
