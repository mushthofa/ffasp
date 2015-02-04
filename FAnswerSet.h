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
#include "Program.h"
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

	void clear()
	{
		as.clear();
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
			int num = it->second.getNom();
			int denom = it->second.getDenom();
			os<<*(it->first)<<"["<<num<<"/"<<denom<<"]";
		}
		os<<"}";
		return os.str();
	}

	std::string getStrClean() const
	{
		Inter_t::const_iterator it;
		std::ostringstream os;
		os<<"{";
		for(it=as.begin(); it!=as.end(); ++it)
		{
			std::string predName = it->first->getPredicateName();

			if(predName.find("_NEW_")!=string::npos)
						continue;
			if(it!=as.begin())
				os<<", ";
			float truthval = it->second.getFloat();
			os<<*(it->first)<<"["<<truthval<<"]";
		}
		os<<"}";
		return os.str();
	}


	/* Translate any interpretation into a set of fuzzy facts
	 * a[x], b[y], ....
	 * into
	 * a <- #x.
	 * b <- #y.
	 * ....
	 */


	Program getFacts() const
	{
		Inter_t::const_iterator it;
		Program result;
		int c=0;
		for(it=as.begin(); it!=as.end(); ++it)
		{
			HeadList_t hl;
			hl.push_back(it->first);
			AtomPtr b(new ConstantAtom(it->second));
			LiteralPtr lptr (new Literal (b));
			BodyList_t bl;
			bl.push_back(lptr);
			RulePtr rr(new
				Rule(std::make_pair(hl, MAX), std::make_pair(bl, MAX), "_NEW_", c++));
			result.addRule(rr);
		}
		return result;
	}

	bool operator<(const FAnswerSet& x) const
	{
		Inter_t::const_iterator it, itfind;
		for(it=as.begin(); it!=as.end(); ++it)
		{
			itfind = x.as.find(it->first);
			if(itfind==x.as.end() || itfind->second < it->second)
				return false;
		}
		return true;
	}


	/* Merge two answer sets into one, finding the largest truth value I(a) from both
	 *
	 */

	FAnswerSet merge(const FAnswerSet& other) const
	{
		Inter_t o = other.as;
		Inter_t res = as;
		for(Inter_t::iterator it = o.begin(); it!= o.end(); ++it)
		{
			if(res.find(it->first) == res.end() || res[it->first] < it->second )
				res[it->first] = it->second;
		}

		return FAnswerSet(res);
	}


	int getDenomLCM() const
	{
		Inter_t::const_iterator it;
		int res = 1;
		for(it=as.begin(); it!=as.end(); ++it)
			res = lcm(res, it->second.getDenom());

		return res;
	}
protected:
	Inter_t as;
};



std::ostream& operator<<(std::ostream& os, const FAnswerSet& as);


#endif /* FANSWERSET_H_ */
