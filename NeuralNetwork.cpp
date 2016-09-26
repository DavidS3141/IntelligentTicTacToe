/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "NeuralNetwork.h"
#include "Neuron.h"
#include "Synapse.h"

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int hiddenNodes){
	for(int i=0;i<inNodes;++i)
		inputs.push_back(new Neuron(i));
	for(int i=0;i<hiddenNodes;++i)
		hidden.push_back(new Neuron(i+inNodes));
	for(int i=0;i<outNodes;++i)
		outputs.push_back(new Neuron(i+inNodes+hiddenNodes));

	int counter=0;
	for(int i=0;i<inNodes;++i)
		for(int j=0;j<hiddenNodes;++j){
			synapses.push_back(new Synapse(counter,inputs[i],hidden[j]));
			++counter;
		}
	for(int i=0;i<inNodes;++i)
		for(int j=0;j<outNodes;++j){
			synapses.push_back(new Synapse(counter,inputs[i],outputs[j]));
			++counter;
		}
	for(int i=0;i<hiddenNodes;++i)
		for(int j=0;j<outNodes;++j){
			synapses.push_back(new Synapse(counter,hidden[i],outputs[j]));
			++counter;
		}
	for(int i=0;i<hiddenNodes;++i)
		for(int j=i+1;j<hiddenNodes;++j){
			synapses.push_back(new Synapse(counter,hidden[i],hidden[j]));
			++counter;
		}
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
	for(Synapse* cur : synapses) {
		cur->weight += cur->learningRate * cur->in->getActivity() * cur->out->delta;
	}
}
