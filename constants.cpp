/*
 * constants.cpp
 *
 *  Created on: 27.09.2016
 *      Author: David
 */

#include "constants.h"

const char constants::printSymbol(int i) {
	switch (i) {
	case 0:
		return ' ';
	case 1:
		return 'X';
	case 2:
		return 'O';
	default:
		return '#';
	}
}

void constants::printMove(Board &b, Move &m) {
	Board bEnd = b;
	if (bEnd[m.row][m.column] != 0)
		bEnd[m.row][m.column]  = -1;
	else
		bEnd[m.row][m.column]  = m.player;
	cout << printSymbol(b[0][0]) << printSymbol(b[0][1]) << printSymbol(b[0][2])
			<< "    " << printSymbol(bEnd[0][0]) << printSymbol(bEnd[0][1])
			<< printSymbol(bEnd[0][2]) << endl;
	cout << printSymbol(b[1][0]) << printSymbol(b[1][1]) << printSymbol(b[1][2])
			<< " -> " << printSymbol(bEnd[1][0]) << printSymbol(bEnd[1][1])
			<< printSymbol(bEnd[1][2]) << endl;
	cout << printSymbol(b[2][0]) << printSymbol(b[2][1]) << printSymbol(b[2][2])
			<< "    " << printSymbol(bEnd[2][0]) << printSymbol(bEnd[2][1])
			<< printSymbol(bEnd[2][2]) << endl;
}

vector<double> getNodeBoard(Board board) {
	vector<double> ret = vector<double>(27, 0.0);
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 3; j++) {
			ret[i * 9 + j * 3 + board[i][j]] = 1.0;
		}
	}
	return ret;
}

vector<double> getNodeMove(Move move) {
	vector<double> ret = vector<double>(9, 0);
	ret[move.row * 3 + move.column] = 1.0;
	return ret;
}

/*	not needed
Board getBoardNode(vector<double> nodes) {
	Board ret = constants::empytBoard;
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 3; j++) {
			ret[i][j] = static_cast<short>(nodes[i * 9 + j * 3 + 1]
					+ nodes[i * 9 + j * 3 + 2]);
		}
	}
	return ret;
}
*/

Move getMoveNode(vector<double> nodes) {
	Move ret(0, 0, 0);
	double max = -1.;
	for (int i = 0; i < 9; ++i) {
		if (nodes[i] > max) {
			max = nodes[i];
			ret.row = i / 3;
			ret.column = i % 3;
		}
	}
	//std::cout << max << endl;
	return ret;
}
