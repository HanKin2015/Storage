// Cpp����cout�ض����ļ�
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    fstream file;
    file.open("cout.txt", ios::out);
    string line;

    // cout�ı�����������
    streambuf* stream_buffer_cout = cout.rdbuf();
    streambuf* stream_buffer_cin = cin.rdbuf();

    // ��ȡ�ļ���streambuffer
    streambuf* stream_buffer_file = file.rdbuf();

    // ��cout�ض����ļ�
    cout.rdbuf(stream_buffer_file);

    cout << "Linux��www.linuxmi.com����д���ļ�" << endl;

    // ��cout�ض������Ļ
    cout.rdbuf(stream_buffer_cout);
    cout << "www.linuxmi.com��һ�б�д����Ļ" << endl;

    file.close();
    return 0;
}
