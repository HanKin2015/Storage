@echo off
@echo ��ʼ����IP
netsh interface ip set address name="��̫��" source=static addr=12.18.0.254 mask=255.255.255.0 gateway=12.18.0.1 gwmetric=0
netsh interface ip set dns name="��̫��" source=static addr=114.114.114.114 primary
netsh interface ip add dns name="��̫��" address=8.8.8.8 index=2
netsh interface ip add address name="��̫��" addr=12.18.0.20 mask=255.255.255.0 gateway=12.18.0.1 gwmetric=0
@echo on
@echo IP������
@echo off
del %0
END