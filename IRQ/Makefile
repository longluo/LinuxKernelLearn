obj-m:=wqtest.o
PWD:=$(shell pwd)
CUR_PATH:=$(shell uname -r)
KERNELPATH:=/usr/src/linux-headers-$(CUR_PATH)

all:
	make -C $(KERNELPATH) M=$(PWD) modules
clean:
	make -C $(KERNELPATH) M=$(PWD) clean
