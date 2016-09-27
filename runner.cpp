#include "runner.h"

Runner::Runner(NeuralNetwork *n) :
		network(n) {
	runSimulation();
}

void Runner::dump() const {
	cout << "Last bad move:" << endl;
	vector<State> baddies = getBadStates();
	constants::printMove(baddies[baddies.size() - 1].first,
			baddies[baddies.size() - 1].second);

	cout << "Last good move:" << endl;
	vector<State> goodies = getBadStates();
	constants::printMove(goodies[goodies.size() - 1].first,
			goodies[goodies.size() - 1].second);
	cout << endl;
}

void Runner::runSimulation() {
	short player = 1;
	Move move;
	short state = 0;
	while (!state) {
		move = network->getMove(game.getBoard(player));
		move.player = player;
		moves.push_back(
				move);
		state = game.makeMove(move.row, move.column, move.player);
		player = (player % 2) + 1;
	}
	endState = state;
}

vector<State> Runner::getGoodStates() const {
	vector<State> states = std::vector<State>();
	TicTacToe pseudoGame;
	for (auto move : moves) {
		if (move.player == endState
				|| (endState == -1 && move.player == circle))
			states.push_back(
					std::make_pair(pseudoGame.getBoard(move.player),
							move));
		pseudoGame.makeMove(move.row, move.column, move.player);
	}
	return states;
}

vector<State> Runner::getBadStates() const {
	vector<State> states = std::vector<State>();
	TicTacToe pseudoGame;
	for (auto move : moves) {
		if (move.player != endState
				|| (endState == -1 && move.player == cross))
			states.push_back(
					std::make_pair(pseudoGame.getBoard(move.player),
							move));
		pseudoGame.makeMove(move.row, move.column, move.player);
	}
	return states;
}
