import winreg

# 打开注册表键
key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r'SYSTEM\CurrentControlSet\Enum\USB')

# 遍历子键
for i in range(winreg.QueryInfoKey(key)[0]):
    subkey_name = winreg.EnumKey(key, i)
    print(subkey_name)
    subkey = winreg.OpenKey(key, subkey_name)
    try:
        # 获取Driver值
        driver = winreg.QueryValueEx(subkey, 'Driver')[0]
        print(f'{subkey_name}: {driver}')
    except FileNotFoundError:
        #print('FileNotFoundError')
        pass
    finally:
        subkey.Close()
key.Close()