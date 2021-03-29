# 单元测试考题

## 待测函数介绍

### 1. 函数参考实现
```cpp

/**
 *  升序数组
 */
typedef struct arr_t {
    int *vals;      //存放整数的数组
    int capacity;   //vals的容量
    int cnt;        //vals中存放的整数个数
} arr_t;
/**
 *  在升序数组arr中插入一个整数val，插入后数据保持升序
 */
int insert(arr_t *arr, int val)
{
    int i;
    assert(arr);
    if (arr->cnt >= arr->capacity)
        return -1;
    for (i = 0; i < arr->cnt; ++i) {
        if (arr->vals[i] >= val)
            break;
    }
    if (i < arr->cnt) {
        memmove(&arr->vals[i + 1], &arr->vals[i], sizeof(int) * (arr->cnt - i));
    }
    arr->vals[i] = val;
    ++arr->cnt; 
    return 0;
}
```

### 2. 函数说明

* 前置条件：

 arr是个有效的升序数组，满足：

```cpp
assert(arr);
assert(arr->cnt <= arr->capacity);
assert(arr->cnt == 0 || arr->vals);
for (i = 0; i < arr->cnt - 1; ++i) {
    assert(arr->vals[i] <= arr->vals[i + 1]);
}
```

* 调用者必须保证调用insert前，arr的合法性。

* 插入val后，升序数组arr增加一个新元素val，但依然保持升序

* 不满足插入条件时，返回-1，否则完成插入，并返回0

## 测试案例编写要求

上述insert函数实现是一种参考实现，也存在一些其它的实现方式，这些实现方式有些是正确的，有些可能是错误的，或者存在缺陷。

本题要求为insert设计单元测试案例，尽可能测出各种insert实现当中可能存在的缺陷。

## 单测框架接口说明

本题采用的测试框架是个精简的C单元测试框架，和gtest的使用方式比较相似。

完成题目要求，需要用到的主要是5个宏：

### 1. UT_CASE

UT_CASE定义一个测试案例，每个测试案例运行过程中，如果出现错误(比如UT_ASSERT和UT_EXPECT发现不满足要求)，则终止本案例后续代码的运行。但不影响其他案例的执行。

定义一个单元测试案例：

```cpp
UT_CASE(case_name)
{
    UT_EXPECT(0, insert(&s_arr, 3));
    UT_EXPECT(4, s_arr.cnt);
    UT_EXPECT(3, s_arr.vals[2]);
}
```

### 2. UT_SETUP

UT_SETUP用于测试环境的构建。每当一个单元测试案例开始前，都会自动调用UT_SETUP中的代码，构建本案例运行过程中需要使用到的资源。

例如：

```cpp
UT_SETUP()
{
    memset(s_buf, 0, sizeof(s_buf));
    s_arr.vals = s_buf;
    s_arr.capacity = 1024;
    s_arr.cnt = 0;
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
UT_ASSERT(insert(arr, 2) >= 0);
```

### 5. UT_EXPECT

UT_EXPECT用于测试结果的检查。

UT_EXPECT(expect, actual): 检查表达式actual的执行结果是否等于expect，如果不等于expect,则报告错误；

例如：

```cpp
UT_EXPECT(0, insert(arr, 1));
```
