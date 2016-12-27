/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "constants.h"

#include <vector>
using std::vector;

class Neuron;
class Synapse;
typedef std::shared_ptr<Neuron> NeuronPtr;
typedef std::shared_ptr<Synapse> SynapsePtr;

class NeuralNetwork {
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

	vector<NeuronPtr> inputs;
	vector<NeuronPtr> hidden;
	vector<NeuronPtr> outputs;
	vector<SynapsePtr> synapses;

private:
	NeuronPtr getNeuron(unsigned idx) const;

	NeuronPtr bias;
};

#endif /* NEURALNETWORK_H_ */
