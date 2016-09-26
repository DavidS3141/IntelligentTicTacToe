/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "NeuralNetwork.h"
#include "Neuron.h"

#define nodes neurons;

NeuralNetwork::NeuronalNetwork() {
	super();
}

NeuralNetwork::~NeuronalNetwork() {

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

void NeuralNetwork::backProp(vector<double> correctOutput) {
	for(int neuronIdx = outputs.size()-1; neuronIdx >= 0; neuronIdx--) {
		//double* deltas = new double[neurons.size()];
		//if(neuronIdx >= outputNeurons) {
		outputs[neuronIdx]->delta = sigmoidPrime(outputs[neuronIdx]->getNetInput()) *
				(correctOutput[neuronIdx] - outputs[neuronIdx]->getActivity());

		//}
	}
	for(int neuronIdx = hidden.size()-1; neuronIdx >= 0; neuronIdx--) {
		double tempSum = 0;
		for(Synapse* curOut : hidden[neuronIdx]->childs) {
			tempSum += curOut->weight * curOut->out->delta;
		}
		hidden[neuronIdx]->delta = sigmoidPrime(hidden[neuronIdx]->getNetInput()) *
				tempSum;
		//}
	}
	for(Synapse* cur : edges) {
		cur->weight += cur->learningRate * cur->in->getActivity() * cur->out->delta;
	}
}
