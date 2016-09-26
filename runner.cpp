#include "runner.h"

Runner::Runner(NeuralNetwork *n) : network(n) { runSimulation(); }

void Runner::runSimulation() {
  short player = 1;
  short row, column;
  short state = 0;
  while (!state) {
    network->getMove(game->getBoard(player), row, column);
    moves.push_back(std::make_tuple(row, column, player));
    state = game->makeMove(row, column, player);
    player = (player % 2) + 1;
  }
  endState = state;
}

vector<State> Runner::getGoodStates() {
  vector<State> states = std::vector<State>();
  TicTacToe pseudoGame();
  for (auto move : moves) {
    if (player == endState | endState == -1 && player == circle)
      states.push_back(std::make_pair(pseudoGame.getBoard(player), move));
    pseudoGame.makeMove(move[0], move[1], move[2]);
  }
  return states;
}

vector<State> Runner::getBadStates() {
  vector<State> states = std::vector<State>();
  TicTacToe pseudoGame();
  for (auto move : moves) {
    if (player != endState | endState == -1 && player == cross)
      states.push_back(std::make_pair(pseudoGame.getBoard(player), move));
    pseudoGame.makeMove(move[0], move[1], move[2]);
  }
  return states;
}
