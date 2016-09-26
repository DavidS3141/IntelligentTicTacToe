#include "tictactoe.h"
#include <stdexcept>

Board TicTacToe::getBoard() { return board; }

int TicTacToe::makeMove(int row, int column, int player) {
  if (!(player == cross || player == circle))
    throw std::runtime_error("Player not defined!");
  if (board[row][column] != 0)
    return (player == circle) ? cross : circle;
  else
    board[row][column] = player;
  return gameEnded();
}

int TicTacToe::gameEnded() {
  short player;
  for (auto final : constants::winningPositions)
    if (board[final[0][0]][final[0][1]] == board[final[1][0]][final[1][1]] &&
        board[final[1][0]][final[1][1]] == board[final[2][0]][final[2][1]])
      return board[final[0][0]][final[0][1]];
  return 0;
}
