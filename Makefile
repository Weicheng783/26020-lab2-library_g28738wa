all: test-suite

test-suite: library.o catch.o test-suite.o
	g++ test-suite.o library.o catch.o -o test-suite

catch.o: catch.cpp catch.h
	g++ -c catch.cpp -o catch.o

test-suite.o: test-suite.cpp catch.cpp catch.h
	g++ -c test-suite.cpp -o test-suite.o

library.o: library.cpp library.h
	g++ -c library.cpp -o library.o

clean:
	rm -rf *.o test-suite
