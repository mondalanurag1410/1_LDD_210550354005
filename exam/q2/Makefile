obj-m:=driver_test.o
KDIR=/lib/modules/$(shell uname -r)/build
all: 
	make -C $(KDIR) M=$(PWD) modules
	gcc -o app1 app1.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf app1
