# inf
INF文件用于定义如何安装设备驱动程序，包括文件复制、注册表项添加等操作。

# USB autorun
D:\Github\GitBook\gitbook\USBDevice\usb_autorun.md

# inf教程
https://www.cr173.com/html/8075_1.html
https://learn.microsoft.com/zh-cn/windows-hardware/drivers/install/using-a-universal-inf-file
https://learn.microsoft.com/zh-cn/windows-hardware/drivers/ifs/creating-an-inf-file-for-a-file-system-driver

# 命令
安装：rundll32.exe setupapi,InstallHinfSection DefaultInstall 132 .\file_operation.inf
卸载：rundll32.exe setupapi,InstallHinfSection DefaultUninstall 132 .\file_operation.inf

https://blog.csdn.net/weixin_44452065/article/details/135830678
安装驱动：pnputil /add-driver XXX.inf /install /reboot
pnputil -i -a XXX.inf

卸载驱动：pnputil /delete-driver oem110.inf /force
显示驱动：pnputil /enum-drivers > a.txt