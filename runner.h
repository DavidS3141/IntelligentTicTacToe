#ifndef RUNNER_H
#define RUNNER_H

#include "NeuralNetwork.h"
#include "TicTacToe.h"
#include "constants.h"
#include <vector>

class Runner {

public:
	Runner(NeuralNetwork *);

	vector<State> getBadStates();
	vector<State> getGoodStates();

private:
	short endState;
	TicTacToe game;
	std::vector<Move> moves;
	NeuralNetwork * const network;
	void runSimulation();
};
#endif
