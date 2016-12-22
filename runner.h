#ifndef RUNNER_H
#define RUNNER_H

#include "NeuralNetwork.h"
#include "TicTacToe.h"
#include "constants.h"
#include "player.h"

#include <vector>

class Runner {

public:
	Runner(NeuralNetwork *, bool, bool);
	~Runner();

	vector<State> getBadStates() const;
	vector<State> getGoodStates() const;

	void dump() const;

private:
	short endState;
	TicTacToe game;
	std::vector<Move> moves;
	Player* p1;
	Player* p2;
	void runSimulation();
};
#endif
