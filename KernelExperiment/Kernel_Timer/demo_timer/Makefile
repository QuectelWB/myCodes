obj-m:=demo_timer.o
ARCH=arm
CROSS_COMPILE=arm-linux-gnueabi-
# KDIR:=/lib/modules/$(shell uname -r)/build

KDIR:=/home/rlk/rlk_basic/runninglinuxkernel_4.0

PWD:=$(shell pwd)

default:
	$(MAKE) ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C $(KDIR) M=$(PWD) modules

install:
	cp *.ko  /home/rlk/rlk_basic/runninglinux/runninglinuxkernel_4.0/kmodules
clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.markers *.unsigned
