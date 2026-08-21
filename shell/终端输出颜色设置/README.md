# 说明
Bash 脚本中ANSI 转义序列（Escape Sequences）的写法，用来在终端输出带颜色的文字。

```
\033[     ← ESC 字符（ASCII 27），告诉终端"接下来是控制指令，不是普通文字")
  0;      ← 样式代码：0=正常/重置，1=粗体/高亮
  31      ← 颜色代码：31=红色
  m       ← 结束标记（m = Select Graphic Rendition）
```

单引号在 Bash 中是强引用，不会解析 $ 变量，但这里的转义序列 \033 仍然会被识别。用单引号包裹可以避免一些意外的变量扩展问题，同时保持转义码原样。
实际上 \033 在单引号和双引号中都会被解析为 ESC 字符，但单引号更安全。

# 现在更推荐用 tput 命令
```
RED=$(tput setaf 1)      # 红色
GREEN=$(tput setaf 2)    # 绿色
YELLOW=$(tput bold; tput setaf 3)  # 粗体黄色
NC=$(tput sgr0)          # 重置
```

ANSI 编码 → 决定"显示什么字符"（字符集）
ANSI 转义序列 → 决定"怎么显示字符"（颜色、样式、光标位置）

# 颜色重置
```
# 最常用，直接发送重置转义码
printf '\033[0m'

# 或者
echo -e '\033[0m'

# 或者更完整的重置（重置颜色 + 清除所有属性）
printf '\033[0;0m'

tput sgr0    # 重置所有样式（sgr0 = Select Graphic Rendition 0）

reset
```