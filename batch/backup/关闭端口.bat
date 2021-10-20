@echo off  

netsh advfirewall firewall add rule name=¡±deny tcp 1433¡± dir=in protocol=tcp localport=1433 action=block
netsh advfirewall firewall add rule name=¡±deny tcp 1434¡± dir=in protocol=tcp localport=1434 action=block
netsh advfirewall firewall add rule name=¡±deny tcp 5554¡± dir=in protocol=tcp localport=5554 action=block
netsh advfirewall firewall add rule name=¡±deny tcp 9996¡± dir=in protocol=tcp localport=9996 action=block

