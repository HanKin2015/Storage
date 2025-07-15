bar ?= world  # 若 bar 未定义，则赋值为 world
bar := hello  # 先定义 bar 为 hello

bala := yes
bala ?= no  # 无效，bala 已定义
all:
	@echo $(bar)	# 输出 hello
	@echo $(bala)	# 输出 yes