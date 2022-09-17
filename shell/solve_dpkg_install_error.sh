#!/bin/bash
#
# 文 件 名: solve_dpkg_install_error.sh
# 文件描述: 解决E: Sub-process /usr/bin/dpkg returned an error code (1)错误
# 作    者: HanKin
# 创建日期: 2022.09.13
# 修改日期：2022.09.13
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

sudo mv /var/lib/dpkg/info /var/lib/dpkg/info_old
sudo mkdir /var/lib/dpkg/info
sudo apt-get update
apt-get -f install
mv /var/lib/dpkg/info/* /var/lib/dpkg/info_old
rm -rf /var/lib/dpkg/info
mv /var/lib/dpkg/info_old /var/lib/dpkg/info
