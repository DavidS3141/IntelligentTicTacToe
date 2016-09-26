#include <iostream>

#include "NeuralNetwork.h"
#include "runner.h"

using namespace std;

int main() {
	NeuralNetwork* nn = new NeuralNetwork(27, 9, 100);
	while (true) {
		int numSims;
		cin >> numSims;
		if(numSims==0)
			break;
		for (int i = 0; i < numSims; ++i) {
			Runner run(nn);
			vector<State> goodies = run.getGoodStates();
			for (auto state : goodies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), true); //TODO check with Marvin if correct parameter
			}
			vector<State> baddies = run.getBadStates();
			for (auto state : baddies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), false); //TODO check with Marvin if correct parameter
			}
			if(i==numSims-1)
				run.dump();
		}
	}
	return 0;
}
