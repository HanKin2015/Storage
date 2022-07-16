#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

// 从流中提取数据，支持 >> 操作
void study_istringstream()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    std::string file_path = "in2.txt";
 
    ifstream fp;
    fp.open(file_path.c_str());
 
    std::string str_line, str_split;
    std::istringstream iss;
    int index = 1;
    while (getline(fp, str_line)) {
        cout << "index: " << index++ << endl;
        iss.str(str_line);          //将strLine中的字符串存入字符串流中
        string str = iss.str();     //可以通过str()将字符流转换为字符串
        cout << str << endl;
        while (iss >> str_split) {  //以空格为界，分离字符串
            cout << str_split << endl;
        }
        cout << endl;
        
        // 不做清理会有问题
        iss.clear();
        iss.str("");
    }
/*
index: 1
i am a boy,
i
am
a
boy,

index: 2
and i like basketball.


index: 1
i am a boy,
i
am
a
boy,

index: 2
and i like basketball.
and
i
like
basketball.
*/
}

// 把其他类型的数据写入流(往流中写入数据)，支持<<操作
void study_ostringstream()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    std::ostringstream ostr("abd cd");
    cout << ostr.str() << endl;

    ostr.put('5');
    cout << ostr.str() << endl;

    ostr.put('4');
    cout << ostr.str() << endl;

    ostr.put('n');  //put()对单个字符有效，若出现多个，以最后一个位准
    ostr.put('b');
    cout << ostr.str() << endl;

    ostr << "1234444";
    std::string str3 = ostr.str();
    cout << ostr.str() << endl;
}

// 是对istringstream和ostringstream类的综合，支持<<, >>操作符，可以进行字符串到其它类型的快速转换
void study_stringstream()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    /*整型变字符串*/
    int n = 10;
    std::string str;
    std::stringstream ss;
    ss << n;
    ss >> str;
    cout << str << endl;

    //多次使用stringstream，要先清空下，否则下面输出10   
    ss.clear();
    ss.str("");

    /*char* 变 string*/
    char cs[10] = "hello";
    ss << cs;
    ss >> str;
    cout << str << endl;
    
    str = "11.11";
    double num;
    
    //多次使用stringstream，要先清空下 
    ss.clear();
    ss.str("");
    
    ss << str;
    ss >> num;
    cout << num << endl;
    
    //多次使用stringstream，要先清空下 
    ss.clear();
    ss.str("");
    
    ss << str;
    ss >> cs;
    cout << cs << endl;
}

void add_pre_zero()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    std::stringstream ss;
    std::string state_str, pid_str, vid_str,bus_port_str;

    int pid = 1234, vid = 6789, bus = 3, port = 15;
    std::string state    = "ok";
    std::string signal   = "usb_device_info";
    std::string dev_name = "hejian";

    ss.str("");
    ss << std::hex << std::setw(4) << std::setfill('0') << vid;
    vid_str = ss.str();
    ss.str("");
    ss << std::hex << std::setw(4) << std::setfill('0') << pid;
    pid_str = ss.str();

    ss.str("");
    ss << bus << "_" << port;
    bus_port_str = ss.str();

    ss.str("");
    ss << state;
    state_str = ss.str();
    
    // json 数据填充
    std::string usbDeviceMsg = "{\"signal\":\"" + signal + "\",\"bus_port\":\"" + bus_port_str +"\",\"name\":\""
        + dev_name + "\",\"vid\":\"" + vid_str + "\",\"pid\":\"" + pid_str + "\",\"state\":" + state_str + "}\n";
    printf("usb device:%s", usbDeviceMsg.c_str());
}

// 失败了想输出科学计数法
void deal_decimal()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    ostringstream oss;
    double num = 123456;
    oss.precision(5);
    oss << num;
    
    cout << oss.str() << endl;
}

int main()
{
    study_istringstream();
    study_ostringstream();
    study_stringstream();
    // 由于stringstream构造函数会特别消耗内存，如果你要在程序中用同一个流，反复读写大量的数据，将会造成大量的内存消耗，因些这时候，需要适时地清除一下缓冲 (用 stream.str("") )。
    add_pre_zero();
    deal_decimal();
    return 0;
}