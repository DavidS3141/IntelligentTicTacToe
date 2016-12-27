/*
 * ai.cpp
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#include "ai.h"

#include "neuralNetwork.h"

AI::AI(const NeuralNetworkPtr network_) :
		network(network_) {
}

Move AI::getMove(Board board) {
	return network->getMove(board);
}
