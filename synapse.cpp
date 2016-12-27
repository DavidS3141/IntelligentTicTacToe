/*
 * Synapse.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "synapse.h"

#include "node.h"
#include <cstdlib>
#include <iostream>
#include "neuron.h"

double Synapse::learningRate = 0.2;

Synapse::Synapse(Neuron* in, Neuron* out) :
		Edge(in, out), weight(2. * ((double) std::rand() / RAND_MAX) - 1.) {
}

Synapse::~Synapse() {
}

double Synapse::getSignal() {
	//std::cout << ((Neuron*) in)->activity << std::endl;
	return weight * ((Neuron*) in)->activity;
}
