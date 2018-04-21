all: test

FLAGS=-Wall -pedantic -std=c++17 -g

test: test.o btriangle.o
	g++ -o $@ $^

test.o: test.cc
	g++ $(FLAGS) -c -o $@ $<

btriangle.o: btriangle.cc
	g++ $(FLAGS) -c -o $@ $<
