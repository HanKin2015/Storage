#include "common.h"

int ReadFile(const char* file_path, vector<char*> &data)
{
    ifstream in_file(file_path);

    if (!in_file.is_open()) {
        cout << "open file failed!" << endl;
        return -1;
    }

    string line;
    while (getline(in_file, line)) {
        size_t len = line.size();
        char* temp = new char[len + 1];
        //temp = const_cast<char *>(line.c_str());
        strncpy(temp, line.c_str(), len + 1);
        data.push_back(temp);
    }

    in_file.close();
    cout << "read data line count = " << data.size() << endl;
    return 0;
}

/*
 * ios::in  只读
 * ios::out 只写
 * ios::app 从文件末尾开始写，防止丢失文件中原来就有的内容
*/
int WriteFile(const char* file_path, vector<char*> data)
{
    ofstream out_file(file_path, ios::out);

    if (!out_file.is_open()) {
        cout << "open file failed!" << endl;
        return -1;
    }

    for (vector<char*>::iterator it = data.begin(); it != data.end(); it++) {
        out_file << (*it);
        out_file << endl;
    }

    out_file.close();
    cout << "write data line count = " << data.size() << endl;
    return 0;
}
