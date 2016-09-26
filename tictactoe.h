#include "constants.h"
#include <iostream>

class TicTacToe {
  TicTacToe() : board(constants::empytBoard){};

  int makeMove(int row, int column, int player);
  Board getBoard();
  int gameEnded();
  bool boardFull();

private:
  Board board;
};
