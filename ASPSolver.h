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
 * @file   ASPSolver.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  ASP solver base class.
 *
 */

#ifndef _ASPSOLVER_H
#define _ASPSOLVER_H

#include <iostream>
#include <string>
#include <vector>

#include "ProcessBuff.h"
#include "Error.h"
#include "Globals.h"
#include "AtomSet.h"
#include "Program.h"
#include "ASPResultParser.h"



/**
 * @brief ASP solver class.
 */
class ASPSolver
{
        public:


                ASPSolver()
                :answersetsleft(false)//, resultParser(rp)
                {}
                virtual ~ASPSolver()
                {
                        //delete resultParser;
                }
                /**
                * @brief Calls the answer set solver with a program.
                *
                *
                *
                */
                virtual void callSolver(std::string program, int, int) = 0;

                /**
                 * @brief Retrieves an Answer set, incrementing the internal result pointer.
                 *
                 *
                 */
                virtual void getNextAnswerSet() = 0;

                /**
                 * @brief Returns the number of answer sets of the last result.
                 */
                //virtual unsigned numAnswerSets() = 0;

                virtual bool answerSetsLeft() const = 0;


        protected:

                /**
                 * @brief System command to call the external asp reasoner.
                 */
                std::string lpcommand;

                /**
                 * @brief List of arguments supplied
                 */

                std::vector<std::string> lpargs;

                /**
                 * @brief Internal result
                 */

                AtomSet currentAnswer;

                /* Is there any answers left */
                bool answersetsleft;

                /* Program string */


                /* Result Parser */

                //ASPResultParser* resultParser;


};

/* The class to store ASP Solver factory */

typedef boost::shared_ptr<ASPSolver> ASPSolverPtr;
class ASPSolverEngine
{
        public:
                ASPSolverEngine()
                {}
                /* Create one instance of the solver */

                virtual ASPSolver* createSolverFilter(bool checkOnly, std::set<std::string>) = 0;
                virtual ASPSolver* createSolver(bool checkOnly) = 0;
                virtual ~ASPSolverEngine() {}

        protected:
};


#endif // _ASPSOLVER_H

//End
