#ifndef RUNNER_H
#define RUNNER_H

#include <vector>

#include "constants.h"
#include "neuralNetwork.h"
#include "player.h"
#include "TicTacToe.h"

typedef shared_ptr<Player> PlayerPtr;

class Runner {

public:
	Runner(PlayerPtr, PlayerPtr);

	bool isDraw() const;
	int getWinner() const;

	vector<State> getBadStates() const;
	vector<State> getGoodStates() const;
	const vector<Move>& getMoves() const;

	void dump() const;

private:
	void runSimulation();

	short endState;
	TicTacToe game;
	vector<Move> moves;
	PlayerPtr p1;
	PlayerPtr p2;
};
#endif
