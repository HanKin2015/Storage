#include <net/if.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <sys/ioctl.h>
#include <net/if.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <net/if_arp.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_PHY_ADDR_LEN 8
#define PHY_ADDR_LEN 6

int get_ip_mac_address(uint32_t &ip_addr, uint8_t *phy_addr, int phy_addr_len)
{
    //ASSERT(NULL != phy_addr);

    int i;
    struct ifreq ifr;
    int sockfd, err;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, "eth0", sizeof(ifr.ifr_name) - 1);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        //LOG_ERROR("Open socket error, %d, %s", errno, strerror(errno));
        return -1;
    }

    err = ioctl(sockfd, SIOCGIFADDR, &ifr); // ip地址
    if (0 == err) {
        ip_addr = ((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr.s_addr;
    }
    else {
        //LOG_ERROR("Get ip address fail, %d, %s", errno, strerror(errno));
        goto FAIL;
    }

    memset(&ifr.ifr_addr, 0, sizeof(ifr.ifr_addr));
    err = ioctl(sockfd, SIOCGIFHWADDR, &ifr); // mac地址
    if (0 == err) {
        if (phy_addr_len < PHY_ADDR_LEN || sizeof(ifr.ifr_hwaddr.sa_data) < PHY_ADDR_LEN) {
            //LOG_ERROR("Mac address format error.");
            goto FAIL;
        }
        memcpy(phy_addr, ifr.ifr_hwaddr.sa_data, PHY_ADDR_LEN);
    }
    else {
        //LOG_ERROR("Get mac address fail, %d, %s", errno, strerror(errno));
        goto FAIL;
    }

    close(sockfd);
    return 0;

FAIL:
    close(sockfd);
    return -1;
}


int main()
{
    uint32_t ip_addr;
    uint8_t phy_addr[MAX_PHY_ADDR_LEN];
    memset(phy_addr, 0, sizeof(phy_addr));

    int err = get_ip_mac_address(ip_addr, phy_addr, MAX_PHY_ADDR_LEN); // 获取ip和mac地址
    in_addr ip;
    ip.s_addr = ip_addr;
    printf("send_agent_vdesk_client_info: %u, ip_addr:%s\n", ip_addr, inet_ntoa(ip));
    printf("send_agent_vdesk_client_info: phy_addr:%02x:%02x:%02x:%02x:%02x:%02x\n", 
            phy_addr[0], phy_addr[1], phy_addr[2], phy_addr[3], phy_addr[4], phy_addr[5]);
    return 0;
}
