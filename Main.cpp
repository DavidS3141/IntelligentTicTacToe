#include <iostream>

#include "NeuralNetwork.h"
#include "runner.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	int randomMode;
	cout << "Interesting seeds:" << endl;
	cout << "1474978835" << endl;
	cout << "Type '-1' for random mode or type seed for random engine:" << endl;
	cin >> randomMode;
	if (randomMode < 0) {
		unsigned seed = time(NULL);
		cout << "Seed is:" << seed << endl;
		srand(seed);
	} else
		srand(randomMode);
	NeuralNetwork* nn = new NeuralNetwork(27, 9, 100);
	while (true) {
		int numSims;
		cin >> numSims;
		if (numSims <= 0)
			break;
		cout << "|                    |" << endl << " ";
		int progressCounter = 0;
		for (int i = 0; i < numSims; ++i) {
			while ((i+1) * 20 > numSims * progressCounter) {
				cout << "#" << flush;
				++progressCounter;
			}
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
			if (i == numSims - 1) {
				cout << endl;
				run.dump();
			}
		}
	}
	return 0;
}
