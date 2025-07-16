ifneq ($(KERNELRELEASE),)
	# 内核编译系统调用时执行
	obj-m := newchar.o
 
else
	# 用户直接调用 make 时执行
	PWD  := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions modules.*  Module.*
endif