// Cpp程序将cout重定向到文件
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    fstream file;
    file.open("cout.txt", ios::out);
    string line;

    // cout的备份流缓冲区
    streambuf* stream_buffer_cout = cout.rdbuf();
    streambuf* stream_buffer_cin = cin.rdbuf();

    // 获取文件的streambuffer
    streambuf* stream_buffer_file = file.rdbuf();

    // 将cout重定向到文件
    cout.rdbuf(stream_buffer_file);

    cout << "Linux迷www.linuxmi.com这行写入文件" << endl;

    // 将cout重定向回屏幕
    cout.rdbuf(stream_buffer_cout);
    cout << "www.linuxmi.com这一行被写入屏幕" << endl;

    file.close();
    return 0;
}
