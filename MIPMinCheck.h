/*
 * MIPMinCheck.h
 *
 *  Created on: Feb 1, 2015
 *      Author: mushthofa
 */

#ifndef MIPMINCHECK_H_
#define MIPMINCHECK_H_

#include "Mincheck.h"
#include <glpk.h>
#include "coin/CbcModel.hpp"
#include "coin/OsiClpSolverInterface.hpp"

class MIPMinCheck: public MinCheck
{
public:
	MIPMinCheck(const Program& p, const FAnswerSet& as)
	:MinCheck(p,as)
	{}

	virtual bool isMinimal()
	{
		return true;
	}

	std::string translate2MIP()
	{
		std::string result;


		return result;
	}


};


#endif /* MIPMINCHECK_H_ */
