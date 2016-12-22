/*
 * player.h
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "constants.h"

class Player {
public:
	Player();
	virtual ~Player();

	virtual Move getMove(Board) = 0;
};

#endif /* PLAYER_H_ */
