/*
 * loadingBar.cpp
 *
 *  Created on: 29.12.2016
 *      Author: David
 */

#include "loadingBar.h"

#include <cmath>
#include <ctime>
#include <chrono>
#include <iostream>
using std::cout;
using std::endl;
using std::flush;

unsigned LoadingBar::minBlockNbr = 20;
unsigned LoadingBar::maxBlockNbr = 80;
float LoadingBar::maxBlockT = 30;
float LoadingBar::maxDisplayT = 3;

LoadingBar::LoadingBar(string desc_) :
		desc(desc_) {
	reset();
}

void LoadingBar::reset() {
	length = 0;
	counter = 0;
	block = 0;
	bcounter = 0;
	start = std::chrono::high_resolution_clock::now();
}

void LoadingBar::set(unsigned length_) {
	length = length_;
	counter = 0;
	block = 0;
	bcounter = 0;
	start = std::chrono::high_resolution_clock::now();
	cout << desc << " ... started at "
			<< std::asctime(std::localtime(new time_t(time(NULL))));
}

void LoadingBar::operator++() {
	++counter;
	if (block == 0) {
		double delT = std::chrono::duration<double>(
				std::chrono::high_resolution_clock::now() - start).count();
		if (counter * 20 > length || delT > maxDisplayT) {
			delT /= counter;
			double approx = delT * (length - counter);
			unsigned hours = approx / 3600;
			unsigned minutes = std::round((approx - 3600 * hours) / 60.);
			if (minutes == 60) {
				++hours;
				minutes = 0;
			}
			//block*delT<=maxBlockT and length>=minBlockNbr*block and length<=maxBlockNbr*block
			//=> block<=length/minBlockNbr and block<=maxBlockT/delT and block>=length/maxBlockNbr
			block = std::max(length / maxBlockNbr,
					std::min(length / minBlockNbr,
							(unsigned) (maxBlockT / delT)));
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
							std::localtime(
									new time_t(std::time(NULL) + approx)));
			cout << "|" << string(length / block, '-') << "|" << endl;
			cout << " ";
		}
	} else {
		while ((bcounter + 1) * block <= counter) {
			cout << "#" << flush;
			++bcounter;
		}
		if (counter == length) {
			cout << endl;
			cout << "Finished: "
					<< std::asctime(
							std::localtime(new time_t(std::time(NULL))));
			reset();
		}
	}
}
