// mock_network_interface.h
#ifndef MOCK_NETWORK_INTERFACE_H
#define MOCK_NETWORK_INTERFACE_H

#include <gmock/gmock.h>
#include "network_interface.h"

class MockNetworkInterface : public NetworkInterface {
public:
    MOCK_METHOD(bool, send_data, (const std::string& data), (override));
};

#endif // MOCK_NETWORK_INTERFACE_H