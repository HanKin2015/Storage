#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;

// 转换大小写
void transfer_case(string &str)
{
    for (int i = 0; i < str.size(); i++) {
       str[i] = tolower(str[i]);    // 把大写全部转为小写
    }
    return;
}

// 判断数据是否有效
bool is_valid(string vid, string pid)
{
    // 1、长度
    if (vid.size() != 7 || pid.size() != 6) return false;

    // 2、异常字符
    if (vid[0] != '0' || pid[0] != '0') return false;
    if (vid[1] != 'x' || pid[1] != 'x') return false; 
    
    for (int i = 2; i < 6; i++) {
        if (((vid[i] >= '0' && vid[i] <= '9') || (vid[i] >= 'a' && vid[i] <= 'f')) &&
            ((pid[i] >= '0' && pid[i] <= '9') || (pid[i] >= 'a' && pid[i] <= 'f'))) {
                //return true;
        } else {
            return false;
        }
    }
    return true;
}

// 去掉前后的空格换行符
static char* trim(char* str, const char* delim)
{
    char* p1 = str;
    char* p2 = NULL;
    int len;

    assert(str && str[0] != 0);

    len = strlen(p1);
    p2 = p1 + len - 1;

    while (strchr(delim, *p1)) {
        p1++;
    }
    if (p1 > p2) {
        return NULL;
    }
    if (*p1 == 0) {
        return p1;
    }

    while (strchr(delim, *p2)) {
        p2--;
    }
    if (p2 < str) {
        return NULL;
    }
    *(p2+1) = 0;
    return p1;
}

// 去重
void unrepeat(const char *data_raw_path, const char *data_in_path)
{
    FILE *fp_r = fopen(data_raw_path, "r");
    if (fp_r == NULL) {
        printf("open data_raw_path failed\n");
        return;
    }
    
    set<string> data;
    int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp_r)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("raw_data: %s(%zu)\n", line, strlen(line));
               
        trim(line, " \r\n\t");
        //printf("data: %s(%zu)\n", line, strlen(line));
        //printf("\n");
        
        data.insert(line);
        count++;
    }
    
    printf("原有%d条数据, 去重之后有%zu条数据.\n", count, data.size());
    
    FILE *fp_w = fopen(data_in_path, "w");
    if (fp_w == NULL) {
        printf("open data_in_path failed\n");
        return;
    }
    for (string meta : data) {
        fprintf(fp_w, "%s\n", meta.data());
    }
    
    free(line);
    fclose(fp_r);
    fclose(fp_w);
}

// 处理函数
void deal_vpid(const char *data_in_path, const char *data_out_path)
{
    string vid, pid;
    int line_num = 0;
    
    ifstream ifs(data_in_path);
    if (ifs.fail()) {
        printf("open data_in_path failed\n");
        return;
    }
    ofstream ofs(data_out_path);
    if (ofs.fail()) {
        printf("open data_out_path failed\n");
        return;
    }
    
    istringstream iss;
    ostringstream oss;
    string line;
    int valid_count = 0;

    while (getline(ifs, line)) {
        line_num++;
        
        iss.str(line);
        iss >> vid >> pid;

        transfer_case(vid);
        transfer_case(pid);
        
        if (!is_valid(vid, pid)) {
            printf("line number: %d, %s %s\n", line_num, vid.data(), pid.data());
            continue;
        }
        
        valid_count++;
        oss << vid << pid << endl;
        
        iss.clear();
        iss.str("");
    }
    
    ofs << oss.str();
    printf("原有%d条数据, 去非法数据之后有%d条数据.\n", line_num, valid_count);
    
    ifs.close();
    ofs.close();
    return;
}

int main()
{
    const char *data_raw_path = "data/raw_udev_net_driver_vpid.txt";
    const char *data_in_path  = "data/udev_net_driver_vpid.txt";
    const char *data_out_path = "udev_net_driver_vpid.txt";
    
    //freopen(data_in_path,  "r", stdin);
    //freopen(data_out_path, "w", stdout);
    
    unrepeat(data_raw_path, data_in_path);
    
    deal_vpid(data_in_path, data_out_path);
    return 0;
}