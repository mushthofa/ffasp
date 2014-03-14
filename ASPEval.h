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

class ASPEval : public Eval
{
public:
	ASPEval(ASPSolverEngine* eng, const Program& prog, stop_t stop, int st)
	:Eval(prog, stop), step(st)
	{
		/* Get filters from the programs's predicate signature
		 * However these still contain p_NEW_'s from ASPTranslate
		 * so these need to be excluded
		 *
		 // TODO: No filter definition in clingo found!!!
		 //	These are for DLV style filter definition

		MapSign_t predsign = program.getPredicates();
		MapSign_t::iterator pit;
		std::set<std::string> filter;
		for(pit=predsign.begin(); pit!=predsign.end(); ++pit)
		{
			std::string predname (pit->first);
			if(predname.find(NEW_PRED)==std::string::npos)
				filter.insert(predname);
		}
		*/

		bool checkonly = Globals::Instance()->boolOption("check");
		solver = eng->createSolver(checkonly);
		doSolve();
	}


	virtual ~ASPEval()
	{
		delete solver;
	}

	virtual void doSolve();

	//void processAS(AtomSet as, int k);

protected:
	int step;
	ASPSolver* solver;
};

#endif /* ASPEVAL_H_ */
