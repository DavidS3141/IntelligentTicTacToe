#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <iostream>
#include <tuple>
#include <utility>

struct Move;

using std::vector;
using namespace std;

typedef vector<vector<int> > Board;
typedef std::pair<Board, Move> State;
const int cross = 1;
const int circle = 2;

struct Move {
	int row, column;
	int player;

	Move() :
			row(0), column(0), player(0) {
	}
	Move(int row, int column, int player) :
			row(row), column(column), player(player) {
	}
};

template<typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

const vector<vector<vector<int> > > winningPositions = { { { 0, 0 }, { 1, 0 }, {
		2, 0 } }, { { 0, 1 }, { 1, 1 }, { 2, 1 } }, { { 0, 2 }, { 1, 2 },
		{ 2, 2 } }, { { 0, 0 }, { 0, 1 }, { 0, 2 } }, { { 1, 0 }, { 1, 1 }, { 1,
		2 } }, { { 2, 0 }, { 2, 1 }, { 2, 2 } },
		{ { 0, 0 }, { 1, 1 }, { 2, 2 } }, { { 0, 2 }, { 1, 1 }, { 2, 0 } }, };

const Board empytBoard = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

const char printSymbol(int i);
void printMove(Board &b, Move &m);

vector<double> getNodeBoard(Board board);
vector<double> getNodeMove(Move move);
Board getBoardNode(vector<double> nodes);
Move getMoveNode(vector<double> nodes);

void printBoard(Board &b);

#endif // CONSTANTS_H
