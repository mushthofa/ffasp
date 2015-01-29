/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa   								*
 *   unintendedchoice@gmail.com   									*
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
 * @file   EvalComp.h
 * @author Mushthofa
 *
 * 
 * @brief  Evaluation of one component
 * 
 * 
 */

#ifndef _EVALCOMP_H
#define _EVALCOMP_H

#include "ASPSolver.h"
#include "FAnswerSet.h"

/* Abstract base class */
class EvalComp
{
	public:
		EvalComp()
		:answersetsleft(false)
		{}
		virtual ~EvalComp()
		{}
		virtual void setInput(const Program& , const FAnswerSet& f) = 0;
		virtual void clearInput() = 0;
		
		bool answerSetsLeft() const
		{
			return answersetsleft;
		}
		
		FAnswerSet getNextAnswerSet()
		{
			FAnswerSet result = currentAnswerSet;
			doEval();
			return result;	
		}
		
		
	protected:
		virtual void doEval() = 0;
		
		Program IDB;
		FAnswerSet EDB;
		FAnswerSet currentAnswerSet;
		bool answersetsleft;
		

};

/* Empty component evaluation class */
/* Dummy evaluation to simulate other non-empty component's evaluation */

class EvalEmpty : public EvalComp
{
	public:
		EvalEmpty();
		~EvalEmpty();
		
		virtual void setInput(const Program&, const FAnswerSet& f);
		
		virtual void clearInput();
		
		virtual void doEval();
		
	protected:
		
};


/* Direct Evaluation by ASP Solver */

class EvalDirect : public EvalComp
{
	public:
		EvalDirect(ASPSolverEngine*);
		~EvalDirect();
		
		virtual void setInput(const Program&, const FAnswerSet& f);
		
		virtual void clearInput();
		

	protected:
		virtual void doEval();
		
		ASPSolverEngine* solverEngine;
		
};

#endif
// End
