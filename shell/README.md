# 1、`function func()` 语法
POSIX sh **没有 `function name()`** 这种写法；`function` 关键字是 bash 扩展。
Android `/system/bin/sh` 是 mksh，支持但不标准，稳妥写法：
```
func()
{
    ...
}
```

# 2、declare命令
`declare` 是 bash 内置命令，用来**声明 shell 变量、设置变量属性**，可以定义只读、整数、数组、导出变量等，和 `readonly` 是近亲。

# 3、realpath和dirname
```
realpath j.sh
# /home/root/j.sh

dirname /home/root/j.sh
# /home/root

basename /home/root/j.sh
# j.sh

basename /home/root/j.sh .sh
# j
```
**dirname 和 basename 会先把末尾的斜杠全部删掉，再做拆分**，不是简单按 `/` 切割字符串。
