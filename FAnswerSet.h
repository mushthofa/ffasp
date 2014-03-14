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
/*

 * FAnswerSet.h
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

#ifndef FANSWERSET_H_
#define FANSWERSET_H_

#include "Atom.h"
#include <sstream>

typedef std::map<AtomPtr, Rational> Inter_t;

class FAnswerSet
{
public:
	FAnswerSet()
	{	}

	FAnswerSet(const Inter_t& a )
	:as(a)
	{}

	void addAnswer(AtomPtr a, Rational r)
	{
		as[a] = r;
	}

	void delAnswer(AtomPtr a)
	{
		Inter_t::iterator it = as.find(a);
		if(it!=as.end())
			as.erase(it);
	}

	Rational operator[](AtomPtr a)
	{
		return as[a];
	}

	std::string getStr() const
	{
		Inter_t::const_iterator it;
		std::ostringstream os;
		os<<"{";
		for(it=as.begin(); it!=as.end(); ++it)
		{

			if(it!=as.begin())
				os<<", ";
			double ratfloat = it->second.getFloat();
			os<<*(it->first)<<"["<<ratfloat<<"]";
		}
		os<<"}";
		return os.str();
	}

protected:
	Inter_t as;
};

std::ostream& operator<<(std::ostream& os, const FAnswerSet& as);


#endif /* FANSWERSET_H_ */
