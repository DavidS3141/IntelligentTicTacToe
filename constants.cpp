/*
 * constants.cpp
 *
 *  Created on: 27.09.2016
 *      Author: David
 */

#include "constants.h"

#include <sstream>

/*
 template <typename T> int sgn(T val) {
 return (T(0) < val) - (val < T(0));
 }
 */
const char printSymbol(int i) {
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

void printMove(Board &b, Move &m) {
	Board bEnd = b;
	/*
	 if (bEnd[m.row][m.column] != 0)
	 bEnd[m.row][m.column]  = -1;
	 else
	 */
	bEnd[m.row][m.column] = m.player;
	cout << " --- " << "    " << " --- " << endl;
	cout << "|" << printSymbol(b[0][0]) << printSymbol(b[0][1])
			<< printSymbol(b[0][2]) << "|" << "    " << "|"
			<< printSymbol(bEnd[0][0]) << printSymbol(bEnd[0][1])
			<< printSymbol(bEnd[0][2]) << "|" << endl;
	cout << "|" << printSymbol(b[1][0]) << printSymbol(b[1][1])
			<< printSymbol(b[1][2]) << "|" << " -> " << "|"
			<< printSymbol(bEnd[1][0]) << printSymbol(bEnd[1][1])
			<< printSymbol(bEnd[1][2]) << "|" << endl;
	cout << "|" << printSymbol(b[2][0]) << printSymbol(b[2][1])
			<< printSymbol(b[2][2]) << "|" << "    " << "|"
			<< printSymbol(bEnd[2][0]) << printSymbol(bEnd[2][1])
			<< printSymbol(bEnd[2][2]) << "|" << endl;
	cout << " --- " << "    " << " --- " << endl;
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

vector<double> getNodeMove(Move move, bool reverse) {
	if (reverse) {
		vector<double> ret = vector<double>(9, 1.);
		ret[move.row * 3 + move.column] = 0.0;
		return ret;
	} else {
		vector<double> ret = vector<double>(9, 0);
		ret[move.row * 3 + move.column] = 1.0;
		return ret;
	}
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

Move getProbableMoveFromNode(vector<double> nodes) {
	Move ret(0, 0, 0);
	double sum = 0.;
	for (unsigned i = 0; i < nodes.size(); ++i)
		sum += nodes[i];
	double randomNum = ((double) std::rand() / RAND_MAX) * sum;
	sum = 0;
	for (unsigned i = 0; i < nodes.size(); ++i) {
		if (randomNum < sum + nodes[i]) {
			ret.row = i / 3;
			ret.column = i % 3;
			return ret;
		} else
			sum += nodes[i];
	}
#ifdef DEBUG
	assert(true);
#endif
	return ret;
}

vector<double>& norm(vector<double>& v) {
	double sum = 0.;
	for (unsigned i = 0; i < v.size(); ++i)
		sum += v[i];
	for (unsigned i = 0; i < v.size(); ++i)
		v[i] /= sum;
	return v;
}

void printBoard(Board &b) {
	cout << " --- " << "    " << " --- " << endl;
	cout << "|" << printSymbol(b[0][0]) << printSymbol(b[0][1])
			<< printSymbol(b[0][2]) << "|" << endl;
	cout << "|" << printSymbol(b[1][0]) << printSymbol(b[1][1])
			<< printSymbol(b[1][2]) << "|" << endl;
	cout << "|" << printSymbol(b[2][0]) << printSymbol(b[2][1])
			<< printSymbol(b[2][2]) << "|" << endl;
	cout << " --- " << endl;
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

double calcErrorSum(vector<double> a, vector<double> b) {
	double result = 0;
#ifdef DEBUG
	assert(a.size() == b.size());
#endif
	for (unsigned i = 0; i < a.size(); ++i)
		result += (a[i] - b[i]) * (a[i] - b[i]);
	return result;
}

ostream& operator<<(ostream& os, vector<double> v) {
	os << v[0];
	for (unsigned i = 1; i < v.size(); ++i) {
		os << ";" << v[i];
	}
	return os;
}
