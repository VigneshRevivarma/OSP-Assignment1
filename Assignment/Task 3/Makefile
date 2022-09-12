.default: all

all: Task3

clean:
	rm -rf task3 *.o *.dSYM

Task2: Map2.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^