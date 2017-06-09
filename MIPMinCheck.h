/*
 * MIPMinCheck.h
 *
 *  Created on: Feb 1, 2015
 *      Author: mushthofa
 */

#ifndef MIPMINCHECK_H_
#define MIPMINCHECK_H_

#include "MinCheck.h"
#include <glpk.h>
#include "MIPRegistry.h"
#include <coin/CbcModel.hpp>
#include <coin/OsiClpSolverInterface.hpp>

const double EPS = 1e-5;

class MIPMinCheck: public MinCheck
{
public:
	MIPMinCheck(const Program& p, const FAnswerSet& as)
	:MinCheck(), mipreg(p, as)
	{
		/* Count our target = \Sigma_x a[x]\in AS
		 * If the objective value z from MIP is s.t.
		 * |z-target| < EPS
		 * we got a minimal AS
		 */
		Inter_t interp = as.getInter();
		Inter_t::iterator it;
		target = 0;
		for(it=interp.begin(); it!=interp.end(); ++it)
		{
			std::string predName = it->first->getPredicateName();
			if(predName.find("_NEW_")!=string::npos)
						continue;
			target += it->second.getFloat();
		}
	}


	void writeMPS();
	bool callMIP();

	virtual bool isMinimal()
	{
		writeMPS();
		return callMIP();
	}

	virtual ~MIPMinCheck() {}

protected:
	MIPRegistry mipreg;
	double target;
};


#endif /* MIPMINCHECK_H_ */
