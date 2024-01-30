## 1、需求
想获取usb设备加载的驱动程序详细信息，之前研究发现加载sys文件是通过主驱动程序以及一些过滤驱动程序组成。（只针对视频设备做检测）
后来发现设备可能还会加载dll文件，甚至inf文件（暂没遇到），搜了很多资料并没有关于dll文件的介绍，注册表中也无。

## 2、探索
发现注册表中计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Setup\PnpLockdownFiles\%SystemRoot%/System32/SysFxUI.dll会显示该dll文件的Owners，然后就会找到很多inf文件，inf文件在C:\Windows\INF\目录中。

对于inf文件内容，可以发现SourceDisksFiles字段中就是usb设备驱动程序详细信息加载的驱动文件，需要进行组合。
上面这是逆向查找，但是需要正向找到几种方法。

## 3、通过Win32_PnPEntity中的Service
在注册表SYSTEM\CurrentControlSet\Services\中就可以找到相关联的inf文件，然后再在inf文件中读取SourceDisksFiles字段。
PowerShell命令：Get-CimInstance Win32_PnPEntity

## 4、通过Win32_PnPSignedDriver可以直接找到inf文件
再在inf文件中读取SourceDisksFiles字段。
PowerShell命令：Get-CimInstance Win32_PnPSignedDriver
Get-CimInstance -ClassName Win32_PnPSignedDriver | Where-Object { $_.DeviceName -eq $null }
Get-CimInstance -ClassName Win32_PnPSignedDriver | Where-Object { $_.IsSigned -eq $false }

## 5、问题待解决
复合设备中每个加载的驱动程序详细信息不同，如一款摄像头，音频设备和视频设备如何区分？

我这有一款摄像头，有音频设备和视频设备，通过wmi命令也找到了三个此相关信息，通过DeviceClass或者PNPClass字段可以进行区分，有USB、MEDIA、CAMERA之分。

其实现在探索也仅仅是摄像头设备的问题，因此只需要关注CAMERA类型设备即可。
