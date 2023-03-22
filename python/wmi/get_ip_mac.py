import socket
import win32com.client

def get_ip_mac():
    """获取ip地址行不通
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')
    address = wmi.ExecQuery('SELECT * FROM Win32_NetworkAdapterConfiguration')
    for elem in address:
        if elem.IPAddress and elem.DefaultIPGateway:
            print(elem.IPAddress, elem.ServiceName)
            print(type(elem.IPAddress))
            print(len(elem.IPAddress))  # 可能存在第二个成员是本地链接IPv6地址
            return elem.IPAddress[0], elem.MACAddress
            #for prop in elem.Properties_:
            #    print(prop.Name, ":", prop.Value)


#获取计算机名称和IP
hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)
print("计算机名称: %s" %hostname)
print("IP地址: %s" %ip)

ip, mac = get_ip_mac()
print(ip)
print(mac)