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
 * @file   DLVASPSolver.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  ASP solver class implemented using dlv.
 *
 */


#include "DLVASPSolver.h"
#include "DLVResultParser.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>

DLVASPSolver::DLVASPSolver(ASPResultParser* rp, std::set<std::string> filter, bool co)
        :checkOnly(co), checkSatisfy(false), resultParser(rp)
	{
        /* Get dlv's path and arguments from command line */

        lpcommand = Globals::Instance()->strOption("solver");
        lpargs.push_back(lpcommand);
        lpargs.push_back("-silent");
        lpargs.push_back("--");
        lpargs.push_back("-n=1");
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

        /*
        for(boost::tokenizer<>::iterator args_it = args.begin(); args_it!=args.end(); ++args_it)
        {
                lpargs.push_back(*args_it);
        }
		*/


        pb = new ProcessBuf();
        /*
        answerSets.clear();
        answerSetIndex = answerSets.end();
        */
}

/*
DLVASPSolver::DLVASPSolver(ASPResultParser* rp)
        :ASPSolver(rp), checkOnly(false), checkSatisfy(false)
{


        lpcommand = Globals::Instance()->strOption("DLVPath");
        boost::tokenizer<> args (Globals::Instance()->strOption("DLVArgs"));
        lpargs.push_back(lpcommand);
        lpargs.push_back("-silent");
        lpargs.push_back("--");

        for(boost::tokenizer<>::iterator args_it = args.begin(); args_it!=args.end(); ++args_it)
        {
                lpargs.push_back(*args_it);
        }

        pb = new ProcessBuf();

}

*/

DLVASPSolver::~DLVASPSolver()
{
        delete pb;
}

void DLVASPSolver::callSolver(std::string program, int k)
{
        //answerSets.clear();


        int retcode = 0;
        if(pb->isOpen())
                retcode = pb->close();

        try
        {
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

                /*std::cout<<"DLV Result: "<<std::endl;
                */
                std::string outputline;

                if(checkOnly)
                {

                        std::getline(iopipe, outputline);
                        if(outputline.size() >= 2) // atleast {}
                                checkSatisfy = true;
                        else
                                checkSatisfy = false;
                }
                else
                {
                        //std::cout<<"parsing dlv result"<<outputline<<std::endl;
                        if(std::getline(iopipe, outputline))
                        {

                                try
                                {
                                        resultParser->parseLine(outputline);
                                }
                                catch(GeneralError& e)
                                {
                                        std::ostringstream err;
                                        err << e.getErrorMsg() << std::endl;
                                        err << " Program was : " <<std::endl
                                        		<< program <<std::endl;

                                        throw FatalError(err.str());
                                }
                                currentAnswer= resultParser->getAnswerSet();

                                answersetsleft = true;
                        }
                        else
                                answersetsleft = false;

                }
                //retcode = pb.close();

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
                throw FatalError("DLV is not found in the specified path");
        }

}

//
void DLVASPSolver::getNextAnswerSet()
{
        if(checkOnly)
        	throw FatalError("Cannot get next answer set: Solver was called with 'check only' flag!");

        AtomSet resultAS = currentAnswer;
        std::string outputline;
        std::iostream iopipe(pb);
        iopipe.exceptions(std::ios_base::badbit);
        if(std::getline(iopipe, outputline))
        {
                resultParser->parseLine(outputline);
                currentAnswer = resultParser->getAnswerSet();

                answersetsleft = true;
        }
        else
                answersetsleft = false;
        //return resultAS;
        std::cout<<resultAS<<std::endl;

}



bool DLVASPSolver::answerSetsLeft() const
{
        if(checkOnly)
        {
                return checkSatisfy;
        }
        return answersetsleft;
}


DLVASPSolverEngine::DLVASPSolverEngine()
{

}

ASPSolver* DLVASPSolverEngine::createSolverFilter(bool checkonly, std::set<std::string> filter)
{
        ASPResultParser* rp = new DLVResultParser();

        ASPSolver* new_solver = new DLVASPSolver(rp, filter, checkonly) ;
        return new_solver;
}

ASPSolver* DLVASPSolverEngine::createSolver(bool checkonly)
{
        ASPResultParser* rp = new DLVResultParser();

        std::set<std::string> f;
        ASPSolver* new_solver = new DLVASPSolver(rp, f, checkonly);
        return new_solver;
}
//End
