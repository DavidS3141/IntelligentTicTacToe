#include "runner.h"

Runner::Runner(NeuralNetwork *n) :
		network(n) {
	runSimulation();
}

void Runner::runSimulation() {
	short player = 1;
	short row, column;
	short state = 0;
	while (!state) {
		network->getMove(game->getBoard(player), row, column);
		moves.push_back(std::make_tuple(row, column, player));
		state = game->makeMove(row, column, player);
		player = (player % 2) + 1;
	}
	endState = state;
}

vector<State> Runner::getGoodStates() {
	return vector<State>();
}

vector<State> Runner::getBadStates() {
	return vector<State>();
}
