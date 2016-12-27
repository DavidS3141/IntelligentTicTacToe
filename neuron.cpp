/*
 * Neuron.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "neuron.h"

#include <cmath>
#include "synapse.h"

unsigned Neuron::counter = 0;

Neuron::Neuron() :
		activity(0), delta(0), id(counter) {
	counter++;
}

double Neuron::sum(vector<double> x) {
	double sum = 0;
	for (double cur : x) {
		sum += cur;
	}
	return sum;
}

void Neuron::feedForward() {
	double propagation = this->getNetInput();
	this->activity = sigmoid(propagation);
}

double Neuron::getNetInput() {
	vector<double> inp;
	for (SynapsePtr input : parents) {
		inp.push_back(input->getSignal());
	}
	return sum(inp);
}

double Neuron::sigmoid(double x) {
	return (x / (1. + std::abs(x))) * 0.5 + 0.5;
}

double Neuron::sigmoidPrime(double x) {
	return std::pow(1. + std::abs(x), -2) / 2.;
}
