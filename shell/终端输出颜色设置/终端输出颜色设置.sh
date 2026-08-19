#!/bin/bash

# 颜色定义 (用于输出提示)
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}开始从主线分支更新脚本文件...${NC}"
echo -e "${GREEN}当前分支: $(git rev-parse --abbrev-ref HEAD)${NC}"
echo -e "${GREEN}目标分支: ${MAINLINE_BRANCH}${NC}"
echo -e "${GREEN}========================================${NC}"

