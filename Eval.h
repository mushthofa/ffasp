/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                             *
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
/*

* Eval.h
 *
 *  Created on: Feb, 2014
 *      Author: mush
 */

#ifndef EVAL_H_
#define EVAL_H_


#include "Program.h"
#include "FAnswerSet.h"

typedef std::pair<int, time_t> stop_t;

class Eval
{
public:
	Eval(int k, int s)
	:curr_k(k), step(s), asleft(false)
	{}

	Eval(const Program& p, stop_t st, int k, int s)
	: curr_k(k), step(s), stop(st),  program(p), asleft(false)
	{
	}

	virtual ~Eval()
	{}

	virtual FAnswerSet getNextAnswerSet() = 0;

	virtual bool answersetsLeft() = 0;


	virtual bool doSolve() = 0;



protected:
	int curr_k;
	int step ;
	stop_t stop;
	Program program;
	std::set<std::string> strAS;
	std::vector<FAnswerSet> fas;

	bool asleft;
};


#endif /* EVAL_H_ */
