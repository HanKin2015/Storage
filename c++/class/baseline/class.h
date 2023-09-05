#include <iostream>
#include <vector>
#include <string>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>

class UsbDevicePort
{
public:
    UsbDevicePort(std::string ports_describe, uint32_t _channel_id);
    ~UsbDevicePort(){}
    bool match_ports_path(std::vector<int>& dev_ports);
    int get_channel_id(){return _channel_id;}
    std::string getPortsString(){return _ports_str;}

private:
    uint32_t _channel_id;
    std::vector<int> _ports_vec;
    std::string _ports_str;
};

class UsbManager {
private:
    std::vector<UsbDevicePort> ports_array;
    
public:
    /*
     * 实例化一个管理对象
     */
    static UsbManager* instance()
    {
        static UsbManager instance_;
        return &instance_;
    }

    void init_default_port_paths();
};
