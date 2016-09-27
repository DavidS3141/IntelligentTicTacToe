#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <iostream>
#include <tuple>
#include <utility>

struct Move;

using std::vector;
using namespace std;

typedef vector<vector<short>> Board;
//typedef std::tuple<short, short, short> Move;
typedef std::pair<Board, Move> State;
const short cross = 1;
const short circle = 2;

struct Move {
	short row, column;
	short player;

	Move() { }
	Move(short row, short column, short player) : row(row), column(column), player(player) { }
};

namespace constants {

const std::vector<std::vector<std::vector<short>>>winningPositions = {
	{	{	0, 0}, {1, 0}, {2, 0}}, { {0, 1}, {1, 1}, {2, 1}},
	{	{	0, 2}, {1, 2}, {2, 2}}, { {0, 0}, {0, 1}, {0, 2}},
	{	{	1, 0}, {1, 1}, {1, 2}}, { {2, 0}, {2, 1}, {2, 2}},
	{	{	0, 0}, {1, 1}, {2, 2}}, { {0, 2}, {1, 1}, {2, 0}},
};

const Board empytBoard = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

const char printSymbol(int i);
void printMove(Board &b, Move &m);

};

vector<double> getNodeBoard(Board board);
vector<double> getNodeMove(Move move);
Board getBoardNode(vector<double> nodes);
Move getMoveNode(vector<double> nodes);

#endif // CONSTANTS_H
