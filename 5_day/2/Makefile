obj-m:=ioctl_cal_driver.o
KDIR=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o ioctl_device ioctl_device.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf ioctl_device
