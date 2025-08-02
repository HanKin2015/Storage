// network_interface.h
#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

class NetworkInterface {
public:
    virtual ~NetworkInterface() = default;
    virtual bool send_data(const std::string& data) = 0;
};

#endif // NETWORK_INTERFACE_H