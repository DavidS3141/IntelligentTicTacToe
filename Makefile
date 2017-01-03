CC=g++
CFLAGS=-std=c++14 -Wall -g
DEPS = $(wildcard *.h)
SRC = $(wildcard *.cpp)
OBJ = $(addprefix bin/, $(SRC:.cpp=.o))

bin/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	g++ -o IntelligentTicTacToe $^ $(CFLAGS)

clean:
	rm bin/*.o