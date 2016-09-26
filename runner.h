#ifndef RUNNER_H
#define RUNNER_H
#include "NeuralNetwork.h"
#include "TicTacToe.h"
#include <vector>

class Runner {
  Runner(NeuralNetwork *);

  vector<State> getBadStates();
  vector<State> getGoodStates();

private:
  short endState;
  TicTacToe game;
  vector<Moves> moves;
  NeuronalNetwork *const network;
  void runSimulation();
};
#endif
