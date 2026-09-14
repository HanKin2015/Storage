!/bin/bash
set -x
cd .
if [-t 0]; then
echo "You are in a terminal."
else
echo "Input is redirected."
fi

`-t fd` 是 `test` 命令的选项：

> 
> `-t 文件描述符`：**如果这个文件描述符关联到终端（TTY），返回 true**。

- `0` = **标准输入 stdin**（文件描述符 0）
- `1` = stdout 标准输出
- `2` = stderr 标准错误

## 含义拆解

`[ -t 0 ]` → **判断标准输入是不是终端设备**

1. 你直接在 shell 敲命令运行脚本：stdin 就是当前终端 → `[ -t 0 ]` 成立，打印 `You are in a terminal.`
2. 重定向输入（管道、文件输入），stdin 不再是终端：

```
./l.sh < test.txt   # 输入来自文件 → -t 0 假
cat test.txt | ./l.sh # 管道输入 → -t 0 假
```

## 补充对比

```
[ -t 1 ] # 判断 stdout 是否指向终端
[ -t 2 ] # 判断 stderr 是否指向终端
```

常见场景：脚本判断**是否交互式运行**，很多时候就用 `[ -t 0 ]`。