if command -v ls >/dev/null 2>&1; then
    echo "ls 存在"
else
    echo "ls 不存在"
fi

if type python3 &>/dev/null; then
    echo "python3 exists"
fi

# 不建议！which 是外部命令，部分精简系统没有，且受 PATH/别名干扰
if which xxx >/dev/null 2>&1; then

command -v docker >/dev/null 2>&1 && echo "ok" || echo "no"
