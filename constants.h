#include <vector>
using std::vector;

typedef vector<vector<short>> Board;
const char cross = 1;
const char circle = 2;

namespace constants {

const std::vector<std::vector<std::vector<short>>> winningPositions = {
    {{0, 0}, {1, 0}, {2, 0}}, {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}}, {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}}, {{2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {1, 1}, {2, 2}}, {{0, 2}, {1, 1}, {2, 0}},
};

const Board empytBoard = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
};
