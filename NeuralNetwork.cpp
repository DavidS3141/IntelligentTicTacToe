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
	// TODO Auto-generated destructor stub
}

