/*
 * human.cpp
 *
 *  Created on: 22.12.2016
 *      Author: David
 */

#include "human.h"

Human::Human() {
}


Move Human::getMove(Board board){
	printBoard(board);
	std::cout << "Your move in R,C:" << std::endl;
	std::string s;
	std::cin >> s;
	return Move((s[0]-'0')-1,(s[2]-'0')-1,1);
}
