#include "tictactoe.h"

#include <stdexcept>
#include "constants.h"

TicTacToe::TicTacToe() :
		board(constants::empytBoard) {
}

Board TicTacToe::getBoard(int player) {
	if (player == circle) {
		Board tmp = board;
		for (vector<int> &row : tmp) {
			for (int &field : row) {
				if (field == circle)
					field = cross;
				else if (field == cross)
					field = circle;
			}
		}
		return tmp;
	}
	return board;
}

int TicTacToe::makeMove(int row, int column, int player) {
	if (!(player == cross || player == circle))
		throw std::runtime_error("Player not defined!");
	if (board[row][column] != 0)
		return (player == circle) ? cross : circle;
	else
		board[row][column] = player;
	return gameEnded();
}

int TicTacToe::gameEnded() {
	int player;
	for (auto final : constants::winningPositions)
		if (board[final[0][0]][final[0][1]] == board[final[1][0]][final[1][1]]
				&& board[final[1][0]][final[1][1]]
						== board[final[2][0]][final[2][1]])
			return board[final[0][0]][final[0][1]];
		else if (boardFull())
			return -1;
	return 0;
}

bool TicTacToe::boardFull() {
	for (auto row : board) {
		for (auto field : row) {
			if (field == 0)
				return false;
		}
	}
	return true;
}
