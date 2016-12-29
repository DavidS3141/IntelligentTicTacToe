/*
 * loadingBar.h
 *
 *  Created on: 29.12.2016
 *      Author: David
 */

#ifndef LOADINGBAR_H_
#define LOADINGBAR_H_

#include <string>
using std::string;

class LoadingBar {
public:
	LoadingBar(string desc_ = "Progressing");

	void reset(unsigned length_);
	void operator++();
private:
	string desc;
	unsigned length;
	unsigned counter;
	unsigned block;
	double delT;

	static unsigned minBlockNbr;
	static unsigned maxBlockT;
};

#endif /* LOADINGBAR_H_ */
