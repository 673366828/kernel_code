KERNEL_DIR:=/lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) clean
obj-m:=file_operate.o
