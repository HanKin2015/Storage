#!/bin/bash
#
# 文 件 名: debug_binary.sh
# 文件描述: 如果二进制文件是有多种参数，这样写可以调试每次调用使用的命令
# 作    者: HanKin
# 创建日期: 2024.08.07
# 修改日期：2024.08.07
#           zhangsan@2023.11.14: 新增修改历史模板参考
#           lisi@2024-03-14: 另外一种格式
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

out_path=/root/xx.log
echo ">> call client_binary at: $(date +%F_%T.%N) ...." >> ${out_path}
cmd_res=$(adesk-client_binary.0 $@)
echo "${cmd_res}" >> ${out_path}
echo "${cmd_res}"