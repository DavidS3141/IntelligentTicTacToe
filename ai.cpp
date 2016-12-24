/*
 * ai.cpp
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#include "ai.h"

#include "NeuralNetwork.h"

AI::AI(NeuralNetwork * const network_) :
		network(network_) {
}

Move AI::getMove(Board board) {
	return network->getProbableMove(board);
}
