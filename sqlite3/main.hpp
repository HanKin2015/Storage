/*

实现一个配置数据共享存储模块

要求：
1.对外支持多线程/多进程的数据安全读写访问；
2.对外提供数据更改通知机制，能及时让外部获取数据的变化。
3.数据存储要求支持加密安全，加密算法要求可扩展；

说明：
1.配置数据存储在SQLite里，模块读取出来后转换为JSON格式给业务模块使用

*/

#include <iostream>
#include <map>
#include <set>
#include "sqlite3.h"

using namespace std;


//增加配置数据
int AddConfData(const char *conf_data);

//删除配置数据
int DelConfData(const char *conf_data);

//修改配置数据
int ChgConfData(const char *conf_data);

//查询配置数据
int QuyConfData(const char *conf_data);

//加密算法一：

//加密算法二：

//通知修改机制

//打开sqlite数据库
int OpenSqlite();

//关闭sqlite数据库
int CloseSqlite();