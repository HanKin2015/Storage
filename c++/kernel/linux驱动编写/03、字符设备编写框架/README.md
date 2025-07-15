旧版内核（如 2.6.x）支持 ioctl 作为标准接口。
新版内核（如 5.0+）移除了 ioctl，改用 unlocked_ioctl（用于非原子上下文）和 compat_ioctl（用于 32 位 / 64 位兼容）。
