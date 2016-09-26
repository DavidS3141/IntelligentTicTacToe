/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <vector>;

using namespace std;

class NeuralNetwork : public Graph {
public:
	NeuralNetwork();
	virtual ~NeuralNetwork();

	void feedForward(vector<double> input);
	void backProp(vector<double> correctOutput);
};

#endif /* NEURALNETWORK_H_ */
