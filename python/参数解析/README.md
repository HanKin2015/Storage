# python 全网最优雅命令行参数解析, 没有之一
https://zhuanlan.zhihu.com/p/657492122?utm_id=0

## 1、sys模块（调试方便）
```
import sys

# 打印 sys 模块获取到的命令行参数
print(sys.argv)
```

## 2、getopt模块（复杂参数）
```
import getopt

opts,args=getopt.getopt(sys.argv[1:],"i:ho:",["help","input=","output="])
# 打印选项列表
print(opts)
# 打印参数值列表
print(args)

# 解析参数对应的值
for opts,arg in opts:
	print(opts)
	if opts=="optName":
		print("optName is value is:", arg)
```

## 3、argparse模块（正式）
```
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-a', '--arg1', help='argument 1')
parser.add_argument('-b', '--arg2', help='argument 2')
parser.add_argument('-c', '--arg3', help='argument 3')

args = parser.parse_args()

print(args.arg1)
print(args.arg2)
print(args.arg3)
```

## 4、DebugInfo模块（不是很推荐，因为需要单独安装）
是基于 argparse 的一个二次封装, 但相对于直接使用 argparse, 确实方便和清晰不少.


