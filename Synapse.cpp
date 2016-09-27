/*
 * Synapse.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "Synapse.h"

#include "node.h"
#include "Neuron.h"
#include <cstdlib>

const double Synapse::learningRate = 0.5;

Synapse::Synapse(Neuron* in, Neuron* out): Edge(in,out), weight(2.*((double)std::rand()/RAND_MAX)-1.) {
}

Synapse::~Synapse() {
	// TODO Auto-generated destructor stub
}

double Synapse::getSignal() {
	return weight*((Neuron*) in)->activity;
}
