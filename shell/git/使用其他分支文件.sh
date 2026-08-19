#!/bin/bash

# 定义变量
MAINLINE_BRANCH="master"
TARGET_FILES=(
    "setup.sh"
    "build.sh"
    "gen_zip.sh"
)

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

# 检查目标分支是否存在
if ! git rev-parse --verify "$MAINLINE_BRANCH" >/dev/null 2>&1; then
    echo -e "${RED}错误: 分支 '$MAINLINE_BRANCH' 不存在!${NC}"
    echo "请确认分支名称是否正确，或者先执行 'git fetch' 获取远程分支。"
    exit 1
fi

# 记录当前目录，确保脚本在项目根目录或正确路径下运行
# 如果这些脚本在子目录中，请调整下面的路径逻辑，或者在执行脚本前cd到对应目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# 逐个检查并检出文件
for file in "${TARGET_FILES[@]}"; do
    if [ -f "$file" ]; then
        echo -e "${YELLOW}警告: 本地已存在 $file，将被覆盖。${NC}"
    fi
    
    # 检查该文件在目标分支中是否存在
    if git ls-tree -r "$MAINLINE_BRANCH" --name-only | grep -q "^${file}$"; then
        echo "正在从 $MAINLINE_BRANCH 检出 $file ..."
        
        # 核心命令：从指定分支检出特定文件到当前工作区
        if git checkout "$MAINLINE_BRANCH" -- "$file"; then
            echo -e "${GREEN}成功更新: $file${NC}"
            # 可选：给文件添加执行权限
            chmod +x "$file"
        else
            echo -e "${RED}失败: 无法从 $MAINLINE_BRANCH 检出 $file${NC}"
            exit 1
        fi
    else
        echo -e "${RED}错误: 文件 '$file' 在分支 '$MAINLINE_BRANCH' 中不存在!${NC}"
        exit 1
    fi
done

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}所有脚本文件更新完成！${NC}"
echo -e "${YELLOW}请注意：这些文件现在处于 'staged' (暂存) 状态。${NC}"
echo -e "${YELLOW}如果你不想提交这些更改到当前发布分支，请勿执行 'git commit'。${NC}"
echo -e "${YELLOW}如果只是想临时使用，可以保持现状；如果需要还原，可使用 'git restore <file>'。${NC}"
echo -e "${GREEN}========================================${NC}"

# 简写1
for file in setup.sh build.sh gen_zip.sh; do
    git checkout "$MAINLINE_BRANCH" -- "$file"
fi

# 简写2
git checkout master -- setup.sh build.sh gen_zip.sh

# 注意：切换后修改文件是add状态，需要reset取消add，否则之间commit会把修改提交到当前分支