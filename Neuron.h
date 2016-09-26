/*
 * Neuron.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURON_H_
#define NEURON_H_

#include "node.h"

class Neuron: public Node {
public:
	Neuron();
	virtual ~Neuron();

	double sigmoid(double x) const;
	double sigmoidPrime(double x) const;
};

#endif /* NEURON_H_ */
