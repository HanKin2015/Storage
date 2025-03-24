# SCSI实操

第一次操作失败了，一直没有想通，后面参考了D:\Github\Storage\c++\udev\bulk_only\libusb_operate_upan.c代码才恍然大悟。
友情链接：
D:\Github\GitBook\gitbook\USBDevice\bulk.md
D:\Github\GitBook\gitbook\USBDevice\FAT32.md

## 1、常见 SCSI 指令操作码
SCSI（Small Computer System Interface）指令操作码是用于与 SCSI 设备（如硬盘、光驱、打印机等）进行通信的命令。每个 SCSI 命令都有一个特定的操作码，指示设备执行特定的操作。

| 操作码 | 名称                          | 描述                                     |
| ------ | ----------------------------- | ---------------------------------------- |
| 0x00   | TEST UNIT READY               | 检查设备是否准备好。                     |
| 0x01   | REWIND                        | 磁带设备的倒带命令。                     |
| 0x03   | REQUEST SENSE                 | 请求设备返回错误信息。                   |
| 0x08   | READ                          | 从设备读取数据。                         |
| 0x0A   | WRITE                         | 向设备写入数据。                         |
| 0x0B   | SEEK                          | 移动到指定位置（适用于磁带设备）。       |
| 0x12   | INQUIRY                       | 获取设备的基本信息（如制造商、型号等）。 |
| 0x1A   | MODE SENSE                    | 获取设备的模式参数。                     |
| 0x1B   | MODE SELECT                   | 设置设备的模式参数。                     |
| 0x28   | READ (10)                     | 从设备读取数据（10字节地址）。           |
| 0x2A   | WRITE (10)                    | 向设备写入数据（10字节地址）。           |
| 0x2B   | WRITE AND VERIFY (10)         | 写入数据并验证（10字节地址）。           |
| 0x35   | READ CAPACITY                 | 获取设备的容量信息。                     |
| 0x3C   | READ DISC INFORMATION         | 读取光盘信息（适用于光盘设备）。         |
| 0x3E   | READ TRACK INFORMATION        | 读取轨道信息（适用于光盘设备）。         |
| 0x5A   | READ LONG                     | 从设备读取长数据（适用于某些设备）。     |
| 0x5B   | WRITE LONG                    | 向设备写入长数据（适用于某些设备）。     |
| 0xA0   | START STOP UNIT               | 启动或停止设备。                         |
| 0xB0   | PREVENT ALLOW MEDIUM REMOVAL  | 防止或允许介质移除。                     |
| 0xB1   | GET EVENT STATUS NOTIFICATION | 获取事件状态通知。                       |

## 2、自己编写的代码
怎么也没有想通，为何cbw发送一直返回IO错误，现在明白应该是libusb操作失败的问题，因为需要调用libusb_bulk_transfer函数。
之前还有就是提前关闭了ctx导致了问题。
```
root@hankin:~# ./a.out
[INFO][device_helper](deal_datain|142)libusb_bulk_transfer finish, ret -1, ep 0x81, transferred -1
[ERROR][device_helper](deal_datain|152)deal_datain failed
[INFO][device_helper](read_capacity|181)read_capacity deal_datain finish, ret -1
[ERROR][device_helper](read_capacity|183)deal_datain fail, ret -1
[ERROR][device_helper](main|198)read_capacity, ret=-1
```

## 3、替换成usbfs驱动还是存在问题
原来是跟结构体对齐有关，但是其他人代码没有这个问题，是因为传递了正确的长度罢了。
cbw指令长度是31，csw的长度是13。

最终代码见：D:\Github\Storage\c++\udev\bulk_only\bulk_transfer_example.c
运行结果：
```
[INFO][device_helper](deal_datain|188)55 53 42 43 ed3839b0 00000008 80 00 0a
[INFO][device_helper](deal_datain|190)25
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|190)00
[INFO][device_helper](deal_datain|192)31 31
[INFO][device_helper](bulk_transfer_clear_halt|147)libusb_bulk_transfer finish, ret 0, i 0, ep 0x2, transferred 31
[INFO][device_helper](deal_datain|198)CBW bulk_transfer_clear_halt cbw finish, ret 0, ep_out 0x2, transferred 0x1f
[INFO][device_helper](deal_datain|210)DATA bulk_transfer_clear_halt data-in finish, ret 0, ep_in 0x81, actual_length 0x8
[INFO][device_helper](bulk_transfer_clear_halt|147)libusb_bulk_transfer finish, ret 0, i 0, ep 0x81, transferred 13
[INFO][device_helper](deal_datain|218)CSW bulk_transfer_clear_halt csw finish, ret 0, ep_in 0x81, actual_length 0xd
[INFO][device_helper](deal_datain|225)deal_datain done
[INFO][device_helper](read_capacity|260)read_capacity deal_datain finish, ret 0
[INFO][device_helper](read_capacity|270)last_block_lba=0x733f3f3, size_per_block=0x200
[INFO][device_helper](main|283)read_capacity ok, size_per_sector=512, all_sector_count=120845299
```

## 4、sg3-utils 工具
sg3-utils 是一个常用的工具集，可以用来发送 SCSI 命令。可以使用以下命令来设置 USB 设备为只读模式。
```
sudo sg_mode --set-read-only /dev/sdX

sg_modes命令等
```

## 5、dd命令可以操作U盘扇区数据
详情见：D:\Github\GitBook\gitbook\USBDevice\FAT32.md



