/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "NeuralNetwork.h"
#include "Neuron.h"

NeuralNetwork::NeuronalNetwork() {
	super();
}

NeuralNetwork::~NeuronalNetwork() {

}

void NeuralNetwork::feedForward(vector<double> input) {
	for(int neuronId=0; neuronId < input.size(); neuronId++) {
		neurons[neuronId]->setActivity(input[neuronId]);
	}
	for (int neuronId=input.size(); neuronId < neurons.size(); neuronId++) {
		neurons[neuronId]->feedForward();
	}
}

void NeuralNetwork::backProp(vector<double> correctOutput) {
	for(int neuronId = neurons.size()-1; neuronId >= 0; neuronId--) {
		double* deltas = new double[neurons.size()];
		if(neuronId >= outputNeurons) {
			deltas[neuronId] = sigmoidPrime(neurons[neuronId]->getNetInput()) *
					(correctOutput[neuronId-outputNeurons] - neurons[neuronId]->getActivity());

		}
		else {
			double tempSum = 0;
			for(Synapse* curOut : neurons[neuronId]->outSynapses) {
				tempSum += curOut->weight * deltas[curOut->out->getId()];
			}
			deltas[neuronId] = sigmoidPrime(neurons[neuronId]->getNetInput()) *
					tempSum;
		}
	}
	for(Synapse* cur : synapses) {
		cur->weight += cur->learningRate * cur->in->getActivity() * deltas[cur->out->getId()];
	}
}
