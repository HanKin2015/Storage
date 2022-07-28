#监控工具
import psutil
import datetime

def getMem_info():
    '''内存信息'''
    mem = psutil.virtual_memory()

    print('总内存：', mem.total/1024/1024/1024)
    print('已用内存', mem.used/1024/1024/1024)


def getCpu_info():
    '''cpu信息'''
    cpu = psutil.cpu_times(percpu=True)

    print('显示所有cpu信息：', cpu)
    print('cpu个数：', psutil.cpu_count())
    print('物理cpu个数：', psutil.cpu_count(logical=True))
    print('swap分区信息：', psutil.swap_memory())

def getDisk_info():
    '''磁盘信息'''
    disk = psutil.disk_partitions()
    print('磁盘信息：', disk)
    print('磁盘利用率：', psutil.disk_usage('C:\\'))
    print('磁盘IO况情：', psutil.disk_io_counters('D:\\'))
    print('按分区获取IO信息：', psutil.disk_io_counters(perdisk=True))


def getNet_info():
    '''网络信息'''
    net = psutil.net_io_counters()

    print('网络信息：', net)
    print('详细信息：', psutil.net_io_counters(pernic=True))

def getOther_info():
    print('用户信息：', psutil.users())
    print('开机时间：', datetime.datetime.fromtimestamp(psutil.boot_time()).strftime("%Y-%m-%d %H:%M:%S"))
    
if __name__ == '__main__':
    getMem_info()
    getCpu_info()
    getDisk_info()
    getNet_info()
    getOther_info()