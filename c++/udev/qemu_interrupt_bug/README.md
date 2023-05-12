# 问题现象
2.0网卡设备在xhci主控上面无法正常使用，无法检测到插入网线
2.0硕飞SP8-A嵌入式设备在xhci主控上面软件无法识别设备

# 排查过程
打开xhci主控的debug日志发现在计算mfindex值存在问题，发现怎么计算怎么都会出现问题，很奇怪，说明根因不在这里
```
os-posix:273 mfindex 48016 epctx->interval 32 epctx->mfindex_last 0xhci_submit(slotid=l,epid=3)
os-posix:273 mfindex_kick 48032 mfindex 48016
os-posix:273 set xfer->running_retry to 1
os-posix:273 xhci: xfer nacked, stopping schedule
os-posix:273 mfindex_kick 48032 mfindex 48032
os-posix:273 xhci: setup packet pid ox69 addr 1 ep 1
os-posix:273 start usb_handle_packet
os-posix:273 1p status 0
os-posix:273 hejian nr 12p status 0
os-posix:273 kvm: usb-redir: hejian ep 1, pid 105 type 255
os-posix:273 kvm: usb-redir: hejian ep 129, pid 105 type 3
os-posix:273 kvm: usb-redir: whl started 0
os-posix:273 kvm: usb-redir: whl status 0 pid 105 id 164624384 size
os-posix:273 kvm: usb-redir: interrupt-in ep 81 len 8 id 4459591680
os-posix:273 kvm: usb-redir: interrupt-token-in ep 81, no intp, sta
os-posix:273 3p status -2
os-posix:273 xfer->packet.status -2 USB_RET_NAK -2
os-posix:273 kvm: usb-redir: interrupt-in status 0 ep 81 len 8 id 4
os-posix:273 xhci_wakeup_endpoint
os-posix:273 xhci: setup packet pid ox69 addr 1 ep 1
os-posix:273 start usb_handle_packet
os-posix:273 1p status 0
os-posix:273 2p status 0
os-posix:273 hejian nr 1
os-posix:273 kvm: usb-redir: hejian ep 1, pid 105 type 255
```

增加日志发现是内存分配存在问题
```
kvm: usb-redir: ctrl-out type x4o req 0xl v
kvm: ctrl data 0ut: 00 00 00 80 00 00 00 00
kvm: usb-redir: ctrl-in status o len 8 id 43
kvm: usb-redir: ctrl-out type ox4o req 0xl v
kvm: usb-redir: ctrl-in status  len 8 id 43kvm: ctrl data out: 00 00 00 80 00 00 00 40
kvm: usb-redir: ctrl-out type ox4o req oxl v
kvm: ctrl data 0ut: 00 80 00 80 00 00 00 40
kvm: usb-redir: ctrl-in status o len 8 id 43
kvm: usb-redir: interrupt-in ep 8l len 8 id
kvm: usb-redir: interrupt-token-in ep 8l, no
kvm: usb-redir: interrupt-in status 0 ep 81
kvm: usb-redir: interrupt-token-in ep 8l, no
kvm: usb-redir: start malloc
kvm: usb-redir: malloc success
```

# 解决方案
bug提交commit来源d5c42857d6b0c35028897df8dfc3749eba6f6de3

usb-redir: allocate buffers before waking up the host adapter

Needed to make sure usb redirection is prepared to actually handle the
callback from the usb host adapter.  Without this interrupt endpoints
don't work on xhci.

Note: On ehci the usb_wakeup() call only schedules a BH for the actual
work, which hides this bug because the allocation happens before ehci
calls back even without this patch.

