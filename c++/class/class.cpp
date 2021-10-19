#include "class.h"

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();

    for(int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if(pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

UsbDevicePort::UsbDevicePort(std::string ports_describe, uint32_t channel_id)
{
    std::vector<std::string> bus_ports = split(ports_describe, "-");
    assert(bus_ports.size() == 2);
    int bus_num = strtol(bus_ports[0].c_str(), NULL, 10);
    _ports_vec.push_back(bus_num);

    std::vector<std::string> ports = split(bus_ports[1], ".");
    assert(ports.size() > 0);
    for(int i = 0; i < ports.size(); i++) {
        int prot_num = strtol(ports[i].c_str(), NULL, 10);
        _ports_vec.push_back(prot_num);
    }

    _channel_id = channel_id;
    _ports_str= ports_describe;
}

void UsbManager::init_default_port_paths()
{
     //初始化usb端口，格式为 bus-port1.port2.port3...
    //=====front=====
    //[1-1.4.1][1-1.1]
    //=====back======
    //[1-1.4.4][1-1.3]
    //[1-1.4.3][1-1.2]
    ports_array.push_back(UsbDevicePort("1-1.1", 0));
    ports_array.push_back(UsbDevicePort("1-1.2", 1));
    ports_array.push_back(UsbDevicePort("1-1.3", 2));
    ports_array.push_back(UsbDevicePort("1-1.4.1", 3));
    ports_array.push_back(UsbDevicePort("1-1.4.3", 4));
    ports_array.push_back(UsbDevicePort("1-1.4.4", 5));

    for (int i = 0; i < ports_array.size(); i++) {
        printf("%s %d\n", ports_array[i].getPortsString().data(),
                              ports_array[i].get_channel_id());
    }
    return;
}

int main(int argc, char *argv[])
{
    UsbManager::instance()->init_default_port_paths();
    return 0;
}