#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ai.h"
#include "human.h"
#include "logicPlayer.h"
#include "NeuralNetwork.h"
#include "runner.h"
#include "Synapse.h"

using namespace std;

int main() {
	int randomMode;
	cout << "Type '-1' for random mode or type seed for random engine:" << endl;
	cin >> randomMode;
	if (randomMode < 0) {
		unsigned seed = time(NULL);
		cout << "Seed is:" << seed << endl;
		srand(seed);
	} else
		srand(randomMode);
	//NeuralNetwork* nn = new NeuralNetwork(27, 9, 30);
	NeuralNetwork* nn = new NeuralNetwork(27, 9, 3, 54);
	Player* ai = new AI(nn);
	while (true) {
		cout << "Human Player (h), Logic Player (l) or against itself (t):"
				<< endl;
		char c;
		cin >> c;
		bool human = (c == 'h');
		bool logic = (c == 'l');
		bool train = (c == 't');
		Player* p2 = 0;
		if (human)
			p2 = new Human();
		else if (logic)
			p2 = new LogicPlayer();
		else
			p2 = new AI(nn);
		cout << "Learning Rate:" << endl;
		cin >> Synapse::learningRate;
		cout << "Number of Games:" << endl;
		int numSims;
		cin >> numSims;
		if (numSims <= 0)
			break;
		cout << "|                    |" << endl << " ";
		int progressCounter = 0;
		for (int i = 0; i < numSims; ++i) {
			while ((i + 1) * 20 > numSims * progressCounter) {
				cout << "#" << flush;
				++progressCounter;
			}
			Runner run(ai, p2);
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
				vector<double> out = nn->getOutput();
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						int idx = i * 3 + j;
						cout << out[idx] << "\t";
					}
					cout << endl;
				}
			}
		}
		delete p2;
		nn->saveNetwork("network.nn");
	}
	return 0;
}
