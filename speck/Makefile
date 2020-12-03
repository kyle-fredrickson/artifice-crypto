ALL: main

main:
	gcc -g -c speck.c
	gcc -g -c main.c
	gcc -g -o main main.o speck.o

test: main
	./main

clean:
	rm *.o
	rm main
