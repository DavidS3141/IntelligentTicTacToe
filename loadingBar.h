/*
 * loadingBar.h
 *
 *  Created on: 29.12.2016
 *      Author: David
 */

#ifndef LOADINGBAR_H_
#define LOADINGBAR_H_

#include <chrono>
#include <string>
using std::string;

class LoadingBar {
public:
	LoadingBar(string desc_ = "Progressing");

	void set(unsigned length_);
	void reset();
	void operator++();
	void reprint();
private:
	string desc;
	unsigned length;
	unsigned counter;
	unsigned block;
	unsigned bcounter;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	double approxEnd;

	static unsigned minBlockNbr;
	static unsigned maxBlockNbr;
	static float maxBlockT;
	static float resolutionT;
};

#endif /* LOADINGBAR_H_ */
