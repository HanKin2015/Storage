// tests/test_network_client.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "network_client.h"
#include "mock_network_interface.h"

using ::testing::Return;

TEST(NetworkClientTest, SendDataSuccess) {
    MockNetworkInterface mockNetwork;
    NetworkClient client(&mockNetwork);

    EXPECT_CALL(mockNetwork, send_data("Hello"))
        .WillOnce(Return(true));

    EXPECT_TRUE(client.send("Hello"));
}

TEST(NetworkClientTest, SendDataFailure) {
    MockNetworkInterface mockNetwork;
    NetworkClient client(&mockNetwork);

    EXPECT_CALL(mockNetwork, send_data("Hello"))
        .WillOnce(Return(false));

    EXPECT_FALSE(client.send("Hello"));
}