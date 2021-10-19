import winreg
import wmi

PATH = "SYSTEM\\ControlSet001\\Enum\\"

m = wmi.WMI()
#获取屏幕信息
monitors = m.Win32_DesktopMonitor()

for m in monitors:
    print(m)

    # 可能虚拟机显示不一样，结果除数为0
    subPath = m.PNPDeviceID
    infoPath = PATH + subPath + "\\Device Parameters"
    key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE,infoPath)
    #屏幕信息按照一定的规则保存（BAD_EDID）
    value = winreg.QueryValueEx(key,"BAD_EDID")[0]
    winreg.CloseKey(key)
    
    #屏幕实际尺寸
    width, height = value[21], value[22]
    #推荐屏幕分辨率
    widthResolution = value[56] +(value[58]>>4)*256
    heightResolution = value[59] +(value[61]>>4)*256
    #屏幕像素密度（Pixels Per Inch）
    widthDensity = widthResolution/(width/2.54)
    heightDensity = heightResolution/(height/2.54)
    
    print("屏幕宽度：", width, " (厘米)")
    print("屏幕高度：", height, " (厘米)")
    print("水平分辩率: ", widthResolution, " (像素)")
    print("垂直分辩率: ", heightResolution, " (像素)")
    #保留小数点固定位数的两种方法
    print("水平像素密度: ", round(widthDensity, 2), " (PPI)")
    print("垂直像素密度: ", "%2.f"%heightDensity, " (PPI)")
