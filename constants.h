#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

using std::vector;

typedef vector<vector<short>> Board;
typedef std::tuple<short, short, short> Move;
typedef std::pair<Board, Move> State;
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

#endif // CONSTANTS_H
