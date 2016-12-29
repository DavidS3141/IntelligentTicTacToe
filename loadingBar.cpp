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
		double approx = delT * (length - 1);
		unsigned hours = approx / 3600;
		unsigned minutes = (approx - 3600 * hours) / 60;
		//block*delT<=maxBlockT and length>=minBlockNbr*block
		//=> block<=length/minBlockNbr and block<=maxBlockT/delT
		block = std::min(length / minBlockNbr, (unsigned) (maxBlockT / delT));
		cout << desc << " ..." << endl;
		cout << "Approximated duration: ";
		if (hours > 0)
			cout << hours << "h ";
		if (minutes > 0)
			cout << minutes << "m" << endl;
		else {
			if (hours == 0)
				cout << "<1m" << endl;
			else
				cout << endl;
		}
		cout << "Expected to be finished: "
				<< std::asctime(
						std::localtime(new time_t(std::time(NULL) + approx)));
		cout << "|" << string(length / block, '-') << "|" << endl;
		cout << " ";
	}
	if (counter % block == 0)
		cout << "#" << flush;
	if (counter == length) {
		cout << endl;
		cout << "Finished: "
				<< std::asctime(std::localtime(new time_t(std::time(NULL))));
		reset(0);
	}
}
