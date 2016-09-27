#include <iostream>

#include "constants.h"

class TicTacToe {
public:
	TicTacToe();

	int makeMove(int row, int column, int player);
	Board getBoard(int player);
	int gameEnded();
	bool boardFull();

private:
	Board board;
};
