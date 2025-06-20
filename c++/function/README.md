# 函数相关模块

## 1、形参没有名称
在函数声明中：
无论是C还是在C++，都可以省略形式参数名。
但是，通常都不建议省略形式参数名。

在函数定义中：
1. 当需要使用形式参数的时候，显然，必须给形式参数命名。
2. 当不需要使用形式参数的时候，C与C++有微小差异：
    - C不能省略形式参数名， 即使不使用。
    - C++可以省略形式参数名，如果不使用。并且在C++中，如果给不使用的形式参数命名，可能会得到一个警告。
demo见：

## 2、
- 条件变量
- 回调函数
- 消息缓存
三者可以互相切换。

需求：连接服务端后，服务端会立即下发hello数据包，但是这时候没有客户端可以这个数据，只有在设备映射的时候才会创建客户端，这时候才能接收这个数据。
- 将这个下发hello数据包的流程阻塞，当设备映射的时候然后通知条件变量激活
- 也相当于缓存
- 将hello数据包缓存，当设备映射的时候判断是否存在消息，如果有再下发给客户端

需求：查询和更新本地配置信息，对外提供一个公共接口，如果把配置的键暴露不够隐秘。
因此改为指针传入，指针只能是回调函数（因为查看配置的程序是守护进程，需要等待它返回查询的配置信息），不能是配置信息指针，因为查询的子进程，可能这个配置信息指针的值被替换了。回调函数指针则不会那么轻易的被替换。
```
CTRL_DECL
int ctrl_device_automap_conf(ctrl_handle handle,
                             const char *user_id,
                             void *conf,
                             void (*conf_cb)(void *conf));
```
当conf为nullptr时，则是查询，配置信息会输出给回调函数。当conf不为nullptr时，则是更新。

## 等价替换
三种方式：
```
std::function<void(void *priv, uint8_t *data, int32_t length)> m_write_cb;

void (*m_write_cb)(void *priv, uint8_t *data, int32_t length);

typedef void (*WriteCb)(void *priv, uint8_t *data, int32_t length);
WriteCb m_write_cb;
```

那是否能隐式转换呢？
```
#include <iostream>
#include <functional>
#include <cstdio>
#include <cstring>

// 不支持name变量传入
void test1(void (*cb)(void *conf))
{
    int num = 12345;
    cb(&num);
    return;
}

// 支持name变量传入
void test2(std::function<void(void *)> cb)
{
    int num = 12345;
    cb(&num);
    return;
}

int main()
{
    std::string name = "hejian";
    test2([name](void *conf) {
        int *ptr = (int *)conf;
        printf("name %s: %d\n", name.c_str(), *ptr);
    });
    return 0;
}
```





