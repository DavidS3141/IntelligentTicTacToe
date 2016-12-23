/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <vector>
#include "graph.h"
#include "constants.h"

class Neuron;
class Synapse;

using namespace std;
class NeuralNetwork: public Graph {
public:
	NeuralNetwork(int inNodes, int outNodes, int hiddenNodes);
	NeuralNetwork(int inNodes, int outNodes, int layers, int layerNodes);
	virtual ~NeuralNetwork();

	void feedForward(vector<double> input);
	void backProp(vector<vector<double> > inputs,
			vector<vector<double> > correctOutputs, vector<double> scaling);

	vector<double> getOutput() const;
	vector<double> evalInput(vector<double> input);
	Move getMove(Board board);

	vector<Neuron*> inputs;
	vector<Neuron*> hidden;
	vector<Neuron*> outputs;
	vector<Synapse*> synapses;

private:
	void simpleBackProp(vector<double> correctOutputs, double scale = 1.0);

	Neuron* bias;
};

#endif /* NEURALNETWORK_H_ */
