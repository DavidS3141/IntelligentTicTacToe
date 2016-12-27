/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "neuralNetwork.h"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "constants.h"
#include "neuron.h"
#include "synapse.h"

NeuralNetwork::NeuralNetwork(string s) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	ifstream ifs(s);
	unsigned inNodes, hiddenNodes, outNodes;
	ifs >> inNodes >> s >> hiddenNodes >> s >> outNodes;
	getline(ifs, s);

	for (unsigned i = 0; i < inNodes; ++i)
		inputs.push_back(NeuronPtr(new Neuron()));
	for (unsigned i = 0; i < hiddenNodes; ++i)
		hidden.push_back(NeuronPtr(new Neuron()));
	for (unsigned i = 0; i < outNodes; ++i)
		outputs.push_back(NeuronPtr(new Neuron()));

	for (unsigned start = 0; start <= inNodes + hiddenNodes + outNodes;
			++start) {
		getline(ifs, s);
		vector<string> vs;
		split(s, ';', vs);
#ifdef DEBUG
		assert(vs.size()==1+inNodes+hiddenNodes+outNodes);
#endif
		for (unsigned end = 0; end < vs.size(); ++end) {
			if (vs[end][2] != ' ') {
				double flt = atof(vs[end].data());
				NeuronPtr startN = getNeuron(start);
				NeuronPtr endN = getNeuron(end);
				synapses.push_back(SynapsePtr(new Synapse(startN, endN)));
				synapses.back()->weight = flt;
			}
		}
	}

	ifs.close();
}

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int hiddenNodes) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	for (int i = 0; i < inNodes; ++i)
		inputs.push_back(NeuronPtr(new Neuron()));
	for (int i = 0; i < hiddenNodes; ++i)
		hidden.push_back(NeuronPtr(new Neuron()));
	for (int i = 0; i < outNodes; ++i)
		outputs.push_back(NeuronPtr(new Neuron()));

	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < hiddenNodes; ++j)
			synapses.push_back(SynapsePtr(new Synapse(inputs[i], hidden[j])));
	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(SynapsePtr(new Synapse(inputs[i], outputs[j])));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(SynapsePtr(new Synapse(hidden[i], outputs[j])));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = i + 1; j < hiddenNodes; ++j)
			synapses.push_back(SynapsePtr(new Synapse(hidden[i], hidden[j])));
	for (int i = 0; i < hiddenNodes; ++i)
		synapses.push_back(SynapsePtr(new Synapse(bias, hidden[i])));
	for (int i = 0; i < outNodes; ++i)
		synapses.push_back(SynapsePtr(new Synapse(bias, outputs[i])));
}

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int layers,
		int layerNodes) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	std::vector<NeuronPtr> prevLayer;
	std::vector<NeuronPtr> curLayer;

	for (int i = 0; i < inNodes; ++i) {
		inputs.push_back(NeuronPtr(new Neuron()));
		curLayer.push_back(inputs.back());
	}

	for (int l = 0; l < layers; ++l) {
		prevLayer.clear();
		prevLayer = curLayer;
		curLayer.clear();

		for (int i = 0; i < layerNodes; ++i) {
			hidden.push_back(NeuronPtr(new Neuron()));
			curLayer.push_back(hidden.back());
		}

		for (int i = 0; i < prevLayer.size(); ++i)
			for (int j = 0; j < layerNodes; ++j)
				synapses.push_back(
						SynapsePtr(new Synapse(prevLayer[i], curLayer[j])));
	}

	for (int i = 0; i < outNodes; ++i)
		outputs.push_back(NeuronPtr(new Neuron()));

	for (int i = 0; i < curLayer.size(); ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(
					SynapsePtr(new Synapse(curLayer[i], outputs[j])));

	for (int i = 0; i < hidden.size(); ++i)
		synapses.push_back(SynapsePtr(new Synapse(bias, hidden[i])));
	for (int i = 0; i < outNodes; ++i)
		synapses.push_back(SynapsePtr(new Synapse(bias, outputs[i])));
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

void NeuralNetwork::backProp(vector<double> correctOutput, bool correct) {
	for (int neuronIdx = outputs.size() - 1; neuronIdx >= 0; neuronIdx--) {
		//double* deltas = new double[neurons.size()];
		//if(neuronIdx >= outputNeurons) {
		if (correct) {
			outputs[neuronIdx]->delta = Neuron::sigmoidPrime(
					outputs[neuronIdx]->getNetInput())
					* (correctOutput[neuronIdx]
							- outputs[neuronIdx]->getActivity());
		} else {
			outputs[neuronIdx]->delta =
					Neuron::sigmoidPrime(outputs[neuronIdx]->getNetInput())
							* (correctOutput[neuronIdx]
									- outputs[neuronIdx]->getActivity()
									- sgn(
											correctOutput[neuronIdx]
													- outputs[neuronIdx]->getActivity()));
		}
		//}
	}
	for (int neuronIdx = hidden.size() - 1; neuronIdx >= 0; neuronIdx--) {
		double tempSum = 0;
		for (SynapsePtr curOut : hidden[neuronIdx]->getChilds()) {
			tempSum += curOut->weight * curOut->getOut()->delta;
		}
		hidden[neuronIdx]->delta = Neuron::sigmoidPrime(
				hidden[neuronIdx]->getNetInput()) * tempSum;
		//}
	}
	for (SynapsePtr cur : synapses) {
		cur->weight += /*cur->learningRate*/Synapse::learningRate
				* cur->getIn()->getActivity() * cur->getOut()->delta;
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

void NeuralNetwork::saveNetwork(string s) const {
	/* file format:
	 * 1. line: inputs, hiddens, outputs (numbering goes from 1 to (inputs+hiddens+outputs), 0 is bias)
	 * following lines: matrix representation of Synapse weights
	 *
	 * format of floating numbers: (+-)x.(DECIMALS)e(+-)xx, in total always 7+DECIMALS chars (+- is only one of them)
	 */
	ofstream os(s);
	os << inputs.size() << " ; " << hidden.size() << " ; " << outputs.size()
			<< endl;
	os << setprecision(DECIMALS) << fixed << scientific;
	for (unsigned row = 0;
			row <= inputs.size() + hidden.size() + outputs.size(); ++row) {
		NeuronPtr start = getNeuron(row);
		for (unsigned col = 0;
				col <= inputs.size() + hidden.size() + outputs.size(); ++col) {
			bool found = false;
			for (unsigned i = 0; i < start->getChilds().size(); ++i) {
				if (start->getChilds()[i]->getOut()->getID() == col) {
					found = true;
					if (synapses[start->getChilds()[i]->getID()]->weight > 0)
						os << "+";
					os << synapses[start->getChilds()[i]->getID()]->weight;
				}
			}
			if (!found)
				os << string(DECIMALS + 7, ' ');
			if (col < inputs.size() + hidden.size() + outputs.size())
				os << " ; ";
			else
				os << endl;
		}
	}
	os.close();
}

NeuronPtr NeuralNetwork::getNeuron(unsigned idx) const {
	if (idx == 0)
		return bias;
	idx -= 1;
	if (idx < inputs.size())
		return inputs[idx];
	idx -= inputs.size();
	if (idx < hidden.size())
		return hidden[idx];
	idx -= hidden.size();
	if (idx < outputs.size())
		return outputs[idx];
#ifdef DEBUG
	assert(true);
#endif
	return bias;
}
