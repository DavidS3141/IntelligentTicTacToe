/*
 * Synapse.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef SYNAPSE_H_
#define SYNAPSE_H_

#include <memory>

class Neuron;
typedef std::shared_ptr<Neuron> NeuronPtr;

class Synapse {
public:
	Synapse(NeuronPtr in, NeuronPtr out);

	double getSignal();

	const NeuronPtr getIn() const {
		return in;
	}

	const NeuronPtr getOut() const {
		return out;
	}

	unsigned getID() const {
		return id;
	}

	double weight;
	static double learningRate;

private:
	static unsigned counter; //writes id

	unsigned id;
	NeuronPtr in;
	NeuronPtr out;
};

#endif /* SYNAPSE_H_ */
