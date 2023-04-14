# 检查文件合法性
readelf命令
file命令
ldd命令

```
[admin@hankin ~]$ file check_usable_video
check_usable_video: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.32, BuildID[sha1]=7725f1125840591e2d849a5687c84c383348fca0, not stripped
[admin@hankin ~]$ file v4l2_tool
v4l2_tool: ELF 32-bit LSB shared object, ARM, version 1 (SYSV), dynamically linked (uses shared libs), BuildID[md5/uuid]=fc0c2e267d77e0d6b16e67d49daefe3e, stripped
[admin@hankin ~]$ file v4l2_tool_4.2
v4l2_tool_4.2: ELF 32-bit LSB shared object, ARM, version 1 (SYSV), dynamically linked (uses shared libs), stripped
```