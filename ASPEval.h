/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                             *
 *   Mushthofa.Mushthofa@Ugent.be                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*

 * ASPEval.h
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

#ifndef ASPEVAL_H_
#define ASPEVAL_H_

#include "Eval.h"
#include "ASPSolver.h"
#include "ASPTranslate.h"
#include "FAnswerSet.h"

class ASPEval : public Eval
{
public:
	ASPEval(ASPSolverEngine* eng, const Program& prog, stop_t stop, int k, int st)
	:Eval(prog, stop, k, st), as_idx(0)
	{
		bool checkonly = Globals::Instance()->boolOption("check");
		solver = eng->createSolver(checkonly);
		//doSolve();
	}


	virtual ~ASPEval()
	{
		delete solver;
	}

	virtual bool doSolve();

	void processAS(std::string as);

	virtual std::string getNextAnswerSet()
	{

		if(!answersetsLeft())
		{
			throw FatalError("No more answer sets to return!");
		}

		return as[as_idx++];
	}

	virtual bool answersetsLeft();

protected:
	//int step;
	ASPSolver* solver;
	int as_idx;

};

#endif /* ASPEVAL_H_ */
