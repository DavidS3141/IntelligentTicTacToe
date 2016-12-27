#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#include "ai.h"
#include "human.h"
#include "logicPlayer.h"
#include "neuralNetwork.h"
#include "runner.h"
#include "synapse.h"

using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

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
	NeuralNetwork* nn;
	switch (c) {
	case 'c':
		cout << "How many hidden neurons?" << endl;
		unsigned hiddenNodes;
		cin >> hiddenNodes;
		nn = new NeuralNetwork(27, 9, hiddenNodes);
		break;
	case 'l':
		cout << "Neurons per Layer:" << endl;
		unsigned layerNodes;
		cin >> layerNodes;
		cout << "Layers:" << endl;
		unsigned layers;
		cin >> layers;
		nn = new NeuralNetwork(27, 9, layers, layerNodes);
		break;
	case 'f':
		cout << "Filename:" << endl;
		{
			string file;
			cin >> file;
			nn = new NeuralNetwork(file);
		}
		break;
	default:
		return 0;
	}

	Player* ai = new AI(nn);
	ofstream winSeries("winSeries.txt");
	while (true) {
		cout << "Human Player (h), Logic Player (l) or against itself (t):"
				<< endl;
		char c;
		cin >> c;
		Player* p2 = 0;
		switch (c) {
		case 'h':
			p2 = new Human();
			break;
		case 'l':
			p2 = new LogicPlayer();
			break;
		case 't':
			p2 = new AI(nn);
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
			if (logic)
				winSeries << run.getWinner() << endl;
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
				vector<double> outs = nn->evalInput(inputs.back());
				vector<double> correct;
				if (!run.isDraw()) {
					vector<double> multiply = getNodeMove(sit->second, true);
					for (unsigned j = 0; j < outs.size(); ++j)
						multiply[j] *= outs[j];
					correct = multiply;
				} else {
					vector<double> target = getNodeMove(sit->second);
					double max = 0.;
					double targetval = 0.;
					for (unsigned j = 0; j < outs.size(); ++j) {
						if (outs[j] > max)
							max = outs[j];
						targetval += outs[j] * target[j];
					}
					if (max == 0.)
						correct = target;
					else {
						for (unsigned j = 0; j < outs.size(); ++j) {
							correct.push_back(
									outs[j]
											+ (targetval - outs[j]) * outs[j]
													* targetval / max / max);
						}
					}
				}
				corrections.push_back(norm(correct));
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
	winSeries.close();
	return 0;
}