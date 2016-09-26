/*
 * Neuron.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURON_H_
#define NEURON_H_

#include "node.h"
#include <vector>

using namespace std;
class Neuron: public Node {
public:
	Neuron();
	virtual ~Neuron();

	double sum(vector<double> x) const;

	void feedForward();
	double getNetInput();

	static double sigmoid(double x);
	static double sigmoidPrime(double x);

	double activity;
};

#endif /* NEURON_H_ */
