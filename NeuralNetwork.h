/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "graph.h"

class Neuron;
class Synapse;

class NeuralNetwork : public Graph {
public:
	NeuralNetwork(int inNodes, int outNodes, int hiddenNodes);
	virtual ~NeuralNetwork();

	vector<Neuron*> inputs;
	vector<Neuron*> hidden;
	vector<Neuron*> outputs;
	vector<Synapse*> synapses;

};

#endif /* NEURALNETWORK_H_ */
