ifeq ($(strip $(MODULE)),)
	obj-m += test.o
else
	obj-m += $(MODULE).o
endif


KERNEL_SRC = /lib/modules/$(shell uname -r)/build

all: modules store

modules:
	make -C $(KERNEL_SRC) M=$(PWD) modules
store:
	gcc -m32 store.c -o store 

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean
