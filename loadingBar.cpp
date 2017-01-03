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
float LoadingBar::resolutionT = 10;

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
	approxEnd = 0.;
}

void LoadingBar::set(unsigned length_) {
	length = length_;
	counter = 0;
	block = 0;
	bcounter = 0;
	start = std::chrono::high_resolution_clock::now();
	approxEnd = 0.;
}

void LoadingBar::operator++() {
	++counter;
	std::chrono::time_point<std::chrono::high_resolution_clock> now =
			std::chrono::high_resolution_clock::now();
	double delT = std::chrono::duration<double>(now - start).count();
	delT /= counter;
	double approx = delT * (length - counter);
	double oldApprox = approxEnd
			- std::chrono::duration<double>(now - start).count();
	if (approx > 2 * oldApprox && approx - oldApprox > resolutionT) {
		approxEnd = approx + std::chrono::duration<double>(now - start).count();
		reprint();
	} else if (approx < 0.5 * oldApprox && oldApprox - approx > resolutionT) {
		approxEnd = approx + std::chrono::duration<double>(now - start).count();
		reprint();
	}
	while ((bcounter + 1) * block <= counter) {
		cout << "#" << flush;
		++bcounter;
	}
	if (counter == length) {
		cout << endl;
		cout << "Finished: "
				<< std::asctime(std::localtime(new time_t(std::time(NULL))));
		reset();
	}
}

void LoadingBar::reprint() {
	if (block)
		cout << endl;
	double tstart = std::chrono::duration<double>(
			std::chrono::high_resolution_clock::now() - start).count();
	cout << desc << " ... started at "
			<< std::asctime(
					std::localtime(
							new time_t(
									time(NULL)
											- (unsigned) std::round(tstart))));
	bcounter = 0;
	double approx = approxEnd - tstart;
	double delT = std::chrono::duration<double>(
			std::chrono::high_resolution_clock::now() - start).count()
			/ counter;
	unsigned hours = approx / 3600;
	unsigned minutes = (approx - 3600 * hours) / 60;
	unsigned seconds = std::round(approx - 3600 * hours - 60 * minutes);
	if (seconds == 60) {
		++minutes;
		seconds = 0;
	}
	if (minutes == 60) {
		++hours;
		minutes = 0;
	}
	//block*delT<=maxBlockT and length>=minBlockNbr*block and length<=maxBlockNbr*block
	//=> block<=length/minBlockNbr and block<=maxBlockT/delT and block>=length/maxBlockNbr
	block = std::max(length / maxBlockNbr,
			std::min(length / minBlockNbr, (unsigned) (maxBlockT / delT)));
	cout << "Approximated duration: ";
	if (hours > 0)
		cout << hours << "h ";
	if (minutes > 0)
		cout << minutes << "m ";
	if (seconds > 0)
		cout << seconds << "s" << endl;
	else {
		if (hours == 0 && minutes == 0)
			cout << "<1s" << endl;
		else
			cout << endl;
	}
	cout << "Expected to be finished: " << string(12, ' ')
			<< std::asctime(
					std::localtime(new time_t(std::time(NULL) + approx)));
	cout << "|" << string(length / block, '-') << "|" << endl;
	cout << " ";
}
