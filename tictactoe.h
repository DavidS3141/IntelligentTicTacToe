#include <iostream>

#include "constants.h"

/**
 * @class TicTacToe
 * @brief The game TicTacToe.
 *
 * This class represents a playable game of TicTacToe.
 */
class TicTacToe {
public:
	TicTacToe();

	int makeMove(int row, int column, int player);
	Board getBoard(int player);
	int gameEnded();
	bool boardFull();

private:
    /**
     * @brief The TicTacToe board.
     *
     * This board represents the current state of the game.
     */
	Board board;
};
