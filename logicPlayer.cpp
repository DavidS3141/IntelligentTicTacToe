/*
 * logicPlayer.cpp
 *
 *  Created on: 23.12.2016
 *      Author: David
 */

#include "logicPlayer.h"

LogicPlayer::LogicPlayer() {
}

int LogicPlayer::converter(int x) {
	switch (x) {
	case (0):
		return 0;
	case (1):
		return 1;
	case (2):
		return -1;
	}
	return 0;
}

Move LogicPlayer::getMove(Board board) {
	int loosePosition = -1;
	int winPosition = -1;
	for (unsigned i = 0; i < winningPositions.size(); ++i) {
		int counter = 0;
		for (unsigned pos = 0; pos < winningPositions[i].size(); ++pos) {
			counter +=
					converter(
							board[winningPositions[i][pos][0]][winningPositions[i][pos][1]]);
		}
		if (counter == 2) {
			winPosition = i;
			break;
		}
		if (counter == -2) {
			loosePosition = i;
		}
	}
	if (winPosition >= 0) {
		for (unsigned pos = 0; pos < winningPositions[winPosition].size();
				++pos) {
			if (0
					== board[winningPositions[winPosition][pos][0]][winningPositions[winPosition][pos][1]]) {
				return Move(winningPositions[winPosition][pos][0],
						winningPositions[winPosition][pos][1], 1);
			}
		}
	}
	if (loosePosition >= 0) {
		for (unsigned pos = 0; pos < winningPositions[loosePosition].size();
				++pos) {
			if (0
					== board[winningPositions[loosePosition][pos][0]][winningPositions[loosePosition][pos][1]]) {
				return Move(winningPositions[loosePosition][pos][0],
						winningPositions[loosePosition][pos][1], 1);
			}
		}
	}
	if (board[1][1] == 0)
		return Move(1, 1, 1);
	if (board[0][0] == 0)
		return Move(0, 0, 0);
	if (board[0][2] == 0)
		return Move(0, 2, 0);
	if (board[2][0] == 0)
		return Move(2, 0, 0);
	if (board[2][2] == 0)
		return Move(2, 2, 0);
	for (unsigned r = 0; r < 3; ++r)
		for (unsigned c = 0; c < 3; ++c)
			if (board[r][c] == 0)
				return Move(r, c, 1);
	return Move(1, 1, 1);
}
