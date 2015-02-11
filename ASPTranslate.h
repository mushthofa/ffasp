/***************************************************************************
*   Copyright (C) 2014 by Mushthofa                                        *
*   Mushthofa.Mushthofa@Ugent.be                                           *
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
 * ASPTranslate.h
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

#ifndef ASPTRANSLATE_H_
#define ASPTRANSLATE_H_

#include "Program.h"

class ASPTranslate
{

public:

	/* Types of standard rules:
	 * 1) ONEHB: one (real) predicate in the head and body, e.g.:
	 * a <- p(X,Y)*X<Y.
	 *
	 * 2) FACT, e.g.
	 * a <- #c
	 *
	 * 3) CONSTR, e.g.
	 * #c <- a.
	 *
	 * 4) BTNORM, t-norm in the body, one head atom, e.g. (may contain infix)
	 * [also include when one of the body literals is  NAF]
	 * a <- b(X,Y) * c * X<Y
	 *
	 * 5) BCOTNORM, co-tnorm in the body, one head atom, e.g.
	 * [also include when one of the body literals is  NAF]
	 * a <- b+c.
	 *
	 * 6) BMAX, max in the body, e.g.
	 * [also include when one of the body literals is  NAF]
	 * a <- b&c
	 *
	 * 7) BMIN, min in the body, e.g.
	 * [also include when one of the body literals is  NAF]
	 * a <- b^c
	 *
	 * 8) HTNORM, tnorm in the head, one literal in the body, e.g.
	 * a*b <- c
	 *
	 * 9)HCOTNORM, cotnorm in the head, one literal in the body, e.g.
	 * a+b <- p(X,Y)*X<Y.
	 *
	 * 10) HMAX, max in the head, e.g.
	 * a&b <- c.
	 *
	 * 11) HMIN, min in the head, e.g.
	 * a^b <- c.
	 *
	 * 12) BNAF, negation in the body, e.g.
	 * a <- not b
	 *
	 * 13) INV, invalid/unhandled type.
	 *
	 */

	typedef enum {ONEHB, FACT, CONSTR, BTNORM, BCOTNORM, BMAX, BMIN,
				HTNORM, HCOTNORM, HMAX, HMIN, BNAF, INV} RuleType_t;

	ASPTranslate(const Program& p, int kk)
	:program(p), needmincheck(false), anydisj(false), k(kk)
	{

		// Compute all non-SRCF Atoms
		getNonSRCFAtoms();
		if(nonSRCFAtoms.size()>0 && anydisj)
			needmincheck = true;
		// Do shift for disj rules with SRCF atoms
		//std::cout<<"Non SRCF = "<<nonSRCFAtoms.size()<<std::endl;
		//std::set<AtomPtr>::iterator it;
		//for(it=nonSRCFAtoms.begin(); it!=nonSRCFAtoms.end(); ++it)
			//std::cout<<*(*it)<<std::endl;

		doShift();

		doTranslate(); // translate rules
		addConsRule(); // add rules p_0 <- , p_i <- p_{i+1}
	}

	std::string getProgram() const
	{
		return os.str();
	}

	bool needMinCheck()
	{
		return needmincheck;
	}

protected:

	void getNonSRCFAtoms()
	{
		// Get all the non-SRCF Atoms;
		// by finding all atoms that are disjunct in the head
		// and disjunct in the body as well.

		std::set<AtomPtr> headDisj;
		std::set<AtomPtr> bodyDisj;

		Program::const_iterator it;
		for(it=program.begin(); it!=program.end(); ++it)
		{
			HeadExpr_t head = (*it)->getHead();
			BodyExpr_t body = (*it)->getBody();

			HeadList_t hl = head.first;
			BodyList_t bl = body.first;
			if(hl.size()==2 && head.second == CO_TNORM)
			{
				anydisj = true;
				//
				//if(hl[0]->getPredicateName().find("_NEW_") == std::string::npos)
					headDisj.insert(hl[0]);
				//if(hl[1]->getPredicateName().find("_NEW_") == std::string::npos)
					headDisj.insert(hl[1]);
			}

			if(bl.size() == 2 && body.second == CO_TNORM)
			{
				//
				//if(bl[0]->getAtom()->getPredicateName().find("_NEW_") == std::string::npos)
					bodyDisj.insert(bl[0]->getAtom());
				//if(bl[1]->getAtom()->getPredicateName().find("_NEW_") == std::string::npos)
					bodyDisj.insert(bl[1]->getAtom());
			}
		}

		// Take intersection;

		std::set_intersection(headDisj.begin(), headDisj.end(), bodyDisj.begin(), bodyDisj.end(),
				std::inserter(nonSRCFAtoms, nonSRCFAtoms.begin()));

	}



	void doShift()
	{
		/*
		 * Do shifting on all disjunctive rules
		 */

		//std::cout<<"Do shifting "<<std::endl;
		Program::iterator it = program.begin();

		while(it!=program.end())
		{
			Program::iterator now = it++;
			HeadExpr_t head = (*now)->getHead();

			BodyExpr_t body = (*now)->getBody();

			HeadList_t hl = head.first;
			BodyList_t bl = body.first;

			//cout<<"Rule "<<(*(*now))<<std::endl;
			//cout<<"Head size "<<hl.size()<<" operator = "<<head.second<<std::endl;
			// Check if disjunctive rule
			if(hl.size()!=2 || head.second!=CO_TNORM)
				continue;

			if(nonSRCFAtoms.find(hl[0])!=nonSRCFAtoms.end()
				|| nonSRCFAtoms.find(hl[1])!=nonSRCFAtoms.end())
				continue;

			// Replace a+b <- c
			// into
			// a <- c x p1
			// b <- c x p2
			// p1 <- not b
			// p2 <- not a

			AtomPtr p1 (new Atom(Program::genNextPred(), Tuple()));
			AtomPtr p2 (new Atom(Program::genNextPred(), Tuple()));

			AtomPtr a = hl[0];
			AtomPtr b = hl[1];

			// Create new body lists

			BodyList_t b1 = bl, b2 = bl;
			b1.push_back(LiteralPtr(new Literal(p1)));
			b2.push_back(LiteralPtr(new Literal(p2)));

			BodyExpr_t body1, body2;
			body1.first = b1;
			body2.first = b2;
			body1.second = TNORM;
			body2.second = TNORM;

			// Set up the heads;

			HeadList_t hl1, hl2;
			hl1.push_back(b);
			hl2.push_back(a);


			//std::cout<<"Deleting rule "<<*(*now)<<std::endl;
			program.deleteRule(now);

			RulePtr r1 (new Rule(std::make_pair(hl1, MAX), body1, "_NEW_", program.size()));
			RulePtr r2 (new Rule(std::make_pair(hl2, MAX), body2, "_NEW_", program.size()));

			//std::cout<<"adding rule "<<*r1<<"and "<<*r2<<std::endl;
			program.addRule(r1);
			program.addRule(r2);

			hl1.clear();
			hl2.clear();
			b1.clear();
			b2.clear();

			hl1.push_back(p1);
			hl2.push_back(p2);

			b1.push_back(LiteralPtr(new Literal(a, true)));
			b2.push_back(LiteralPtr(new Literal(b, true)));
			body1.first = b1;
			body2.first = b2;

			RulePtr r3 (new Rule(std::make_pair(hl1, MAX), body1, "_VIRT_", program.size()));
			RulePtr r4 (new Rule(std::make_pair(hl2, MAX), body2, "_VIRT_", program.size()));
			//std::cout<<"adding rule "<<*r3<<"and "<<*r4<<std::endl;
			program.addRule(r3);
			program.addRule(r4);

		}

	}


	/* During translate, rules are converted to string rep
	 * and accumulated in os,
	 * doTranslate() recaps all the translation
	 * addConsRule() adds the auxiliary rules a_i <- a_i+1}
	 * translateXYX() are rules that perform translation for rules of type XYZ
	 */


	void doTranslate();
	void translateRule(RulePtr r);
	void addConsRule();
	void translateONEHB(RulePtr r);
	void translateBNAF(RulePtr r);
	void translateBTNORM(RulePtr r);
	void translateBCOTNORM(RulePtr r);
	void translateFACT(RulePtr);
	void translateCONSTR(RulePtr);
	void translateBMIN(RulePtr);
	void translateBMAX(RulePtr);
	void translateHTNORM(RulePtr );
	void translateHCOTNORM(RulePtr);
	void translateHMAX(RulePtr);
	void translateHMIN(RulePtr);

	RuleType_t detType(RulePtr r);

	std::ostringstream os;
	Program program;
	std::set<AtomPtr> nonSRCFAtoms;
	bool needmincheck;
	bool anydisj;
	int k;

};



#endif /* ASPTRANSLATE_H_ */
