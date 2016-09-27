/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "NeuralNetwork.h"

#include <cmath>

#include "Neuron.h"
#include "Synapse.h"

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int hiddenNodes){
	for(int i=0;i<inNodes;++i)
		inputs.push_back(new Neuron());
	for(int i=0;i<hiddenNodes;++i)
		hidden.push_back(new Neuron());
	for(int i=0;i<outNodes;++i)
		outputs.push_back(new Neuron());

	for(int i=0;i<inNodes;++i)
		for(int j=0;j<hiddenNodes;++j)
			synapses.push_back(new Synapse(inputs[i],hidden[j]));
	for(int i=0;i<inNodes;++i)
		for(int j=0;j<outNodes;++j)
			synapses.push_back(new Synapse(inputs[i],outputs[j]));
	for(int i=0;i<hiddenNodes;++i)
		for(int j=0;j<outNodes;++j)
			synapses.push_back(new Synapse(hidden[i],outputs[j]));
	for(int i=0;i<hiddenNodes;++i)
		for(int j=i+1;j<hiddenNodes;++j)
			synapses.push_back(new Synapse(hidden[i],hidden[j]));
}

NeuralNetwork::~NeuralNetwork() {

}

void NeuralNetwork::feedForward(vector<double> inp) {
	for(int neuronIdx=0; neuronIdx < inp.size(); neuronIdx++) {
		inputs[neuronIdx]->setActivity(inp[neuronIdx]);
	}
	for(int neuronIdx=0; neuronIdx < hidden.size(); neuronIdx++) {
		hidden[neuronIdx]->feedForward();
	}
	for(int neuronIdx=0; neuronIdx < outputs.size(); neuronIdx++) {
		outputs[neuronIdx]->feedForward();
	}
	/*for (int neuronId=input.size(); neuronId < neurons.size(); neuronId++) {
		((Neuron*)neurons[neuronId])->feedForward();
	}*/
}

void NeuralNetwork::backProp(vector<double> correctOutput, bool correct) {
	for(int neuronIdx = outputs.size()-1; neuronIdx >= 0; neuronIdx--) {
		//double* deltas = new double[neurons.size()];
		//if(neuronIdx >= outputNeurons) {
		if(correct) {
			outputs[neuronIdx]->delta = Neuron::sigmoidPrime(outputs[neuronIdx]->getNetInput()) *
					(correctOutput[neuronIdx] - outputs[neuronIdx]->getActivity());
		}
		else {
			outputs[neuronIdx]->delta = Neuron::sigmoidPrime(outputs[neuronIdx]->getNetInput()) *
					(std::abs(correctOutput[neuronIdx] - outputs[neuronIdx]->getActivity()) - .7);
		}
		//}
	}
	for(int neuronIdx = hidden.size()-1; neuronIdx >= 0; neuronIdx--) {
		double tempSum = 0;
		for(Edge* curOut : hidden[neuronIdx]->childs) {
			tempSum += ((Synapse*)curOut)->weight * ((Neuron*)curOut->out)->delta;
		}
		hidden[neuronIdx]->delta = Neuron::sigmoidPrime(hidden[neuronIdx]->getNetInput()) *
				tempSum;
		//}
	}
	for(Synapse* cur : synapses) {
		cur->weight += /*cur->learningRate*/Synapse::learningRate * ((Neuron*)cur->in)->getActivity() * ((Neuron*)cur->out)->delta;
	}
}

vector<double> NeuralNetwork::getOutput(vector<double> inp) {
	feedForward(inp);
	vector<double> output;
	for(int i=0; i<outputs.size(); i++) {
		output.push_back(outputs[i]->getActivity());
	}
	return output;
}

Move NeuralNetwork::getMove(Board board) {
	return getMoveNode(getOutput(getNodeBoard(board)));
}
