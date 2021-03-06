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
#include "MIPMinCheck.h"
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>


bool ASPEval::processAS(std::string asline, bool check)
{
	//std::cout<<"Process AS = "<<asline<<std::endl;
	bool found = false;
	std::map<AtomPtr, int> acc;
	std::map<AtomPtr, int>::iterator acc_it;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sp(" ");
	tokenizer tok(asline, sp);
	tokenizer::iterator as_it;
	for(as_it=tok.begin(); as_it!=tok.end(); ++as_it)
	{
		std::string curp = *as_it;
		/*
		if(curp.find("_NEW_")!=string::npos)
			continue;
		*/


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

		if(sz<2) continue; // For the _NEW_ predicates that has no arguments

		Tuple args;
		for(int i=0; i<sz-1; i++)
		{
			boost::trim(atomv[i]);
			args.push_back(Term(atomv[i], Term::SYMBOL ));
		}

		AtomPtr atom(new Atom(args, false));
		//std::cout<<"Atom="<<atomv[sz-1]<<std::endl;

		int a = boost::lexical_cast<int> (atomv[sz-1]);


		acc_it = acc.find(atom);
		if(acc_it == acc.end() || acc[atom] < a)
			acc[atom] = a;
		/*
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
		*/
	} // End for

	//std::cout<<"created "<<acc.size()<<" atoms"<<endl;

	/*
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
	*/


	FAnswerSet curr_as;
	for(acc_it = acc.begin(); acc_it!=acc.end(); ++acc_it)
	{
		curr_as.addAnswer(acc_it->first, Rational(acc_it->second, curr_k));
	}

	if(strAS.find(curr_as.getStr())==strAS.end())
	{
		if(!check)	// If minimality check is not needed
		{
			fas.push_back(curr_as);
			strAS.insert(curr_as.getStr());
			//std::cout<<"strAS.size() = "<<strAS.size() <<endl;
			found = true;
			//std::cout<<"No Check!"<<std::endl;
		}
		else		// Check minimality
		{
			MinCheck* mc;
			//std::cout<<"Min-Checking..."<<endl; //<<curr_as<<endl;
			mc = new MIPMinCheck(program, curr_as);
			if(mc->isMinimal())		// Found
			{
				fas.push_back(curr_as);
				strAS.insert(curr_as.getStr());
				found = true;
			}
			delete mc;
		}
	}
	return found;
}


bool ASPEval::doSolve()
{

	int maxk = stop.first;
	time_t maxtime = stop.second, dur = 0;
	time_t start = time(0);
	//int k = std::max(step, 2);	// start search from k=2
	bool found = false;

	//std::cout<<"doSolve(): "<<std::endl;
	//std::cout<<program<<std::endl;
	do
	{

		//std::cout<<"k="<<curr_k<<std::endl;
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
			//std::cout<<"Translated program "<<std::endl;
			//std::cout<<tr->getProgram()<<std::endl;
			//std::cout<<"Calling solver..."<<std::endl;
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

			std::string asline = solver->getNextLine();
			//std::cout<<"Found "<<aslines.size()<<std::endl;
			//int i=0;
			//for(std::vector<std::string>::iterator it=aslines.begin();
			//		it!=aslines.end(); ++it)
			//{
				//cout<<i<<endl;
				//cout<<"Processing "<<asline<<endl;
				found = processAS(asline, tr->needMinCheck());
				//found = found || curfound;
			//}

		}

		delete tr;
		time_t end = time(0);
		dur += end-start;
		curr_k += step;
	}
	while(!found && curr_k<=maxk && dur<=maxtime);

	return found;
}

bool ASPEval::answersetsLeft()
{
	//std::cout<<"as_idx = "<<as_idx<<", fas = "<<fas.size()<<std::endl;
	//std::cout<<"curr_k = "<<curr_k<<endl;
	if(as_idx < fas.size())
		return true;
	else if(curr_k <= stop.first)
	{
		as_idx = 0;
		fas.clear();
		return doSolve();
	}
	return false;
}

