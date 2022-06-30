/**
* 文 件 名: study_readdir.c
* 文件描述: 学习readdir函数
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0 -lpthread -lm参数
* 创建日期: 2022.06.29
* 修改日期：2022.06.29
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define NET_CLASS_PATH "/sys/class/net/"
#define MAX_PATH_LEN 256

static bool get_real_path(std::vector<std::string> net_symlink_file_paths);

/*
获取文件夹下文件的绝对路径（只不过该文件夹中文件都是软链接罢了）

-----get_symlink_file_path [22]-----
net_symlink_file_path: /sys/class/net/ens18
net_symlink_file_path: /sys/class/net/lo

lrwxrwxrwx  1 root root 0 6月  28 22:06 ens18 -> ../../devices/pci0000:00/0000:00:12.0/virtio6/net/ens18/
lrwxrwxrwx  1 root root 0 6月  28 22:06 lo -> ../../devices/virtual/net/lo/
*/
static bool get_symlink_file_path()
{
    printf("-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
	std::vector<std::string> net_symlink_file_paths;
    struct dirent *st_dirent;
    DIR *dir;
    std::string net_symlink_file_path;
    
    dir = opendir(NET_CLASS_PATH);
    if (dir == NULL) {
        printf("opendir failed, err=%u, %s\n", errno, strerror(errno));
        return false;
    }
    while ((st_dirent = readdir(dir)) != NULL) {
        if (st_dirent->d_type == DT_LNK) {
            net_symlink_file_path = NET_CLASS_PATH;
            net_symlink_file_path += st_dirent->d_name;
            net_symlink_file_paths.push_back(net_symlink_file_path);
            printf("net_symlink_file_path: %s\n", net_symlink_file_path.c_str());
        }
    }
	
	// st_dirent不需要关闭释放
    closedir(dir);
    dir = NULL;
	
	get_real_path(net_symlink_file_paths);
    return true;
}

/*
获取软链接的真实路径

-----get_real_path [69]-----
symlink: /sys/class/net/ens18, real_path: ../../devices/pci0000:00/0000:00:12.0/virtio6/net/ens18
symlink: /sys/class/net/lo, real_path: ../../devices/virtual/net/lo
*/
static bool get_real_path(std::vector<std::string> net_symlink_file_paths)
{
    printf("-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    char real_path[MAX_PATH_LEN] = { 0 };
    std::string real_path_str    = "";
    int ret                      = -1;

    std::vector<std::string>::iterator it = net_symlink_file_paths.begin();
    for (; it != net_symlink_file_paths.end(); it++) {
        memset(real_path, 0, MAX_PATH_LEN);
        ret = readlink((*it).c_str(), real_path, MAX_PATH_LEN);
        if (ret == -1) {
            printf("readlink failed, ret=%d, err=%u, %s\n", ret, errno, strerror(errno));
            return false;
        }

        printf("symlink: %s, real_path: %s\n", (*it).c_str(), real_path);
    }
    return true;
}

int main()
{
	(void)get_symlink_file_path();
	return 0;
}