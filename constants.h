#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <iostream>

using std::vector;
using namespace std;

typedef vector<vector<short>> Board;
typedef std::tuple<short, short, short> Move;
typedef std::pair<Board, Move> State;
const short cross = 1;
const short circle = 2;

namespace constants {

const std::vector<std::vector<std::vector<short>>>winningPositions = {
	{	{	0, 0}, {1, 0}, {2, 0}}, { {0, 1}, {1, 1}, {2, 1}},
	{	{	0, 2}, {1, 2}, {2, 2}}, { {0, 0}, {0, 1}, {0, 2}},
	{	{	1, 0}, {1, 1}, {1, 2}}, { {2, 0}, {2, 1}, {2, 2}},
	{	{	0, 0}, {1, 1}, {2, 2}}, { {0, 2}, {1, 1}, {2, 0}},
};

const Board empytBoard = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

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

};

#endif //CONSTANTS_H
