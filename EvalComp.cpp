/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa   								*
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
 * @file   EvalComp.cpp
 * @author Mushthofa
 *
 * 
 * @brief  Evaluation of one component
 * 
 * 
 */

#include "EvalComp.h"
#include "ASPEval.h"
#include "CLSolver.h"

unsigned c = 0;
EvalEmpty::EvalEmpty()
	:EvalComp()
{
}

EvalEmpty::~EvalEmpty()
{
}

void EvalEmpty::setInput(const Program& p, const FAnswerSet& f)
{
	/* FFASP: Assume facts are always consistent
	if(f.isConsistent())
	{
		currentAnswerSet = f;
		answersetsleft = true;
	}
	else
		answersetsleft = false;
	*/

	currentAnswerSet = f;
	answersetsleft = true;
}

void EvalEmpty::doEval()
{
	answersetsleft = false;
}

void EvalEmpty::clearInput()
{
	answersetsleft = true;
}



EvalDirect::EvalDirect(ASPSolverEngine* se)
:solverEngine(se)
{}

EvalDirect::~EvalDirect()
{
	//std::cout<<"deleting solver"<<std::endl;
	//delete solver;
}

void EvalDirect::setInput(const Program& p, const FAnswerSet& f)
{
	IDB = p;
	EDB = f;
	doEval();
}

void EvalDirect::doEval()
{

}

void EvalDirect::clearInput()
{
	answersetsleft = false;
}

//End

