/*
 * Neuron.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "Neuron.h"

#include <cmath>

Neuron::Neuron() {
	// TODO Auto-generated constructor stub

}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

double Neuron::sum(vector<double> x) const {
	double sum = 0;
	for(double cur : x) {
		sum += cur;
	}
}

void Neuron::feedForward() {
	double propagation = this->getNetInput();
	this->activity = sigmoid(propagation);
}

double Neuron::getNetInput() {
	vector<double> inp;
	for(Synapse* input : parents) {
		inp.push_back(input->getSignal());
	}
	return sum(inp);
}

double Neuron::sigmoid(double x) {
	return x/(1.+std::abs(x));
}

double Neuron::sigmoidPrime(double x) {
	return std::pow(1.+std::abs(x),-2);
}
