/*
 * logicPlayer.h
 *
 *  Created on: 23.12.2016
 *      Author: David
 */

#ifndef LOGICPLAYER_H_
#define LOGICPLAYER_H_

#include "player.h"

class LogicPlayer: public Player {
public:
	LogicPlayer();
	Move getMove(Board);

private:
	static int converter(int);
};

#endif /* LOGICPLAYER_H_ */
