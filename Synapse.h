/*
 * Synapse.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef SYNAPSE_H_
#define SYNAPSE_H_

#include "edge.h"

class Synapse: public Edge {
public:
	Synapse();
	virtual ~Synapse();

	double weight;
	const static double learningRate;

	double getSignal();
};

#endif /* SYNAPSE_H_ */
