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
	Neuron(int id);
	virtual ~Neuron();

	static double sigmoid(double x);
	static double sigmoidPrime(double x);

	double activity;
	double delta;
};

#endif /* NEURON_H_ */
