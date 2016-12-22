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

class AI: public Player {
private:
	NeuralNetwork * const network;
public:
	AI(NeuralNetwork * const network_);

	Move getMove(Board);
};

#endif /* AI_H_ */
