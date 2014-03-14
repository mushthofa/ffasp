/***************************************************************************
*   Copyright (C) 2014 by Mushthofa                                        *
*   Mushthofa.Mushthofa@Ugent.be                                           *
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
 /* *
 * ASPEval.cpp
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

#include "ASPEval.h"

void ASPEval::doSolve()
{

	int maxk = stop.first;
	time_t maxtime = stop.second, dur;
	time_t start = time(0);
	int k = step;
	do
	{

		//std::cout<<"k="<<k<<std::endl;
		ASPTranslate* tr;
		try
		{
			tr = new ASPTranslate(program, k);
		}
		catch(GeneralError& err)
		{

			delete tr;
			std::ostringstream oserr;
			oserr<<"Error translating program for k = "<<  k  << ": "
				<<std::endl<< err.getErrorMsg();
			throw FatalError(oserr.str());
		}

		try
		{
			solver->callSolver(tr->getProgram(), k);
		}
		catch(GeneralError& e)
		{
			delete tr;
			throw FatalError("doSolve(): Error calling solver : \n"+e.getErrorMsg());
		}

		if(solver->answerSetsLeft())
		{
			found = true;
		}

		delete tr;
		time_t end = time(0);
		dur = end-start;
		k += step;
	}
	while(!found && k<=maxk && dur<=maxtime);
	if(!found)
		std::cout<<"No k-answer set is found until k = "<<k-step<<" and time = "<<dur<<" s"<<std::endl;
}

