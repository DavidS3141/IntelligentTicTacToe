#ifndef RUNNER_H
#define RUNNER_H

#include "TicTacToe.h"
#include "constants.h"
#include "player.h"

#include <vector>
#include "neuralNetwork.h"

class Runner {

public:
	Runner(Player*, Player*);

	bool isDraw() const;
	int getWinner() const;

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
