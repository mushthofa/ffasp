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
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

void ASPEval::processAS(std::string asline)
{
	std::map<std::string, int> acc;
	std::map<std::string, int>::iterator acc_it;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sp(" ");
	tokenizer tok(asline, sp);
	tokenizer::iterator as_it;
	for(as_it=tok.begin(); as_it!=tok.end(); ++as_it)
	{
		std::string curp = *as_it;
		if(curp.find("_NEW_")!=string::npos)
			continue;

		//std::cout<<curp<<std::endl;

		boost::char_separator<char> kur(", ()");
		tokenizer tok2(curp, kur);
		tokenizer::iterator itp;
		std::vector<std::string> atomv;
		for(itp=tok2.begin(); itp!=tok2.end(); ++itp)
		{
			atomv.push_back(*itp);
		}

		int sz = atomv.size();
		assert(sz>=2);

		/*
		Tuple args;
		for(int i=0; i<sz-1; i++)
		{
			boost::trim(atomv[i]);
			args.push_back(Term(atomv[i], Term::SYMBOL ));
		}

		AtomPtr atom(new Atom(args, false));


		int a = boost::lexical_cast<int> (atomv[sz-1]);


		acc_it = acc.find(atom);
		if(acc_it == acc.end() || acc[atom] < a)
			acc[atom] = a;
			*/
		std::ostringstream os;
		os << atomv[0];
		if(sz > 2)
		{
				os<<"("<<atomv[1];
				int i;
				for(i=2; i<sz-1; ++i)
						os<<", "<<atomv[i];
				os<<")";
		}
		int a = boost::lexical_cast<int> (atomv[sz-1]);

		acc_it = acc.find(os.str());
		if(acc_it == acc.end() || acc[os.str()] < a)
				acc[os.str()] = a;
	}

	std::ostringstream os;
	os<<"{";
	int i=0;
	for(acc_it = acc.begin(); acc_it!=acc.end(); ++acc_it)
	{
			i++;
			if(acc_it->second > 0)
			{
					float tv = (float) acc_it->second/curr_k;
					os<<acc_it->first<<"["<<tv<<"]";
					if(i<acc.size())
							os<<", ";
			}

	}
	os<<"}"<<std::endl;
	as.push_back(os.str());
	/*
	FAnswerSet curr_as;
	for(acc_it = acc.begin(); acc_it!=acc.end(); ++acc_it)
	{
		curr_as.addAnswer(acc_it->first, Rational(acc_it->second, curr_k));
	}

	fas_set.insert(curr_as);
	*/
}


bool ASPEval::doSolve()
{

	int maxk = stop.first;
	time_t maxtime = stop.second, dur = 0;
	time_t start = time(0);
	//int k = std::max(step, 2);	// start search from k=2
	bool found = false;
	do
	{

		std::cout<<"k="<<curr_k<<std::endl;
		ASPTranslate* tr;
		try
		{
			tr = new ASPTranslate(program, curr_k);
		}
		catch(GeneralError& err)
		{

			delete tr;
			std::ostringstream oserr;
			oserr<<"Error translating program for k = "<< curr_k  << ": "
				<<std::endl<< err.getErrorMsg();
			throw FatalError(oserr.str());
		}

		try
		{
			solver->callSolver(tr->getProgram(), curr_k, maxtime-dur);
		}
		catch(GeneralError& e)
		{
			delete tr;
			throw FatalError("doSolve(): Error calling solver : \n"+e.getErrorMsg());
		}

		if(solver->answerSetsLeft())
		{

			//fas.clear();
			as.clear();
			std::vector<std::string> aslines = solver->getlines();
			for(std::vector<std::string>::iterator it=aslines.begin();
					it!=aslines.end(); ++it)
			{
				processAS(*it);
			}

			//std::copy(fas_set.begin(), fas_set.end(), std::back_inserter(fas));

			std::cout<<"Found "<<as.size()<<std::endl;
			found = true;
		}

		delete tr;
		time_t end = time(0);
		dur += end-start;
		curr_k += step;
	}
	while(!found && curr_k<=maxk && dur<=maxtime);

	return found;
	/*
	if(!found)
		std::cout<<"No k-answer set is found until k = "<<k-step<<" and time = "<<dur<<" s"<<std::endl;
	*/
}

bool ASPEval::answersetsLeft()
{
	if(as_idx < as.size())
		return true;
	else if(curr_k <= stop.first)
	{
		as_idx = 0;
		return doSolve();
	}
	return false;
}

