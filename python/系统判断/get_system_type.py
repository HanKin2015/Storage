import platform
import sys

# 一般linux结果为linux*，windows为win32/64
print(sys.platform)

# 一般linux结果为('32bit','ELF')ELF或者('64bit','ELF')ELF，windows为('32bit','windowsPE')或者('64bit','windowsPE')
print(platform.architecture())

# 一般linux结果为'Linux-*_*'，后面跟版本号，windows为'Windows-*-*'，后面也跟版本
print(platform.platform())

# 一般linux结果为linux，windows结果为windows
print(platform.system())