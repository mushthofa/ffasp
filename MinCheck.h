/*
 * MinCheck.h
 *
 *  Created on: Feb 1, 2015
 *      Author: mushthofa
 */


#ifndef MINCHECK_H_
#define MINCHECK_H_

#include "Program.h"
#include "FAnswerSet.h"

class MinCheck
{
public:
	MinCheck()
	{}

	virtual bool isMinimal() = 0;

	virtual ~MinCheck() {}

protected:

};





#endif /* MINCHECK_H_ */
