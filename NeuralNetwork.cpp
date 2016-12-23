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
#include "constants.h"

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int hiddenNodes) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	for (int i = 0; i < inNodes; ++i)
		inputs.push_back(new Neuron());
	for (int i = 0; i < hiddenNodes; ++i)
		hidden.push_back(new Neuron());
	for (int i = 0; i < outNodes; ++i)
		outputs.push_back(new Neuron());

	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < hiddenNodes; ++j)
			synapses.push_back(new Synapse(inputs[i], hidden[j]));
	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(new Synapse(inputs[i], outputs[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(new Synapse(hidden[i], outputs[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = i + 1; j < hiddenNodes; ++j)
			synapses.push_back(new Synapse(hidden[i], hidden[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		synapses.push_back(new Synapse(bias, hidden[i]));
	for (int i = 0; i < outNodes; ++i)
		synapses.push_back(new Synapse(bias, outputs[i]));
}

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int layers,
		int layerNodes) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	std::vector<Neuron*> prevLayer;
	std::vector<Neuron*> curLayer;

	for (int i = 0; i < inNodes; ++i) {
		inputs.push_back(new Neuron());
		curLayer.push_back(inputs.back());
	}

	for (int l = 0; l < layers; ++l) {
		prevLayer.clear();
		prevLayer = curLayer;
		curLayer.clear();

		for (int i = 0; i < layerNodes; ++i) {
			hidden.push_back(new Neuron());
			curLayer.push_back(hidden.back());
		}

		for (int i = 0; i < prevLayer.size(); ++i)
			for (int j = 0; j < layerNodes; ++j)
				synapses.push_back(new Synapse(prevLayer[i], curLayer[j]));
	}

	for (int i = 0; i < outNodes; ++i)
		outputs.push_back(new Neuron());

	for (int i = 0; i < curLayer.size(); ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(new Synapse(curLayer[i], outputs[j]));

	for (int i = 0; i < hidden.size(); ++i)
		synapses.push_back(new Synapse(bias, hidden[i]));
	for (int i = 0; i < outNodes; ++i)
		synapses.push_back(new Synapse(bias, outputs[i]));
}

NeuralNetwork::~NeuralNetwork() {

}

void NeuralNetwork::feedForward(vector<double> inp) {
	for (int neuronIdx = 0; neuronIdx < inp.size(); neuronIdx++) {
		inputs[neuronIdx]->setActivity(inp[neuronIdx]);
	}
	for (int neuronIdx = 0; neuronIdx < hidden.size(); neuronIdx++) {
		hidden[neuronIdx]->feedForward();
	}
	for (int neuronIdx = 0; neuronIdx < outputs.size(); neuronIdx++) {
		outputs[neuronIdx]->feedForward();
	}
}

void NeuralNetwork::simpleBackProp(vector<double> correctOutput, double scale) {
	for (int neuronIdx = outputs.size() - 1; neuronIdx >= 0; neuronIdx--) {
		outputs[neuronIdx]->delta =
				Neuron::sigmoidPrime(outputs[neuronIdx]->getNetInput())
						* (correctOutput[neuronIdx]
								- outputs[neuronIdx]->getActivity());
	}
	for (int neuronIdx = hidden.size() - 1; neuronIdx >= 0; neuronIdx--) {
		double tempSum = 0;
		for (Edge* curOut : hidden[neuronIdx]->childs) {
			tempSum += ((Synapse*) curOut)->weight
					* ((Neuron*) curOut->out)->delta;
		}
		hidden[neuronIdx]->delta = Neuron::sigmoidPrime(
				hidden[neuronIdx]->getNetInput()) * tempSum;
	}
	for (Synapse* cur : synapses) {
		cur->weightChange += scale * Synapse::learningRate
				* ((Neuron*) cur->in)->getActivity()
				* ((Neuron*) cur->out)->delta;
	}
}

void NeuralNetwork::backProp(vector<vector<double> > inputs,
		vector<vector<double> > correctOutputs, vector<double> scaling) {
	for (Synapse* cur : synapses)
		cur->weightChange = 0.;
#ifdef DEBUG
	assert(inputs.size()==correctOutputs.size());
	assert(inputs.size()==scaling.size());
#endif
	for (unsigned i = 0; i < inputs.size(); ++i) {
		feedForward(inputs[i]);
		simpleBackProp(correctOutputs[i], scaling[i]);
	}
	for (Synapse* cur : synapses) {
		cur->weight += cur->weightChange;
		cur->weightChange = 0.;
	}
}

vector<double> NeuralNetwork::evalInput(vector<double> inp) {
	feedForward(inp);
	return getOutput();
}

Move NeuralNetwork::getMove(Board board) {
	return getMoveNode(evalInput(getNodeBoard(board)));
}

vector<double> NeuralNetwork::getOutput() const {
	vector<double> output;
	for (int i = 0; i < outputs.size(); i++) {
		output.push_back(outputs[i]->getActivity());
	}
	return output;
}
