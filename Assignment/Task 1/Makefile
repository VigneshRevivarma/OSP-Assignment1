.default: all

all: Task1

clean:
	rm -rf Task1filter *.o *.dSYM

Task2: Map1.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^