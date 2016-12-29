#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "ai.h"
#include "human.h"
#include "loadingBar.h"
#include "logicPlayer.h"
#include "neuralNetwork.h"
#include "runner.h"
#include "synapse.h"

using namespace std;

//TODO organize includes, const

int main() {
	//set random seed
	int randomMode;
	cout << "Type '-1' for random mode or type seed for random engine:" << endl;
	cin >> randomMode;
	if (randomMode < 0) {
		unsigned seed = time(NULL);
		cout << "Seed is:" << seed << endl;
		srand(seed);
	} else
		srand(randomMode);

	//construct neural network
	cout
			<< "Network: completely connected (c), layered (l) or load from file (f):"
			<< endl;
	char c;
	cin >> c;
	shared_ptr<NeuralNetwork> nn;
	switch (c) {
	case 'c':
		cout << "How many hidden neurons?" << endl;
		unsigned hiddenNodes;
		cin >> hiddenNodes;
		nn = shared_ptr<NeuralNetwork>(new NeuralNetwork(27, 9, hiddenNodes));
		break;
	case 'l':
		cout << "Neurons per Layer:" << endl;
		unsigned layerNodes;
		cin >> layerNodes;
		cout << "Layers:" << endl;
		unsigned layers;
		cin >> layers;
		nn = shared_ptr<NeuralNetwork>(
				new NeuralNetwork(27, 9, layers, layerNodes));
		break;
	case 'f':
		cout << "Filename:" << endl;
		{
			string file;
			cin >> file;
			nn = shared_ptr<NeuralNetwork>(new NeuralNetwork(file));
		}
		break;
	default:
		return 0;
	}

	shared_ptr<Player> ai(new AI(nn));
	ofstream winSeries("winSeries.txt");

	while (true) {
		cout << "Human Player (h), Logic Player (l) or against itself (t):"
				<< endl;
		char c;
		cin >> c;
		bool logic = false;
		bool train = false;
		PlayerPtr p2 = 0;
		switch (c) {
		case 'h':
			p2 = PlayerPtr(new Human());
			break;
		case 'l':
			logic = true;
			p2 = PlayerPtr(new LogicPlayer());
			break;
		case 't':
			train = true;
			p2 = PlayerPtr(new AI(nn));
			break;
		default:
			return 0;
		}
		cout << "Learning Rate:" << endl;
		cin >> Synapse::learningRate;
		cout << "Number of Games:" << endl;
		int numSims;
		cin >> numSims;
		if (numSims <= 0)
			return 0;
		LoadingBar lb("Simulation is running");
		lb.set(numSims);
		for (int i = 0; i < numSims; ++i) {
			Runner run(ai, p2);
			if (logic) {
				switch (run.getWinner()) {
				case 1:
					winSeries << 1 << endl;
					break;
				case 2:
					winSeries << 0 << endl;
					break;
				case -1:
					winSeries << 0.5 << endl;
					break;
				default:
					winSeries << -100 << endl;
				}
			} else if (train) {
				winSeries << run.getMoves().size() / 9. << endl;
			}
			vector<State> goodies = run.getGoodStates();
			for (auto state : goodies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), true);
			}
			vector<State> baddies = run.getBadStates();
			for (auto state : baddies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), false);
			}
			++lb;
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
		nn->saveNetwork("network.nn");
	}
	winSeries.close();
	return 0;
}
