/*
 * Neuron.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "Neuron.h"
#include "Synapse.h"
#include <cmath>

Neuron::Neuron(){
}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

double Neuron::sum(vector<double> x) {
	double sum = 0;
	for(double cur : x) {
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
	for(Edge* input : parents) {
		inp.push_back(((Synapse*)input)->getSignal());
	}
	return sum(inp);
}

double Neuron::sigmoid(double x) {
	return (x / (1. + std::abs(x)))*0.5+0.5;
}

double Neuron::sigmoidPrime(double x) {
	return std::pow(1. + std::abs(x), -2)/2.;
}
