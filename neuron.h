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

	void feedForward();
	double getNetInput();

	static double sigmoid(double x);
	static double sigmoidPrime(double x);

	double getActivity() const;
	void setActivity(double activity);
	const vector<SynapsePtr>& getChilds() const;
	void addChild(SynapsePtr syn);
	void addParent(SynapsePtr syn);
	unsigned getID() const;

	double activity;
	double delta;

private:
	static unsigned counter; //writes id

	unsigned id;
	vector<SynapsePtr> childs;
	vector<SynapsePtr> parents;
};

#endif /* NEURON_H_ */
