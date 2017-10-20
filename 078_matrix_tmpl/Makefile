CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
matrixTest: matrix.o test.o	
	g++ -o matrixTest $(CCFLAGS) matrix.o test.o

%.o: %.cpp matrix.h
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ matrixTest
