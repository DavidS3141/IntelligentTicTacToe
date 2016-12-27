#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ai.h"
#include "human.h"
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
	while (true) {
		cout << "Human Player (h), Logic Player (l) or against itself (t):"
				<< endl;
		char c;
		cin >> c;
		PlayerPtr p2 = 0;
		switch (c) {
		case 'h':
			p2 = PlayerPtr(new Human());
			break;
		case 'l':
			p2 = PlayerPtr(new LogicPlayer());
			break;
		case 't':
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
		cout << "|                    |" << endl << " ";
		int progressCounter = 0;
		for (int i = 0; i < numSims; ++i) {
			while ((i + 1) * 20 > numSims * progressCounter) {
				cout << "#" << flush;
				++progressCounter;
			}
			Runner run(ai, p2);
			// training session
			vector<vector<double> > inputs;
			vector<vector<double> > corrections;
			vector<double> scaling;
			vector<State> goodies = run.getGoodStates();
			double scale = 1.;
			double factor = 0.1;
			for (auto sit = goodies.rbegin(); sit != goodies.rend(); ++sit) {
				inputs.push_back(getNodeBoard(sit->first));
				corrections.push_back(getNodeMove(sit->second));
				scaling.push_back(scale);
				scale *= factor;
			}
			vector<State> baddies = run.getBadStates();
			scale = 1.;
			for (auto sit = baddies.rbegin(); sit != baddies.rend(); ++sit) {
				inputs.push_back(getNodeBoard(sit->first));
				nn->feedForward(inputs.back());
				vector<double> outs = nn->getOutput();
				vector<double> multiply = getNodeMove(sit->second, true);
				double sum = 0;
				for (unsigned j = 0; j < outs.size(); ++j) {
					multiply[j] *= outs[j];
					sum += multiply[j];
				}
				for (unsigned j = 0; j < outs.size(); ++j)
					multiply[j] /= sum;
				corrections.push_back(multiply);
				scaling.push_back(scale);
				scale *= factor;
			}
			nn->backProp(inputs, corrections, scaling);
			//end training session
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
	return 0;
}
