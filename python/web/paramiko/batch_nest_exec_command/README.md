# 1、占位符问题
```
command = "echo '%s' | sudo -S tcmgrutil debug -k %s -o | awk 'NR == 2{print $5}'" % (server_pwd, client_sn)

# 字符串中的特殊字符：当字符串使用了大括号（{}）作为占位符，如果字符串中包含大括号，可能会导致格式化出错。
# 你可以尝试使用双大括号（{{}}）来转义大括号，例如'{{}}'。
command = "echo {} | sudo -S tcmgrutil debug -k {} -o | awk 'NR == 2{{print $5}}'".format(server_pwd, client_sn)

# 错误演示
command = "echo {} | sudo -S tcmgrutil debug -k {} -o | awk 'NR == 2{print $5}'".format(server_pwd, client_sn)
```

# 2、ini文件问题
注意字符串是不需要加双引号或者单引号的