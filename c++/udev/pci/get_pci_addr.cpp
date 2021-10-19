#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

struct pci_addr {
    unsigned int domain;
    unsigned char bus;
    unsigned char devid;
    unsigned char function;
};
//字符转十进制的接口
int char_to_hex(char *byte)
{
    int tmp = 0;
    if('0' <= *byte && *byte <= '9')
        tmp = *byte - '0';
    else if('a' <= *byte && *byte <= 'f')
        tmp = *byte - 'a' + 10;
    else if('A' <= *byte && *byte <= 'F')
        tmp = *byte - 'A' + 10;
    else
        return -1;
    return tmp;
}

//这里就写个接口，如果要用直接复制过去就可以
/*
	输入：
	pos: 设备地址字符串   如"0000:02.00.0"
	输出：
	pci: 存储设备地址四个部分
*/
int parse_pci_addr(struct pci_addr *pci, char *str)
{
    int count = 0;
    char *pos = str;

    while('\0' != *pos) {
        if(count < 1) {
            pci->domain = char_to_hex(pos) * 16 * 16 * 16;            //pci->domain = char_to_hex(pos)<<12
            pci->domain = pci->domain + char_to_hex(pos + 1) * 16 * 16;
            pci->domain = pci->domain + char_to_hex(pos + 2) * 16;
            pci->domain = pci->domain + char_to_hex(pos + 3);
        } else if(':' == *pos && 4 == count) {
            pci->bus = pci->bus + char_to_hex(pos + 1) * 16;
            pci->bus = pci->bus + char_to_hex(pos + 2);
        } else if(':' == *pos && 7 == count) {
            pci->devid = pci->devid + char_to_hex(pos + 1) * 16;
            pci->devid = pci->devid + char_to_hex(pos + 2);
        } else if('.' == *pos) {

            pci->function = char_to_hex(pos + 1);
        }
        count++;
        pos++;
    }
    printf("pci_addr:%04x:%02x:%02x:%01x\n", pci->domain, pci->bus, pci->devid, pci->function);
    return 0;
}

/*
首先，lspci可以看设备地址，但是有些机器是不显示域的。
/sys/bus/pci/devices目录下有所有PCI设备地址，以目录名字存在
例如“0000:02:00.0”分为4个部分，因为是字符串，如果要处理，要转成相应的16进制，因为这是16进制表示的。
第一部分0000 ：代表域
第二部分02 ：代表总线编号
第三部分00 ：代表设备号
第四部分0 ：代表功能号
*/

void printf_pci_addr()
{
    DIR *dir = opendir("/sys/bus/pci/devices");
    struct dirent *pdirent = NULL;

    while((pdirent = readdir(dir)) != NULL) {
        //把. ..过滤掉
        if(strcmp(pdirent->d_name, ".") == 0 ||
           strcmp(pdirent->d_name, "..") == 0)
            continue;
        //全部打印出来了
        printf("%s\n", pdirent->d_name);

        struct pci_addr pci;
        parse_pci_addr(&pci, pdirent->d_name);
    }
}

int main(int argc, char **argv)
{
    printf_pci_addr();
    return 0;
}
