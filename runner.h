#ifndef RUNNER_H
#define RUNNER_H
#include <vector>

class Runner {
  Runner();

private:
  vector<Moves> moves;
  void runSimulation();

  vector<Moves> getMoves();
};
#endif
