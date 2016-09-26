#include "constants.h"
#include <iostream>

class TicTacToe {
public:
	TicTacToe() :
			board(constants::empytBoard) {
	}

	int makeMove(int row, int column, int player);
	Board getBoard(int player);
	int gameEnded();
	bool boardFull();

private:
	Board board;
};
