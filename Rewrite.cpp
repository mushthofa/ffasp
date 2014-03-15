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

 * Rewrite.cpp
 *
 *  Created on: Feb  2014
 *      Author: mush
 */


#include "Rewrite.h"

typedef std::map<Rational, std::vector<std::pair<int, char> > > RatMap_t;

/* Check for the occurrences of constants in the head and body
 * and replace the occurrences with new predicate symbols
 */

bool Rewrite::checkRuleConstant(Program::iterator pit)
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();
	HeadList_t h = head.first;
	BodyList_t b = body.first;

	if(h.size()==1 && b.size() == 1) return false;

	int idx = 0;

	/* Map every occurrence of const in the head and body
	 *
	 */

	RatMap_t cmap;
	for(idx=0; idx<h.size(); ++idx)
	{
		AtomPtr aptr = h[idx];
		if(typeid(*aptr)==typeid(ConstantAtom))
		{
			Rational r = aptr->getRat();
			cmap[r].push_back(std::make_pair(idx,'h'));
		}
	}

	for(idx=0; idx<b.size(); ++idx)
	{
		LiteralPtr lptr = b[idx];
		AtomPtr aptr = lptr->getAtom();
		if(typeid(*aptr)==typeid(ConstantAtom))
		{
			Rational r = aptr->getRat();
			cmap[r].push_back(std::make_pair(idx, 'b'));
		}
	}

	if(cmap.empty()) return false;

	RatMap_t::iterator it;
	for(it=cmap.begin(); it!=cmap.end(); ++it)
	{
		Rational r = (*it).first;
		std::vector<std::pair<int, char> > v = (*it).second;
		if(v.empty()) continue;

		/* If constant c appear in the head, add both
		 *  p <- c.
		 *  c <- p.
		 *  Otherwise, just add
		 *  p <- c.
		 */

		int i; bool findhead = false;
		for(i=0; i<v.size(); ++i)
		{
			if(v[i].second == 'h')
				findhead = true;
		}

		std::string new_p (Program::genNextPred());
		AtomPtr aptr (new Atom(new_p, Tuple(), false));
		AtomPtr cptr (new ConstantAtom(r));
		LiteralPtr lcptr (new Literal(cptr, false));
		LiteralPtr lptr (new Literal(aptr, false));

		HeadList_t hh;
		BodyList_t bb;

		hh.push_back(aptr);
		bb.push_back(lcptr);
		RulePtr rr(new // p <- c
				Rule(std::make_pair(hh, MAX), std::make_pair(bb, MAX), "_NEW_", rules.size()));
		rules.addRule(rr, true);
		if(findhead)
		{
			hh.clear();
			bb.clear();
			hh.push_back(cptr);
			bb.push_back(lptr);
			RulePtr rr1(new // c <- p
					Rule(std::make_pair(hh, MAX), std::make_pair(bb, MAX), "_NEW_", rules.size()));
			rules.addRule(rr1, true);

		}

		for(i=0; i<v.size(); i++)
		{
			if(v[i].second == 'h')
			{
				h[v[i].first] = aptr;
			}
			else
			{	b[v[i].first] = lptr;

			}
		}

	}// for each map entry

	RulePtr newr (new
		Rule(std::make_pair(h, head.second),
		std::make_pair(b, body.second), "_NEW_", rules.size()));

	rules.addRule(newr, true);
	return true;
}

/* check for the condition when rule is of the form
 * H <- not a op not b
 * 
 * Must have no variables and no infix predicates since the body is all negative
 * rewrite into
 * H <- p1 op p2
 * p1 <- not a
 * p2 <- not b
 */

bool Rewrite::checkRule2BodyNeg(Program::iterator pit )
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();

	BodyList_t b = body.first;

	if(b.size() != 2 || !(b[0]->isNAF()) || !(b[1]->isNAF()) ) 
		return false;
	AtomPtr p1 (new Atom(Program::genNextPred(), Tuple()));
	AtomPtr p2 (new Atom(Program::genNextPred(), Tuple()));
	
	BodyList_t b1, b2;
	b1.push_back(b[0]);
	b2.push_back(b[1]);
	
	HeadList_t h1, h2;
	h1.push_back(p1);
	h2.push_back(p2);
	
	RulePtr rnew1(new Rule(std::make_pair(h1, TNORM), std::make_pair<>(b1, TNORM), "_NEW_", 0));
	RulePtr rnew2(new Rule(std::make_pair(h2, TNORM), std::make_pair<>(b2, TNORM), "_NEW_", 0));
	rules.addRule(rnew1, true);
	rules.addRule(rnew2, true);
	
	BodyList_t bnew;
	LiteralPtr lp1 (new Literal(p1));
	LiteralPtr lp2 (new Literal(p2));
	
	bnew.push_back(lp1);
	bnew.push_back(lp2);
	RulePtr rrep (new Rule(head, std::make_pair<>(bnew, body.second), "_NEW_", 0));
	rules.addRule(rrep, true);
	
	return true;
	
}

/* check for the condition when rule is of the form
 * H <- b1 op b2 op .. op bn
 * infix predicates are ignored
 * NAF literals must be rewritten first
 *
 */
bool Rewrite::checkRuleBodyOp(Program::iterator pit)
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();

	BodyList_t b = body.first;

	if(b.size() <= 2) return false;


	std::sort(b.begin(), b.end()); // put all the infix in front.

	std::vector<int> predList;	// contains real predicates
	std::vector<int> infixList; // contains infix literals

	std::set<std::string> varList;
	int idx = 0;
	while(idx<b.size())
	{
		AtomPtr aptr = b[idx]->getAtom();
		if(typeid(*aptr) != typeid(InfixAtom))
		{
			if(predList.size()>0) /* start recording vars from the second predicate */
			{
				std::set<std::string> myvar = aptr->getVariables();
				varList.insert(myvar.begin(), myvar.end());
			}
			predList.push_back(idx);
		}
		else
			infixList.push_back(idx);
		idx++;
	}


	if(predList.size()<=2)
		return false;

	/* otherwise, convert
	 *  H <- infix1..infixn op p1 op p2 op p3...op pn
	 *  into
	 *  H <- infix1..infixn op p1 op p_new
	 *  p_new <- p2 op p3 op... op pn
	 *
	 *  NAF predicates get treated first!
	*/

	/* create new predicate
	 * p_new(VAR1, ..., VARN)
	 */
	Tuple args;
	std::set<std::string>::iterator var_it;
	std::string new_p (Program::genNextPred());
	args.push_back(Term(new_p, Term::SYMBOL));
	for(var_it = varList.begin(); var_it!=varList.end(); ++var_it)
	{
		args.push_back(Term(*var_it,Term::VARIABLE ));
	}
	AtomPtr aptr (new Atom(args, false));
	LiteralPtr lptr (new Literal(aptr, false));


	BodyList_t brep;
	BodyList_t bnew;
	HeadList_t hnew;

	for(idx=0; idx<infixList.size(); idx++)
		brep.push_back(b[infixList[idx]]); 	// put all the infix first
	brep.push_back(b[predList[0]]);			// put the first pred p1
	brep.push_back(lptr);					// now put the new pred p_new

	RulePtr rrep (new
			Rule(head,
			std::make_pair(brep, body.second), "_NEW_", rules.size()));
		// H <- infix1...infixn op p1 op p_new
	rules.addRule(rrep, true);

	// Add the rest of preds in a new rule
	hnew.push_back(aptr);
	for(idx=1; idx<predList.size(); idx++)
	{
		bnew.push_back(b[predList[idx]]);
	}

	RulePtr rnew (new Rule
					(std::make_pair(hnew, MAX),
					std::make_pair(bnew, body.second), "_NEW_", rules.size()));
	rules.addRule(rnew, true);
	return true;
}

/* Check for the condition when rule is of the form
 *  H1 op H2 op ... op Hn <- B
 */

bool Rewrite::checkRuleHeadOp(Program::iterator pit)
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();

	HeadList_t h = head.first;
	FuzzyOp_t op = head.second;

	if(h.size() <= 2) return false;


	int idx;
	std::vector<int> predList;	// contains  predicates
	std::set<std::string> varList; // contains vars
	for(idx=1; idx<h.size(); idx++) // get all vars from second-->last predicates
	{
		AtomPtr a = h[idx];
		std::set<std::string> myvar = a->getVariables();
		varList.insert(myvar.begin(), myvar.end());
	}

	/* Rewrite
	 *  H1 op H2 op..op Hn <- B
	 *  into
	 *  H1 op p_new <- B
	 *  p_new <- H2 op .. op Hn
	 *  H2 op ...op Hn <- pnew
	 */



	/* create new predicate
	 * p_new(VAR1, ..., VARN)
	 */
	Tuple args;
	std::set<std::string>::iterator var_it;
	std::string new_p (Program::genNextPred());
	args.push_back(Term(new_p, Term::SYMBOL));
	for(var_it = varList.begin(); var_it!=varList.end(); ++var_it)
	{
		args.push_back(Term(*var_it,Term::VARIABLE ));
	}
	AtomPtr aptr (new Atom(args, false));
	LiteralPtr lptr (new Literal(aptr, false));



	BodyList_t brep, bnew1, bnew2;
	HeadList_t hrep, hnew1, hnew2;

	hrep.push_back(h[0]);
	hrep.push_back(aptr);


	RulePtr rrep (new
			Rule(std::make_pair(hrep, op), body, "_NEW_", rules.size()));

	// H1 op p_new <- B
	rules.addRule(rrep, true);


	hnew1.push_back(aptr);
	for(idx=1; idx<h.size(); idx++)
	{
		LiteralPtr bptr (new Literal(h[idx], false));
		bnew1.push_back(bptr);
	}

	RulePtr rnew1 (new Rule
					(std::make_pair(hnew1, op),
					std::make_pair(bnew1, op), "_NEW_", rules.size()));
	// p_new <- H2 op .. op Hn
	rules.addRule(rnew1, true);

	for(idx=1; idx<h.size(); idx++)
	{
		hnew2.push_back(h[idx]);
	}
	bnew2.push_back(lptr);

	RulePtr rnew2 (new Rule
				(std::make_pair(hnew2, op),
				std::make_pair(bnew2, op), "_NEW_", rules.size()));

	// H2 op .. op Hn <- p_new
	rules.addRule(rnew2, true);
	return true;
}


/* check for rules of the form
 * a op b <- not c
 * since only one NAF literal in the body, it must be ground
 *
 */
bool Rewrite::checkHeadCompBodyNeg(Program::iterator pit)
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();

	HeadList_t h = head.first;
	BodyList_t b = body.first;


	if(h.size()==2 && b.size()==1 && b[0]->isNAF())
	{
		/*We found one, rewrite it into
		 * a op b <- p_new
		 * p_new  <- not c
		 *
		 * Don't care about vars
		 */

		std::string strp(Program::genNextPred());
		AtomPtr aptr (new Atom(strp, Tuple()));
		LiteralPtr lptr (new Literal(aptr));
		HeadList_t hnew;
		BodyList_t bnew;

		bnew.push_back(lptr);
		RulePtr rnew1 (new Rule
				(head, std::make_pair(bnew, MAX), "_NEW_", rules.size()));
		// a op b <- p_new
		rules.addRule(rnew1, true);

		hnew.push_back(aptr);
		RulePtr rnew2 (new Rule
				(std::make_pair(hnew, MAX), body, "_NEW_", rules.size()));
		// p_new <- not c
		rules.addRule(rnew2, true);
		return true;
	}
	else
		return false;
}

/* check for rules of the form
 * a op1 b <- c op2 d
 * and rewrite them into
 * a op1 b <- pnew
 * pnew <- c op2 d
 */
bool Rewrite::checkHeadBodyComp(Program::iterator pit)
{
	RulePtr r = *pit;
	BodyExpr_t body = r->getBody();
	HeadExpr_t head = r->getHead();

	HeadList_t h = head.first;
	BodyList_t b = body.first;


	if(h.size()==2 && b.size()==2)
	{
		/*We found one, rewrite it into
		 * a op1 b <- p_new
		 * p_new  <- c op2 d
		 *
		 * Don't forget the vars
		 */

		// record the vars from c and d
		std::set<std::string> varList, myvar;
		std::set<std::string>::iterator var_it;

		myvar = b[0]->getVariables();
		varList.insert(myvar.begin(), myvar.end());
		myvar = b[1]->getVariables();
		varList.insert(myvar.begin(), myvar.end());
		std::string strp(Program::genNextPred());

		Tuple args;
		args.push_back(Term(strp, Term::SYMBOL));
		for(var_it=varList.begin(); var_it!=varList.end(); ++var_it)
			args.push_back(Term(*var_it, Term::VARIABLE));

		AtomPtr aptr (new Atom(args));
		LiteralPtr lptr (new Literal(aptr));
		HeadList_t hnew;
		BodyList_t bnew;

		bnew.push_back(lptr);
		RulePtr rnew1 (new Rule
				(head, std::make_pair(bnew, MAX), "_NEW_", rules.size()));
		// a op b <- p_new
		rules.addRule(rnew1, true);

		hnew.push_back(aptr);
		RulePtr rnew2 (new Rule
				(std::make_pair(hnew, MAX), body, "_NEW_", rules.size()));
		// p_new <- not c
		rules.addRule(rnew2, true);
		return true;
	}
	else
		return false;
}

void Rewrite::doRewrite()
{
	int change;

	// replacing constants need to be done only once

	do
	{

		Program::iterator it = rules.begin();
		change = 0;
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkRuleConstant(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}
	}
	while(change>0);


	// rewriting need to be done continuously until no change occurs
	do
	{

		Program::iterator it = rules.begin();
		change = 0;
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkRuleBodyOp(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}
		it = rules.begin();
		
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkRule2BodyNeg(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}
		it = rules.begin();
		
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkRuleHeadOp(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}

		it = rules.begin();
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkHeadCompBodyNeg(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}

		it = rules.begin();
		while(it!=rules.end())
		{
			Program::iterator cur = it++;
			if(checkHeadBodyComp(cur))
			{
				rules.deleteRule(cur);
				change++;
			}
		}
	}
	while(change>0);

	done = true;

}


