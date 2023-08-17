# SCSI实操

第一次操作失败了，一直没有想通，后面参考了D:\Github\Storage\c++\udev\bulk_only\libusb_operate_upan.c代码才恍然大悟。

## 自己编写的代码
怎么也没有想通，为何cbw发送一直返回IO错误，现在明白应该是libusb操作失败的问题，因为需要调用libusb_bulk_transfer函数。
之前还有就是提前关闭了ctx导致了问题。
```
root@hankin:~# ./a.out
[INFO][device_helper](deal_datain|142)libusb_bulk_transfer finish, ret -1, ep 0x81, transferred -1
[ERROR][device_helper](deal_datain|152)deal_datain failed
[INFO][device_helper](read_capacity|181)read_capacity deal_datain finish, ret -1
[ERROR][device_helper](read_capacity|183)deal_datain fail, ret -1
[ERROR][device_helper](main|198)usbacc_read_capacity, ret=-1
```

## 替换成usbfs驱动还是存在问题
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
[INFO][device_helper](main|283)usbacc_read_capacity ok, size_per_sector=512, all_sector_count=120845299
```