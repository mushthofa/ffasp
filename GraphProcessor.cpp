/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa   								*
 *   unintendedchoice@gmail.com  									*
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

/** 
 *	@brief GraphProcessor.cpp
 * 		Provides a class to perform evaluation along the components dep. graph
 * 		Assuming that the components is already given in a topological ordering
 *
 *	@author Mushthofa
 */

#include "GraphProcessor.h"
//#include "EvalComp.h"

GraphProcessor::GraphProcessor(DependencyGraph* dg)//, ASPSolverEngine* se)//, Eval* eval, int k)
//	:solver_engine(se)//, ev(eval), step(k)
:found(false)
{
	components = dg->getComponents();
	
	/* Set up array for storing individual AS */
	
	for(int i=0; i<components.size(); i++)
	{
		Program cur = components[i]->getBottom();
		if(cur.size()>0)
			compPrograms.push_back(cur);

	}

	numComp = compPrograms.size();
	globalAS.resize(numComp);
}

GraphProcessor::~GraphProcessor()
{
}

FAnswerSet GraphProcessor::getInput(unsigned idx)
{
	//std::cout<<"Get input "<<idx<<": "<<std::endl;
	FAnswerSet result;
	
	/* Merge all fuzzy answer set from previous components (number < idx) into one answer set
	 * Note: take care of finding the largest truth value among atoms a s.t. I(a)>0
	 */
	if(idx == 0)
	{
		return result;
	}
	for(unsigned i=0; i<idx; i++)
	{
		FAnswerSet cur = globalAS[i];
		//std::cout<<"cur = "<<cur<<std::endl;
		result = result.merge(cur);
	}

	//std::cout<<result<<std::endl;
	return result;
}


void GraphProcessor::eval(unsigned idx)
{
	
	
	// Get the input
	FAnswerSet input = getInput(idx);
	
	
	// Get the current component's program
	Program currentComp = compPrograms[idx];

	// Add the current input
	currentComp = currentComp + input.getFacts();

	// Decide what evaluation method we should call


	//std::cout<<"Evaluating component "<<idx<<": " << std::endl;
	//std::cout<<currentComp<<std::endl;
	//std::cout <<"with input "<< std::endl << input << std::endl;


	FAnswerSet currentAS;

	int maxk = Globals::Instance()->intOption("maxk");
	int maxtime = Globals::Instance()->intOption("maxt");
	//bool printAS = !Globals::Instance()->boolOption("check");

	stop_t stop = std::make_pair(maxk, maxtime);
	int step = lcm(ConstantAtom::denomList);
	step = lcm(step, input.getDenomLCM());

	ASPSolverEngine* eng = new CLSolverEngine();
	Eval* evaluator;

	//bool needcheck = !components[idx]->isSRCF() && components[idx]->isDisjunctive();
	evaluator  = new ASPEval(eng, currentComp, stop, step, step);

	//found = false;
	while(!found && evaluator->answersetsLeft())
	{
		if(idx == numComp-1)
		{
			// Last component to be evaluated
			// Just stream it out
			// std::cout<<"Reached last component, streaming answer set: "<<std::endl;
			currentAS = evaluator->getNextAnswerSet();
			std::cout<<currentAS.getStrClean()<<std::endl;
			//std::cout<<"<<Consistent>>"<<std::endl;
			found = true;
		}
		else
		{
			// Call eval recursively for the next components
			currentAS = evaluator->getNextAnswerSet();
			//std::cout <<" Answer set of component " <<idx<<std::endl<<currentAS<<std::endl;
			globalAS[idx] = currentAS;
			eval(idx+1);
		}
	}
	
	//delete evaluator;
	
}

//end
