/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                       *
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
/**
 * @file   CLSolver.cpp
 * @author Mushthofa
 *
 * @brief  ASP solver class implemented using clingo.
 *
 */


#include "CLSolver.h"
#include <boost/tokenizer.hpp>


CLSolver::CLSolver(std::set<std::string> filter, bool co)
        :checkOnly(co), checkSatisfy(false)
	{
        /* Get solver's path and arguments from command line */

        lpcommand = Globals::Instance()->strOption("solver");
        lpargs.push_back(lpcommand);
        lpargs.push_back("--verbose=0");
        if(checkOnly)
        	lpargs.push_back("-q");
        else
        	lpargs.push_back("-n 0");
        
        lpargs.push_back("-W");
        lpargs.push_back("no-atom-undefined");
        lpargs.push_back("-W");
        lpargs.push_back("no-define-cyclic");
        lpargs.push_back("-W");
        lpargs.push_back("no-define-redfinition");
        lpargs.push_back("-W");
        lpargs.push_back("no-nonmonotone-aggregate");
        lpargs.push_back("-W");
        lpargs.push_back("no-term-undefined");
        lpargs.push_back("dummy");

        /*
         * TODO : No filter definition yet for clingo!
        std::string filter_arg = "";
        if(filter.size()>0)
        {
                filter_arg += "-pfilter=";
                std::set<std::string>::iterator f_it;
                unsigned n(0);
                for(f_it = filter.begin(); f_it !=filter.end(); ++f_it)
                {
                        filter_arg += *f_it;
                        if(n<filter.size() - 1)
                                filter_arg += ",";
                }
                lpargs.push_back(filter_arg);
        }
        */

        /*
        for(boost::tokenizer<>::iterator args_it = args.begin(); args_it!=args.end(); ++args_it)
        {
                lpargs.push_back(*args_it);
        }
	*/


        pb = new ProcessBuf();

}


CLSolver::~CLSolver()
{
        delete pb;
}

void CLSolver::callSolver(std::string program, int k, int time_limit)
{

        int retcode = 0;
        aslines.clear();
        if(pb->isOpen())
                retcode = pb->close();

        try
        {
			lpargs.pop_back();
			std::ostringstream osstime;
			osstime<<"--time-limit="<<time_limit;
			std::string timelim = osstime.str();
			lpargs.push_back(timelim);
			pb->open(lpargs);

			std::iostream iopipe(pb);
			iopipe.exceptions(std::ios_base::badbit);
			try
			{

					iopipe<<program<<std::endl;
			}
			catch(std::ios_base::failure e)
			{
					std::ostringstream oserr;
					oserr << "Error executing command ";
					for(std::vector<std::string>::iterator it = lpargs.begin(); it!=lpargs.end(); ++it)
							oserr<<*it<<" ";
					std::cout<<"I/O stream failure: "<<e.what()<<std::endl;
					oserr<<"Program is "<<std::endl<<program<<std::endl;
					throw FatalError(oserr.str());
			}

			pb->endoffile();

			std::string outputline;

			if(checkOnly)
			{

				std::string sat("SATISFIABLE");
				std::string unsat("UNSATISFIABLE");
				std::string timelimit("*** Info : (clingo): INTERRUPTED by signal!");
				std::getline(iopipe, outputline);
				if(outputline==sat)
					checkSatisfy = true;
				else if(outputline==unsat || outputline==timelimit)
					checkSatisfy = false;
				else
					throw FatalError("Unknown result from clingo: "+outputline);
			}
			else
			{
				std::string sat("SATISFIABLE");
				std::string unsat("UNSATISFIABLE");
				std::string timelimit("*** Info : (clingo): INTERRUPTED by signal!");
				std::getline(iopipe, outputline);
				if(outputline!=sat && outputline != unsat && outputline!=timelimit )
				{
					aslines.push_back(outputline);
					//std::cout<<outputline<<std::endl;
					try
					{
						while(std::getline(iopipe, outputline))
						{
							//std::cout<<outputline<<std::endl;
							if(outputline!=sat && outputline != unsat && outputline!=timelimit )
								aslines.push_back(outputline);
						}
					}
					catch(const std::exception& e)
					{
						std::ostringstream ostr;
						ostr<<"Error processing output from clingo: "<<std::endl;
						ostr<<outputline<<std::endl;
						ostr<<e.what()<<std::endl;
						throw FatalError(ostr.str());
					}
					answersetsleft = true;
				}
				else
				{
					 if(outputline == sat)
						 answersetsleft = true;
					 else
						 answersetsleft = false;
				}

			}

			retcode = pb->close();

        }
        catch(FatalError& e)
        {
                throw e;
        }
        catch(GeneralError& e)
        {
                throw FatalError(e.getErrorMsg());
        }
        catch (std::exception& e)
        {
                throw FatalError(e.what());
        }
        if(retcode==127)
        {
                throw FatalError("clingo is not found in the specified path");
        }

}

/*
void CLSolver::processAS(std::string as, int k)
{
	std::map<AtomPtr, int> acc;
	std::map<AtomPtr, int>::iterator acc_it;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sp(" ");
	tokenizer tok(as, sp);
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
		Tuple args;
		for(int i=0; i<sz-1; i++)
		{
			boost::trim(atomv[i]);
			args.push_back(Term(atomv[i], Term::SYMBOL ));
		}
		AtomPtr atom (new Atom(args, false));

		std::ostringstream os;
		int sz = atomv.size();
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


		acc_it = acc.find(atom);
		if(acc_it == acc.end() || acc[atom] < a)
			acc[atom] = a;
	}


	for(acc_it = acc.begin(); acc_it!=acc.end(); ++acc_it)
	{
		fas.addAnswer(acc_it->first, Rational(acc_it->second, k));
	}


	std::cout<<"{";
	int i=0;
	for(acc_it = acc.begin(); acc_it!=acc.end(); ++acc_it)
	{
		i++;
		if(acc_it->second > 0)
		{
			float tv = (float) acc_it->second/k;
			std::cout<<*(acc_it->first)<<"["<<tv<<"]";


			if(i<acc.size())
				std::cout<<", "<<std::endl;
		}

	}
	std::cout<<"}"<<std::endl;

}
*/

void CLSolver::getNextAnswerSet()
{
        if(checkOnly)
        	throw FatalError("Cannot get next answer set: Solver was called with 'check only' flag!");

        //AtomSet resultAS = currentAnswer;
        std::string outputline;
        std::iostream iopipe(pb);
        iopipe.exceptions(std::ios_base::badbit);
        std::string sat("SATISFIABLE");
		std::string unsat("UNSATISFIABLE");
		if(std::getline(iopipe, outputline) && outputline!=sat && outputline != unsat )
        {
        		/*
                resultParser->parseLine(outputline);
                currentAnswer = resultParser->getAnswerSet();
				*/
				std::cout<<outputline<<std::endl;
                answersetsleft = true;
        }
        else
                answersetsleft = false;
        //return resultAS;

}



bool CLSolver::answerSetsLeft() const
{
        if(checkOnly)
        {
                return checkSatisfy;
        }
        return answersetsleft;
}


CLSolverEngine::CLSolverEngine()
{
}

ASPSolver* CLSolverEngine::createSolverFilter(bool checkOnly, std::set<std::string> filter)
{

        ASPSolver* new_solver = new CLSolver(filter, checkOnly);
        return new_solver;
}

ASPSolver* CLSolverEngine::createSolver(bool checkOnly)
{

        std::set<std::string> f;
        ASPSolver* new_solver = new CLSolver(f, checkOnly);
        return new_solver;
}
//End
