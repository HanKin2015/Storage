@echo off
@echo 开始设置IP
netsh interface ip set address name="以太网" source=static addr=12.18.0.254 mask=255.255.255.0 gateway=12.18.0.1 gwmetric=0
netsh interface ip set dns name="以太网" source=static addr=114.114.114.114 primary
netsh interface ip add dns name="以太网" address=8.8.8.8 index=2
netsh interface ip add address name="以太网" addr=12.18.0.20 mask=255.255.255.0 gateway=12.18.0.1 gwmetric=0
@echo on
@echo IP已设置
@echo off
del %0
END