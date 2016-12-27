/*
 * Synapse.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "synapse.h"

#include "node.h"
#include <cstdlib>
#include "neuron.h"

double Synapse::learningRate = 0.2;

Synapse::Synapse(Neuron* in, Neuron* out) :
		Edge(in, out), weight(2. * ((double) std::rand() / RAND_MAX) - 1.), weightChange(
				0.) {
}

Synapse::~Synapse() {
}

double Synapse::getSignal() {
	return weight * ((Neuron*) in)->activity;
}