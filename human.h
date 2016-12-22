/*
 * human.h
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class Human: public Player {
public:
	Human();
	Move getMove(Board);
};

#endif /* HUMAN_H_ */
