ifneq ($(KERNELRELEASE),)
obj-m := my_driver.o
 
else
PWD  := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
endif