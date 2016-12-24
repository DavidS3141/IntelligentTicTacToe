#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#include "ai.h"
#include "human.h"
#include "logicPlayer.h"
#include "NeuralNetwork.h"
#include "runner.h"
#include "Synapse.h"

using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

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
	ofstream winSeries("winSeries.txt");
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
		delete p2;
	}
	winSeries.close();
	return 0;
}
