// 确认fprintf函数是否能写入空格句子，注意需要换行符
#include <iostream>
#include <string>
#include <cstdio>

int main()
{
    std::string msg = "fudhahfaueruioq dasjdkldw djklsa";
    FILE *fp = fopen("/home/hejian.log", "w");
    if (fp) {
        fprintf(fp, "%s", msg.c_str());
        fclose(fp);
        fp = NULL;
    }
    return 0;
}
