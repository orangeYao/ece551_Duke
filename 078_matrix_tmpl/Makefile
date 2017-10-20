CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
<<<<<<< HEAD
matrixTest: matrix.o test.o	
	g++ -o matrixTest $(CCFLAGS) matrix.o test.o

%.o: %.cpp matrix.h
	g++ -c $(CCFLAGS) $<
=======
matrixTest: test.cpp 
	g++ -o matrixTest $(CCFLAGS) test.cpp
>>>>>>> 495227147f64ad9a0639b85d203607ff87c09ad8

clean:
	rm -f *.o  *~ matrixTest
