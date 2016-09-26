#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

using std::vector;

typedef vector<vector<short>> Board;
typedef tuple<short, short, short> Move;
typedef pair<Board, Move> State;
const short cross = 1;
const short circle = 2;

namespace constants {

const std::vector<std::vector<std::vector<short>>> winningPositions = {
    {{0, 0}, {1, 0}, {2, 0}}, {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}}, {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}}, {{2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {1, 1}, {2, 2}}, {{0, 2}, {1, 1}, {2, 0}},
};

const Board empytBoard = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
};

#endif CONSTANTS_H
