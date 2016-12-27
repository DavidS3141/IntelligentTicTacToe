/*
 * Neuron.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <vector>
using std::vector;

class Synapse;
typedef std::shared_ptr<Synapse> SynapsePtr;

class Neuron {
public:
	Neuron();

	static double sum(vector<double> x);

	void addChild(SynapsePtr syn) {
		childs.push_back(syn);
	}

	void addParent(SynapsePtr syn) {
		parents.push_back(syn);
	}

	void feedForward();
	double getNetInput();

	static double sigmoid(double x);
	static double sigmoidPrime(double x);

	double getActivity() const {
		return activity;
	}

	void setActivity(double activity) {
		this->activity = activity;
	}

	const vector<SynapsePtr>& getChilds() const {
		return childs;
	}

	unsigned getID() const {
		return id;
	}

	double activity;
	double delta;

private:
	static unsigned counter; //writes id

	unsigned id;
	vector<SynapsePtr> childs;
	vector<SynapsePtr> parents;
};

#endif /* NEURON_H_ */
