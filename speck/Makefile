ALL: main

ccflags-y += -I$(src)/include/
specktest-objs := main_kernel.o speck.o
obj-m += specktest.o

main:
	gcc -g -c speck.c
	gcc -g -c main.c
	gcc -g -o main main.o speck.o

main_kernel:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test: main
	./main

test_kernel: main_kernel
	sudo insmod specktest.ko
	sudo rmmod specktest.ko

infer:
	make clean; infer-capture -- make; infer-analyze -- make

clean:
	rm *.o
	rm main

clean_kernel:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
