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
	if (bEnd[std::get<0>(m)][std::get<1>(m)] != 0)
		bEnd[std::get<0>(m)][std::get<1>(m)] = -1;
	else
		bEnd[std::get<0>(m)][std::get<1>(m)] = std::get<2>(m);
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
	ret[std::get<0>(move) * 3 + std::get<1>(move)] = 1.0;
	return ret;
}

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

Move getMoveNode(vector<double> nodes) {
	Move ret = std::make_tuple(0, 0, 0);
	for (int i = 0; i < 9; i++) {
		if (nodes[i] == 1.0) {
			std::get<1>(ret) = i % 3;
			std::get<0>(ret) = i / 3;
		}
	}
	return ret;
}
