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
{
	components = dg->getComponents();
	
	/* Set up array for storing individual AS */
	
	std::vector<Component*>::const_iterator cit;
	unsigned i=0;
	for(cit = components.begin(); cit!= components.end(); ++cit)
	{
		globalAS.insert(std::pair<Component*, FAnswerSet> (components[i++], FAnswerSet()));
	}
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
		FAnswerSet cur = globalAS[components[i]];
		//std::cout<<"cur = "<<cur<<std::endl;
		result = result.merge(cur);
	}

	//std::cout<<result<<std::endl;
	return result;
}


void GraphProcessor::eval(unsigned idx)
{
	
	
	/* Get the input */
	FAnswerSet input = getInput(idx);
	
	/* Decide what evaluation method we should call */
	
	Program currentComp = components[idx]->getBottom();

	currentComp = currentComp + input.getFacts();

	//std::cout<<"Evaluating component "<<idx<<": " << std::endl;
	//std::cout<<currentComp<<std::endl;
	//std::cout <<"with input "<< std::endl << input << std::endl;
	//std::cout <<"SRCF = " << components[idx]->isSRCF()<< std::endl;


	/*
	std::cout<<"Pred sign:"<<std::endl;
	MapSign_t predsign = currentComp.getPredicates();
	MapSign_t::iterator it;
	for(it=predsign.begin(); it!=predsign.end(); ++it)
	{
		std::cout<<it->first<<"/"<<it->second<<", ";
	}
	std::cout<<std::endl;
	*/

	FAnswerSet currentAS;

	int maxk = Globals::Instance()->intOption("maxk");
	int maxtime = Globals::Instance()->intOption("maxt");
	//bool printAS = !Globals::Instance()->boolOption("check");

	stop_t stop = std::make_pair(maxk, maxtime);
	int step = lcm(ConstantAtom::denomList);
	step = lcm(step, input.getDenomLCM());

	ASPSolverEngine* eng = new CLSolverEngine();
	Eval* evaluator;


	evaluator  = new ASPEval(eng, currentComp, stop, step, step);

	while(evaluator->answersetsLeft())
	{
		if(idx == components.size()-1)
		{
			/* Last component to be evaluated */
			/* Just stream it out */
			// std::cout<<"Reached last component, streaming answer set: "<<std::endl;
			currentAS = evaluator->getNextAnswerSet();
			std::cout<<currentAS.getStrClean()<<std::endl;
		}
		else
		{
			/* Call eval recursively for the next components */
			currentAS = evaluator->getNextAnswerSet();
			//std::cout <<" Answer set of component " <<idx<<std::endl<<currentAS<<std::endl;
			globalAS[components[idx]] = currentAS;
			eval(idx+1);
		}
	}
	
	delete evaluator;
	
}

//end
