/*
 * Synapse.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "synapse.h"

#include <cstdlib>
#include "neuron.h"

double Synapse::learningRate = 0.2;
unsigned Synapse::counter = 0;

Synapse::Synapse(NeuronPtr in_, NeuronPtr out_) :
		weight(2. * ((double) std::rand() / RAND_MAX) - 1.), weightChange(0.) {
	in = in_;
	out = out_;
	in->addChild(SynapsePtr(this));
	out->addParent(SynapsePtr(this));
	id = counter;
	counter++;
}

double Synapse::getSignal() {
	return weight * in->activity;
}
