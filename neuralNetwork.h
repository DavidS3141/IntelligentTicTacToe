/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "graph.h"

#include <vector>
#include "constants.h"

class Neuron;
class Synapse;

using std::vector;

class NeuralNetwork: public Graph {
public:
	NeuralNetwork(string s);
	NeuralNetwork(int inNodes, int outNodes, int hiddenNodes);
	NeuralNetwork(int inNodes, int outNodes, int layers, int layerNodes);
	virtual ~NeuralNetwork();

	void feedForward(vector<double> input);
	void backProp(vector<double> correctOutput, bool correct);

	vector<double> getOutput() const;
	vector<double> evalInput(vector<double> input);
	Move getMove(Board board);

	void saveNetwork(string s) const;

	vector<Neuron*> inputs;
	vector<Neuron*> hidden;
	vector<Neuron*> outputs;
	vector<Synapse*> synapses;

private:
	Neuron* getNeuron(unsigned idx) const;

	Neuron* bias;
};

#endif /* NEURALNETWORK_H_ */
