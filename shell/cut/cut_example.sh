#!/bin/sh
#
# 文 件 名: cut_example.sh
# 文件描述: 截断
# 备    注:
# 作    者: HanKin
# 创建日期: 2025.07.04
# 修改日期：2025.07.04
#
# Copyright (c) 2025 HanKin. All rights reserved.
#
target_version="5.9.8"
cur_version="5.9.9.11"

# 提取 cur_version 的前三位
cur_version_trimmed=$(echo "$cur_version" | cut -d '.' -f 1-3)

if dpkg --compare-versions "$cur_version_trimmed" gt "$target_version"; then
    echo "yes $cur_version_trimmed"
else
    echo "no $cur_version_trimmed"
fi

package="common=1.2.4.5"
package_name=$(echo "${package}" | cut -d '=' -f 1)
package_version=$(echo "${package}" | cut -d '=' -f 2)
echo ${package_name}_${package_version}

<<EOF
[root@ubuntu0006:~/myservice-1.0] #./test.sh
yes 5.9.9
common_1.2.4.5
EOF