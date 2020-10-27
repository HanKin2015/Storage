#include "common.h"

void test_file_opt()
{
    const char* in_file_path = "./in.txt";
    const char* out_file_path = "./out.txt";
    vector<char*> data;
    ReadFile(in_file_path, data);
    cout << data.size() << endl;
    for (vector<char*>::iterator it = data.begin(); it != data.end(); it++) {
        cout << (*it) << endl;
    }
    return;
}

int main(int argc, char* argv[])
{
    test_file_opt();
    return 0;
}
