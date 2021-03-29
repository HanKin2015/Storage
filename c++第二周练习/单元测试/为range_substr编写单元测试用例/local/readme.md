# 单元测试考题

## 待测函数介绍

### 1. 函数参考实现

```cpp
const char *range_substr(const char *pb, const char *pe, const char *sub)
{
    const char *cp = NULL;

    assert(pb && sub);
    assert(!pe || pe >= pb);

    if (!pe)
        return strstr(pb, sub);
    if (!*sub)
        return pb;

    cp = pb;
    while (cp < pe) {
        const char *s1 = cp;
        const char *s2 = sub;

        while (s1 < pe && *s2 && *s1 == *s2) {
            s1++;
            s2++;
        }

        if (!*s2)
            return cp;

        cp++;
    }
    return NULL;
}

```

### 2. 函数说明


函数range_substr从内存区间[pb, pe)搜寻子串sub。

如果找到子串sub，返回匹配块的起始地址。
如果没找到，则返回NULL。

如果pe为NULL，表示pb指向一个'\0'结束的字符串，否则表示从pb开始，pe结束（不包括pe本身）的一个内存区间，即：[pb, pe)。区间内的'\0'字符当成普通字符处理。


## 测试案例编写要求

上述range_substr函数实现是一种参考实现，也存在一些其它的实现方式，这些实现方式有些是正确的，有些可能是错误的，或者存在缺陷。

本题要求为range_substr设计单元测试案例，尽可能测出各种range_substr实现当中可能存在的缺陷。

## 单测的本地调试

下载本单测试题的本地包，解压，在local目录下，运行make命令，即可编译运行。

单测案例代码写在template.c文件中，这也是提交到OnlineJudge平台的代码内容。

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
    UT_ASSERT(buf + 2 == range_substr(buf, buf + 4, "ll"));
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
