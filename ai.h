/*
 * ai.h
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#ifndef AI_H_
#define AI_H_

#include "player.h"

class NeuralNetwork;
typedef shared_ptr<NeuralNetwork> NeuralNetworkPtr;

class AI: public Player {
public:
	AI(const NeuralNetworkPtr network_);
	Move getMove(Board);
private:
	const NeuralNetworkPtr network;
};

#endif /* AI_H_ */
