#include "runner.h"

Runner::Runner(NeuralNetwork *n) : network(n) { runSimulation(); }

void Runner::runSimulation() {
  short player = 1;
  Move move;
  short state = 0;
  while (!state) {
    move = network->getMove(game.getBoard(player));
    moves.push_back(
        std::make_tuple(std::get<0>(move), std::get<1>(move), player));
    state = game.makeMove(row, column, player);
    player = (player % 2) + 1;
  }
  endState = state;
}

vector<State> Runner::getGoodStates() {
  vector<State> states = std::vector<State>();
  TicTacToe pseudoGame;
  for (auto move : moves) {
    if (std::get<2>(move) == endState ||
        (endState == -1 && std::get<2>(move) == circle))
      states.push_back(
          std::make_pair(pseudoGame.getBoard(std::get<2>(move)), move));
    pseudoGame.makeMove(std::get<0>(move), std::get<1>(move),
                        std::get<2>(move));
  }
  return states;
}

vector<State> Runner::getBadStates() {
  vector<State> states = std::vector<State>();
  TicTacToe pseudoGame;
  for (auto move : moves) {
    if (std::get<2>(move) != endState ||
        (endState == -1 && std::get<2>(move) == cross))
      states.push_back(
          std::make_pair(pseudoGame.getBoard(std::get<2>(move)), move));
    pseudoGame.makeMove(std::get<0>(move), std::get<1>(move),
                        std::get<2>(move));
  }
  return states;
}
