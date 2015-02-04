/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                       *
 *   Mushthofa.Mushthofa@Ugent.						*
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
 * @file   ffasp.cpp
 * @author Mushthofa
 *
 * @brief  Implementation of Fuzzy ASP solver
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include "SpiritProgramParser.h"
#include "ASPEval.h"
#include "CLSolver.h"
#include "Rewrite.h"
#include "GraphBuilder.h"
#include "BoostComponentFinder.h"
#include "DependencyGraph.h"
#include "GraphProcessor.h"

#include <ctime>

void showUsage(char* prog)
{
	std::cout<<"FFASP -- A finite-valued fuzzy answer set solver -- "<<std::endl;
	std::cout<<"build 03/2014"<<std::endl;
	std::cout<<"(c) Ghent University, BE"<<std::endl;
	std::cout<<std::endl<<"USAGE: \t"<<prog<<" [options] [<input-file>]"<<std::endl<<std::endl;
	std::cout<<"E.g.: \t"<<prog<<" --maxk=200 -c program.lp"<<std::endl<<std::endl;
	std::cout<<"Options are:"<<std::endl;
	std::cout<<"--maxk=<n> \t= find k-answer sets up to k=<n> (default <n>=100)."<<std::endl;
	std::cout<<"--maxt=<t> \t= stop after computation exceeds <t> seconds, approximately (default <t>=600 s)."<<std::endl;
	std::cout<<"--trans=<k> \t= only perform translation with k=<k> and print the result to <STDOUT>."<<std::endl;
	std::cout<<"--rnd=<d> \t= only perform rewriting of the program and rounding the constants "<<std::endl
				<<"\t\t  in the program to rational numbers with denominator=<d>."<<std::endl;
	std::cout<<"-c/--check \t= only check for satisfiability/consistency, no answer set is printed."<<std::endl;
	std::cout<<"-h/--help  \t= show this help and exit."<<std::endl;
	std::cout<<"If no <input-file> is given, input is read from <STDIN>"<<std::endl<<std::endl;

}

int main(int argc, char *argv[])
{

        GetPot cl(argc, argv);
        Globals::Instance()->processArgs(cl);

        if(Globals::Instance()->boolOption("help"))
        {
                showUsage(argv[0]);
                return 0;
        }
        Program p;

        /* Read and parse input */

        ProgramParser* parser;
        try
        {
                parser = new SpiritProgramParser();
                //EDB = parser->getEDB();
                p = parser->getRules();

        }
        catch(GeneralError& e)
        {
                std::cerr << e.getErrorMsg() << std::endl;
                //delete parser;
                return 1;
        }

        delete parser;

       /* Just for conversion purposes.
        *
        */
        if(Globals::Instance()->intOption("rp")>0)
        {
        	std::cout<<p<<std::endl;
        	return 0;
        }



        /* Rewrite the program
		*
		*/
        Rewrite* rw = new Rewrite(p);
        Program rewp;
        try
        {
        	rewp = rw->getStandard();
        }
        catch(GeneralError& err)
        {
        	std::cout<<"Error rewriting program: "<<err.getErrorMsg()<<std::endl;
        	delete rw;
        	return 1;
        }

        delete rw;


        //std::cout<<"done rewriting.."<<std::endl;
        //std::cout<<"program after rewritten : "<<std::endl<<rewp<<std::endl;
        //return 0


        GraphBuilder gb;

		NodeGraph nodegraph;

		try
		{
				// Build the graph of dependency between atoms
				gb.run(rewp, nodegraph);
		}
		catch (GeneralError& e)
		{
				std::cerr << e.getErrorMsg() << std::endl << std::endl;

				return EXIT_FAILURE;
		}



		//gb.dumpGraph(nodegraph, std::cout);
		//return EXIT_SUCCESS;


		ComponentFinder* cf;

		//
		// The DependencyGraph identifies and creates the graph components that will
		// be processed by the GraphProcessor.
		//
		DependencyGraph* dg;

		try
		{
				cf = new BoostComponentFinder();

				//
				// Initializing the DependencyGraph. Its constructor uses the
				// ComponentFinder to find relevant graph
				// properties for the subsequent processing stage.
				//
				dg = new DependencyGraph(nodegraph, cf);
		}
		catch (GeneralError &e)
		{
				std::cerr << e.getErrorMsg() << std::endl << std::endl;

				delete cf;
				delete dg;
				return EXIT_FAILURE;
		}



		/*
		std::cout<<"Program Components: "<<std::endl;
		std::vector<Component*> comps = dg->getComponents();
		std::vector<Component*>::iterator cit;
		for(cit = comps.begin(); cit!=comps.end(); ++cit)
		{
			if((*cit)->getBottom().size() > 0)
				(*cit)->dump(std::cout);
		}

		*/

		//delete cf;
		//return EXIT_SUCCESS;



        /* If called with --trans=<n> option, just translate and return immediately
         *
         */

        int trans_k = Globals::Instance()->intOption("trans");
        if(trans_k>0)
        {
        	ASPTranslate* tr;//, *tr1;
			try
			{
				tr = new ASPTranslate(rewp, trans_k);
				//tr1 = new ASPTranslate(rewp, trans_k);
			}
			catch(GeneralError& err)
			{

				std::ostringstream oserr;
				oserr<<"Error translating program for k = "<<  trans_k  << ": "
						<<std::endl<< err.getErrorMsg();
				std::cout<<oserr.str()<<std::endl;
				//throw FatalError(oserr.str());
				//delete tr;
				return 1;
			}



			std::string trans = tr->getProgram();
			//trans = tr1->getProgram();
			std::cout<<trans<<std::endl;
			delete tr;
			return EXIT_SUCCESS;
        }



        /*
        // Get evaluation options
        int maxk = Globals::Instance()->intOption("maxk");
        int maxtime = Globals::Instance()->intOption("maxt");
        //bool printAS = !Globals::Instance()->boolOption("check");

        stop_t stop = std::make_pair(maxk, maxtime);
        int step = lcm(ConstantAtom::denomList);

        ASPSolverEngine* eng = new CLSolverEngine();
        Eval* eval;

        try
        {
        	eval  = new ASPEval(eng, rewp, stop, step, step);
        }
        catch(GeneralError& err)
        {
        	std::cout<<"Error evaluating program using ASP eval: "<<std::endl;
        	std::cout<<err.getErrorMsg()<<std::endl;
        	//delete eval;
        	//delete eng;
        	return 1;
        }



        while(eval->answersetsLeft())
        {
        	FAnswerSet as = eval->getNextAnswerSet();
        	std::cout<<as;
        }


        delete eval;
        delete eng;
        */

        //ASPSolverEngine* eng = new CLSolverEngine();

    	GraphProcessor* gp;
    	gp = new GraphProcessor(dg);//, eng);

    	try
    	{
    		gp->run();
    	}
    	catch(GeneralError& err)
    	{
    		std::cout<<"Error evaluating component "<<std::endl;
    		std::cout<<err.getErrorMsg()<<std::endl;
    		delete cf; delete dg; delete gp;
    		return EXIT_FAILURE;
    	}

    	delete cf; delete dg; delete gp;
        return EXIT_SUCCESS;
}
