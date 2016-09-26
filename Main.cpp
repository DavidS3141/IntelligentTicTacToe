#include <iostream>

#include "NeuralNetwork.h"
#include "runner.h"

using namespace std;

int main() {
  NeuralNetwork *nn = new NeuralNetwork(27, 100, 9);
  while (true) {
    int numSims;
    cin >> numSims;
    for (int i = 0; i < numSims; ++i) {
      Runner run(nn);
      vector<State> goodies = run.getGoodStates();
      for (auto state : goodies) {
        nn->feedForward(getNodeBoard(state.first));
        nn->backProp(getNodeMove(state.second),
                     true); // TODO check with Marvin if correct parameter
      }
    }
  }
  return 0;
}
