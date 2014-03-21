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
 * @file   CLSolver.h
 * @author Mushthofa
 *
 * @brief  ASP solver class implemented using clingo.
 *
 */

#ifndef _CLSOLVER_H
#define _CLSOLVER_H

#include "ASPSolver.h"
#include "ProcessBuff.h"
#include <sstream>
#include <set>

class CLSolver : public ASPSolver
{
        public:
                CLSolver(std::set<std::string> filter, bool checkOnly);
                //DLVASPSolver(ASPResultParser*);
                ~CLSolver();
                void callSolver(std::string program, int k, int time);
                //AtomSet getNextAnswerSet();
                void getNextAnswerSet();
                //unsigned numAnswerSets();
                bool answerSetsLeft() const;

        private:
                ProcessBuf* pb;
                bool checkOnly;
                bool checkSatisfy;
                void processAS(std::string, int k);

};

class CLSolverEngine : public ASPSolverEngine
{

        public:
                CLSolverEngine();
                virtual ASPSolver* createSolverFilter(bool checkOnly, std::set<std::string>);
                virtual ASPSolver* createSolver(bool checkOnly);
};

#endif
//End
