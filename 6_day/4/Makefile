obj-m:=my_tasklet.o
KDIR=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o app app.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf app
