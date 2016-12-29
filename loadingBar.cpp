/*
 * loadingBar.cpp
 *
 *  Created on: 29.12.2016
 *      Author: David
 */

#include "loadingBar.h"

#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using std::flush;

unsigned LoadingBar::minBlockNbr = 20;
unsigned LoadingBar::maxBlockT = 30;

LoadingBar::LoadingBar(string desc_) :
		desc(desc_) {
	reset(0);
}

void LoadingBar::reset(unsigned length_) {
	length = length_;
	counter = 0;
	block = 0;
	delT = clock();
}

void LoadingBar::operator++() {
	++counter;
	if (counter == 1) {
		delT = clock() - delT;
		delT /= CLOCKS_PER_SEC;
		//block*delT<=maxBlockT and length>=minBlockNbr*block
		//=> block<=length/minBlockNbr and block<=maxBlockT/delT
		block = std::min(length / minBlockNbr, (unsigned) (maxBlockT / delT));
		cout << desc << " ..." << endl;
		cout << "|" << string(length / block, '-') << "|" << endl;
		cout << " ";
	}
	if (counter % block == 0)
		cout << "#" << flush;
	if (counter == length) {
		cout << endl;
		reset(0);
	}
}
