ALL: main

ccflags-y += -I$(src)/include/
specktest-objs := main_kernel.o sha3.o
obj-m += shatest.o

main:
	gcc -g -c sha3.c
	gcc -g -c main.c
	gcc -g -o main main.o sha3.o

main_kernel:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test: main
	./main

test_kernel: main_kernel
	sudo insmod shatest.ko
	sudo rmmod shaktest.ko

infer:
	make clean; infer-capture -- make; infer-analyze -- make

clean:
	rm *.o
	rm main

clean_kernel:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
