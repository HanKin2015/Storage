#include "main.hpp"




int main()
{
	sqlite3 *sql = NULL; // 一个打开的数据库实例
    const char * path = "./hejian.db";//某个sql文件的路径

    // 根据文件路径打开数据库连接。如果数据库不存在，则创建。
    // 数据库文件的路径必须以C字符串传入。
    int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

    if (result == SQLITE_OK) {
        std::clog << "打开数据库连接成功";
    }
    else {
        std::clog << "打开数据库连接失败";
    }
	cout << "hello何健" << endl;
	return 0;
}