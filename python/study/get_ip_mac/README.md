# 获取系统的ip和mac地址

## 1、参考
D:\Github\Storage\python\python黑帽\获取Windows主机信息.py
D:\Github\Storage\qt\python\office_assistant\src\hack_interface.py

## 2、chatgpt给的方法
D:\Github\Storage\python\study\get_ip_mac\get_ip_mac.py

注意注意注意：需要考虑到物理机、虚拟机、以及无线wifi场景
如果需要考虑所有场景，那就只能获取本地所有的mac地址和ip地址，然后再进行匹配。

## 3、查询ip的归属地
这里就有一个新的概念了，那就是真实ip地址。

通常情况下，要获取真实的公共 IP 地址，你的设备需要连接到互联网。因为公共 IP 地址是由你的互联网服务提供商分配给你的，所以只有在设备连接到互联网并获得了一个公共 IP 地址之后，才能通过查询服务获取到真实的公共 IP 地址信息。

在局域网中，设备通常会被分配一个局域网内部的 IP 地址，这个 IP 地址是由局域网内部的路由器或者 DHCP 服务器分配的。这个局域网内部的 IP 地址是在局域网内部进行路由和通信时使用的，它并不是公共的互联网 IP 地址。

在局域网中，通常有一个网络地址转换（NAT）设备，比如路由器，它会将局域网内部设备的局域网 IP 地址映射到公共的互联网 IP 地址上。这个公共的互联网 IP 地址是由互联网服务提供商分配的，它是用来在互联网上进行通信的。

虚拟机也是一样，它在局域网中会被分配一个局域网内部的 IP 地址，同时也可以通过 NAT 技术来映射到宿主机的真实 IP 地址上，从而可以在局域网内部和互联网上进行通信。

因此，局域网内部的 IP 地址和真实的公共互联网 IP 地址是不同的概念。获取局域网内部的 IP 地址通常不需要联网解析，因为它是由局域网内部的设备分配的；而获取真实的公共互联网 IP 地址需要联网解析，因为它是由互联网服务提供商分配的。

局域网中可能是存在一个接入ip地址（通过vpn跳转）和客户端的真实ip地址。

## 4、在线查询
whatismyipaddress.com
http://httpbin.org/ip
https://ip.cn/ip/58.20.54.211.html
https://ipinfo.io/

dos：
nslookup myip.opendns.com resolver1.opendns.com

win10 powershell：
(Invoke-WebRequest ifconfig.me/ip).Content.Trim()

## 5、免费的地理位置信息geo-ip数据库maxmind
https://blog.csdn.net/yxhxj2006/article/details/131552936



