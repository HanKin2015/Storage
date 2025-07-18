# OpenCV安装

## 安装pip3命令
```
sudo apt-get install python3-pip
```

## 安装OpenCV库
现代 Linux 发行版（如 Ubuntu 22.04+）遵循 PEP 668，通过 /etc/pip.conf 配置文件禁止 pip 修改系统 Python 环境。这是为了防止 pip 和 apt 之间的依赖冲突。
```
这样会报错：使用了外部管理的 Python 环境（由操作系统包管理器控制），直接使用 pip 安装可能会破坏系统环境。这是现代 Linux 发行版（如 Ubuntu 22.04+）采用的安全策略。
sudo pip3 install opencv-python

sudo apt-get install python3-opencv
```

## 强制安装（未测试）
```
sudo pip3 install --break-system-packages opencv-python
```

注意：这可能导致系统 Python 环境不稳定，仅建议在测试环境中使用。

