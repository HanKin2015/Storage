import usb.core
import usb.util

# 查找USB设备
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)

# 如果设备不存在，抛出异常
if dev is None:
    raise ValueError('Device not found')

# 尝试获取设备的接口
cfg = dev.get_active_configuration()
interface = cfg[(0,0)]

# 打开设备
dev.set_configuration()
usb.util.claim_interface(dev, interface)

# 发送数据
dev.write(1, b'Hello, World!')

# 释放设备
usb.util.release_interface(dev, interface)
dev.reset()