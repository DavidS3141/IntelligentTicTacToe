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
class NeuralNetwork : public Graph {
private:
	Neuron* bias;
public:
	NeuralNetwork(int inNodes, int outNodes, int hiddenNodes);
	virtual ~NeuralNetwork();

	void feedForward(vector<double> input);
	void backProp(vector<double> correctOutput, bool correct);

	vector<double> getOutput() const;
	vector<double> evalInput(vector<double> input);
	Move getMove(Board board);

	vector<Neuron*> inputs;
	vector<Neuron*> hidden;
	vector<Neuron*> outputs;
	vector<Synapse*> synapses;

};

#endif /* NEURALNETWORK_H_ */
