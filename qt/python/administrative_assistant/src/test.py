import platform

import psutil

# 获取CPU信息

cpu_count = psutil.cpu_count() # CPU核数

cpu_freq = psutil.cpu_freq() # CPU频率

cpu_percent = psutil.cpu_percent(interval=1) # CPU使用率

# 获取内存信息

mem = psutil.virtual_memory()

mem_total = mem.total # 内存总量

mem_available = mem.available # 可用内存

# 获取硬盘信息

disk = psutil.disk_partitions()

disk_info = []

for part in disk:
    disk_usage = psutil.disk_usage(part.mountpoint)
    disk_info.append({
    "device": part.device,

    "mountpoint": part.mountpoint,

    "fstype": part.fstype,

    "total": disk_usage.total,
    "used": disk_usage.used,
    "free": disk_usage.free,
    "percent": disk_usage.percent

    })

# 获取网络信息

net_io_counters = psutil.net_io_counters() # 网络IO信息

net_addrs = psutil.net_if_addrs() # 网络地址信息

net_stats = psutil.net_if_stats() # 网络状态信息

# 获取操作系统信息

system = platform.system() # 操作系统名称

release = platform.release() # 操作系统版本号

version = platform.version() # 操作系统发行号

# 输出信息

print("CPU info: ", cpu_count, cpu_freq, cpu_percent)

print("Memory info: ", mem_total, mem_available)

print("Disk info: ", disk_info)

print("Network info: ", net_io_counters, net_addrs, net_stats)

print("OS info: ", system, release, version)

#获取电脑运行资源使用状态

import psutil

# 获取 CPU 的信息

cpu_count = psutil.cpu_count() # CPU 核数

cpu_freq = psutil.cpu_freq() # CPU 主频

cpu_usage = psutil.cpu_percent() # CPU 使用率

# 获取内存的信息

mem_total = psutil.virtual_memory().total # 总内存大小

mem_free = psutil.virtual_memory().available # 空闲内存大小

mem_percent = psutil.virtual_memory().percent # 内存使用率

# 获取磁盘的信息

disk_usage = psutil.disk_usage('/').percent # 系统盘使用率

# 输出结果

print(f"CPU: {cpu_count} 核 {cpu_freq.max:.2f} GHz 使用率 {cpu_usage}%")

print(f"内存: 总共 {mem_total // 1024 // 1024} MB 空闲 {mem_free // 1024 // 1024} MB 使用率 {mem_percent}%")

print(f"系统盘使用率: {disk_usage}%")