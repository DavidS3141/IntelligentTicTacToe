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

.PHONY: longrun
longrun: $(OBJ)
	g++ -o longRun/LR_IntelligentTicTacToe $^ $(CFLAGS)

user:
	g++ -std=c++14 -g \
		ai.cpp \
		constants.cpp \
		edge.cpp \
		graph.cpp \
		human.cpp \
		logicPlayer.cpp \
		Main.cpp \
		NeuralNetwork.cpp \
		Neuron.cpp \
		node.cpp \
		player.cpp \
		runner.cpp \
		Synapse.cpp \
		tictactoe.cpp \