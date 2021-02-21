CC= g++
CFLAGS= -Wextra -Wvla -Wall -std=c++14 -g
CODEFILES=  ex2.tar ikea.cpp  ikea.h Product.cpp Product.h Makefile


#make all
all: ex2

# make ex2- generating ex2
ex2: Product.o ikea.o
	$(CC) $(CFLAGS) Product.o ikea.o -o ex2

# generating tar file
tar:
	tar -cvf $(CODEFILES)

# make clean
clean:
	-rm -f *.o  Product ikea

#tests
tests:
	( cd tests-cpp-ex2/ ; java -jar SimpleTest.jar  )

.PHONY: clean