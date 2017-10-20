CFLAGS=-std=gnu99 -pedantic -Wall
computPower.exe: power.c test-power.o 
	gcc $(CFLAGS) -o computPower.exe power.c test-power.o
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
