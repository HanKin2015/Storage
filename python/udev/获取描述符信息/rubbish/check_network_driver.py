import subprocess

# 执行系统命令
result = subprocess.run(['powershell', 'Get-NetAdapter'], capture_output=True, text=True)

# 检查命令执行结果
if result.returncode == 0:
    # 命令执行成功，检查输出中是否包含网络适配器信息
    if 'Name' in result.stdout and 'Status' in result.stdout:
        print('网络适配器驱动加载正常')
    else:
        print('网络适配器驱动未加载或加载异常')
else:
    # 命令执行失败
    print('命令执行失败')