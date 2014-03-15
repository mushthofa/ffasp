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
 * ASPTranslate.cpp
 *
 *  Created on: Feb  2014
 *      Author: mush
 */

#include "ASPTranslate.h"
#include <boost/concept_check.hpp>
#include <boost/lexical_cast.hpp>

void ASPTranslate::doTranslate()
{
	Program::iterator it;
	for(it=program.begin(); it!=program.end(); ++it)
	{
		translateRule(*it);
	}
}

void ASPTranslate::addConsRule()
{
	// Add rules
	// p_i <- p_{i+1}
	//

	MapSign_t predsign = program.getPredicates();
	MapSign_t::iterator it;
	for(it=predsign.begin(); it!=predsign.end(); ++it)
	{
		int i,j;

		// p(_,..,0) <-

		/*
		os<<it->first<<"(";
		for(i=1; i<=it->second; i++)
			os<<"_,"; // fill with anonymuous vars;
		os<<"0)."<<std::endl;

		*/


		for(i=1; i<k; i++)
		{
			os<<it->first<<"(";
			int varid = 0;
			for(j=1; j<=it->second; j++)
				os<<"VAR_"<<varid++<<", "; // fill with variables
			os<<i<<") :- "<<it->first<<"(";
			varid = 0;
			for(j=1; j<=it->second; j++)
				os<<"VAR_"<<varid++<<", "; // fill with variables
			os<<i+1<<")."<<std::endl;
		}
	}
}

void ASPTranslate::translateFACT(RulePtr r)
{
	/* Translate
	 * p <- #c
	 * into
	 * p_i <-
	 * where i=#c*k
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;

	if(hl.size()!=1 && bl.size()!=1)
		throw FatalError("translateFACT: wrong rule type!");
	AtomPtr hpred = hl[0];
	AtomPtr bpred = bl[0]->getAtom();
	if(typeid(*hpred) == typeid(ConstantAtom)
		|| typeid(*bpred)!=typeid(ConstantAtom))
		throw FatalError("translateFACT: wrong rule type!");

	Rational rat = bpred->getRat();
	int val = rat.getNom() * k/rat.getDenom();
	if(val>0)
	{
		Atom a = *hpred;
		a.addTerm(val);
		os << a <<". "<<std::endl;
	}

}


void ASPTranslate::translateCONSTR(RulePtr r)
{
	/* Translate
	 * #c <- p
	 * into
	 * <- p_{i+1}
	 * where i=#c*k and i<k
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;

	if(hl.size()!=1 && bl.size()!=1)
		throw FatalError("translateCONSTR: wrong rule type!");
	AtomPtr hpred = hl[0];
	AtomPtr bpred = bl[0]->getAtom();

	if(typeid(*hpred) != typeid(ConstantAtom)
		|| typeid(*bpred) == typeid(ConstantAtom))
		throw FatalError("translateCONSTR: wrong rule type!");

	Rational rat = hpred->getRat();
	int val = rat.getNom() * k/rat.getDenom();
	++val;
	if(val>0)
	{
		Atom a = *bpred;
		a.addTerm(val);
		os << ":- "<< a <<". "<<std::endl;
	}
}

void ASPTranslate::translateONEHB(RulePtr r)
{
	/* Just distribute truth values over 1 to k
	 * e.g.
	 *
	 * p(X,Y) <- q(X,Y)*X<Y
	 *
	 * into
	 * p(X,Y,i) <- q(X,Y,i) , X<Y. [1<=i<=k]
	 *
	 * Infix predicate can only appear in T-norm body
	 *
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	//FuzzyOp_t oph = head.second;
	//FuzzyOp_t opb = body.second;

	/* sort body so real predicate appears in the last of the rule
	 *
	 */
	int i;
	std::sort(bl.begin(), bl.end());
	LiteralPtr blitpred = bl[bl.size()-1];

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-1; i++)
		infix.push_back(bl[i]);

	if(hl.size()!=1 || (bl.size() - infix.size())!=1)
		throw FatalError("translateONEBH: wrong rule type!");

	// generate output
	for(i=1; i<=k; i++)
	{
		Atom bpred = *(blitpred->getAtom());
		Atom hpred = *hl[0];
		// add argument to the predicates
		hpred.addTerm(i);
		bpred.addTerm(i);

		os << hpred <<" :- ";
		int j;
		for(j=0; j<infix.size(); j++)
			os<<*infix[j]<<", ";
		os << bpred << "." << std::endl;
	}

}

void ASPTranslate::translateBNAF(RulePtr r)
{
	/* Translate
	 * a <- not b
	 * into
	 * a_i <- not b_{k-i+1} [1<=i<=k]
	 * Note that since only one body literal and it's NAF,
	 * no infix atom nor variables can appear. Easy!
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;

	int i;
	for(i=1; i<=k; i++)
	{
		Atom bpred =  *(bl[0]->getAtom());
		Atom hpred =  *hl[0];
		// add argument to the predicates
		hpred.addTerm(i);
		bpred.addTerm(k-i+1);

		os << hpred <<" :- ";
		os << "not " << bpred << "." << std::endl;
	}

}

void ASPTranslate::translateBTNORM(RulePtr  r)
{
	/* Translate
	 * a <- b*c [may contain infix atoms]
	 * [also include when one of the body literals is  NAF]
	 * into
	 * a1 <- b1 * ck
	 * ..
	 * a1 <- bk * ck1
	 * ..
	 *
	 * ak <- bk * ck
	 * i.e.
	 *
	 * ai <- bj * c[k-j+i] [1<=i<=k, i<=j<=k]
	 *
	 */


	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(bl.size()<2 || hl.size()!=1)
		throw FatalError("translateBTNORM: wrong rule type!");
	int i;

	// sort the body literals, two of the last literals are real predicates.
	std::sort(bl.begin(), bl.end());

	LiteralPtr blitpred1 = bl[bl.size()-2]; // if there is a NAF, it must be blitpred1
	LiteralPtr blitpred2 = bl[bl.size()-1];

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-2; i++)	// up to before the last two
		infix.push_back(bl[i]);

	bool isnaf = blitpred1->isNAF(); // is one of the NAF?
	std::string notstr = (isnaf)?std::string("not "):std::string("");

	for(i=1; i<=k; i++)
	{
		int j;
		for(j=i; j<=k; j++)
		{
			Atom bpred1 = *(blitpred1->getAtom());
			Atom bpred2 = *(blitpred2->getAtom());
			Atom hpred = *hl[0];
			// add argument to the predicates
			hpred.addTerm(i);
			if(isnaf)
				bpred1.addTerm(k-j+1);
			else
				bpred1.addTerm(j);
			bpred2.addTerm(k-j+i);

			os << hpred <<" :- ";
			int l;
			for(l=0; l<infix.size(); l++)
				os<<*infix[l]<<", ";

			os << notstr << bpred1 << ", "<< bpred2<<"." << std::endl;
		}
	}
}

void ASPTranslate::translateBCOTNORM(RulePtr  r)
{
	/* Translate
	 * a <- b+c [no infix atoms]
	 * into
	 * a1 <- b1
	 * a1 <-  c1
	 * a2 <-  c2
	 * ..
	 * a2 <- b2 , c2
	 * ..
	 * ak <- ck
	 * ak <- b1, ck-1
	 * ..
	 * ak <- bk
	 * i.e.
	 *
	 * ai <- bj * c[i-j] [1<=i<=k, 0<=j<=i]
	 *
	 */


	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(bl.size()!=2 || hl.size()!=1)
		throw FatalError("translateBCOTNORM: wrong rule type!");

	int i;

	// no infix, so just 2 literals;
	LiteralPtr blitpred1 = bl[0];
	LiteralPtr blitpred2 = bl[1];
	if(blitpred2 < blitpred1)
	{
		std::swap(blitpred1, blitpred2);
	}

	bool isnaf = blitpred1->isNAF(); // is one of them NAF?
	std::string notstr = (isnaf)?std::string("not "):std::string("");

	for(i=1; i<=k; i++)
	{
		int j;
		for(j=0; j<=i; j++)
		{
			Atom bpred1 = *(blitpred1->getAtom());
			Atom bpred2 = *(blitpred2->getAtom());
			Atom hpred = *hl[0];
			// add argument to the predicates

			hpred.addTerm(i);
			bpred2.addTerm(j);
			int l;
			if(isnaf)
				l = k-i+j+1;
			else
				l = i-j;
			bpred1.addTerm(l);

			os << hpred <<" :- ";


			if(j<=0 || j>k)
				os << notstr<< bpred1 <<". "<<std::endl;
			else if(l<=0 || l>k)
				os << bpred2 <<". "<<std::endl;
			else
				os << notstr << bpred1 << ", "<< bpred2<<"." << std::endl;

		}
	}
}

void ASPTranslate::translateBMIN(RulePtr r)
{
	/* Translate
	 * a <- min(b,c)
	 * [ no infix but may contain one NAF ]
	 * into
	 * ai <- bi, ci
	 * or
	 * a <- min(not b, c)
	 * into
	 * ai <- not b_{k-i+1}, ci [1<=i<=k]
	 * if b is NAF
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(bl.size()!=2 || hl.size()!=1)
		throw FatalError("translateBMIN: wrong rule type!");

	int i;

	// no infix, so just 2 literals;
	LiteralPtr blitpred1 = bl[0];
	LiteralPtr blitpred2 = bl[1];
	if(blitpred2 < blitpred1)
	{
		std::swap(blitpred1, blitpred2);
	}

	bool isnaf = blitpred1->isNAF(); // is one of them NAF?
	std::string notstr = (isnaf)?std::string("not "):std::string("");

	for(i=1; i<=k; i++)
	{

		Atom bpred1 = *(blitpred1->getAtom());
		Atom bpred2 = *(blitpred2->getAtom());
		Atom hpred = *hl[0];
		// add argument to the predicates

		hpred.addTerm(i);
		bpred2.addTerm(i);
		int l;
		if(isnaf)
			l = k-i+1;
		else
			l = i;

		bpred1.addTerm(l);

		os << hpred <<" :- ";
		os << notstr << bpred1 << ", "<< bpred2<<"." << std::endl;
	}
}

void ASPTranslate::translateBMAX(RulePtr r)
{
	/* Translate
	 * a <- max(a,b)
	 * [ no infix but may contain one NAF ]
	 * into
	 * ai <- bi
	 * ai <- ci
	 * or
	 * a <- max(not b, c)
	 * into
	 * ai <- not b_{k-i+1}
	 * ai <- ci
	 * if b is NAF
	 * [1<=i<=k]
	 */
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(bl.size()!=2 || hl.size()!=1)
		throw FatalError("translateBMAX: wrong rule type!");

	int i;

	// no infix, so just 2 literals;
	LiteralPtr blitpred1 = bl[0];
	LiteralPtr blitpred2 = bl[1];
	if(blitpred2 < blitpred1)
	{
		std::swap(blitpred1, blitpred2);
	}

	bool isnaf = blitpred1->isNAF(); // is one of them NAF?
	std::string notstr = (isnaf)?std::string("not "):std::string("");

	for(i=1; i<=k; i++)
	{

		Atom bpred1 = *(blitpred1->getAtom());
		Atom bpred2 = *(blitpred2->getAtom());
		Atom hpred = *hl[0];
		// add argument to the predicates

		hpred.addTerm(i);
		bpred2.addTerm(i);
		int l;
		if(isnaf)
			l = k-i+1;
		else
			l = i;
		bpred1.addTerm(l);

		os << hpred <<" :- ";
		os << notstr << bpred1 << "." << std::endl;
		os << hpred <<" :- "<< bpred2<<"." << std::endl;
	}
}

void ASPTranslate::translateHTNORM(RulePtr  r)
{
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(hl.size()!=2 || head.second!= TNORM)
		throw FatalError("translateHTNORM: wrong rule type!");
	int i,j;

	std::sort(bl.begin(), bl.end());

	LiteralPtr blitpred1 = bl[bl.size()-1];
	AtomPtr bptr1 = blitpred1->getAtom();

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-1; i++)	// up to before the last one
		infix.push_back(bl[i]);
	

	Tuple args1;
	args1.push_back(Term(Program::genNextPred(), Term::SYMBOL));
	std::set<std::string> vars;
	for(i=0; i<bl.size(); i++)
	{
		AtomPtr aptr = bl[0]->getAtom();
		std::set<std::string> myvars = aptr->getVariables();
		vars.insert(myvars.begin(), myvars.end());
	}
	std::set<std::string>::iterator vit;
	for(vit=vars.begin(); vit!=vars.end(); ++vit)
	{
		args1.push_back(Term(*vit, Term::VARIABLE));
	}
	
	AtomPtr newb (new Atom(args1));
	
	/*
	 * 	newb(X1...Xn, i) <-  aptr1(...,i), infixs.
	 * 
	 */
	Atom h, hprev;
	for(i=1; i<=k; i++)
	{
		if(i>1)
			hprev = h;
		h = *newb;
		Atom b (*bptr1);
		h.addTerm(i);
		b.addTerm(i);
		os << h <<" :- "<<b<<"."<<std::endl;
		if(i>1)
			os<<hprev<<" :- "<<h<<"."<<std::endl;
	}
	
	/* Create new atoms newp_i_j(VAR1,...,VARn)
	 *  1<=i,j<=k
	 */
	
	Atom newp[k+2][k+2];
	std::string newpstr = Program::genNextPred();
	for(i=1; i<=k; i++)
	{
		for(j=1; j<=k; j++)
		{
			Tuple args2;
			std::string predname (newpstr + "_" + boost::lexical_cast<std::string>(i)
					      +"_"+boost::lexical_cast<std::string>(j));
			args2.push_back(Term(predname, Term::STRING));
			for(vit=vars.begin(); vit!=vars.end(); ++vit)
			{
				args2.push_back(Term(*vit, Term::VARIABLE));
			}
			newp[i][j] = Atom(args2);
		}
	}
	
	/* newp_k,i v newp_k-1,i+1 v .... newp_i_k <- newb_i 
	 * 1 <= i <= k
	 */
	
	for(i=1; i<=k; i++)
	{
		for(j=i; j<=k; j++)
		{
			if(j>i)
				os<<" | ";
			os<<newp[j][k-j+i];
		}
		Atom b (*newb);
		b.addTerm(i);
		os<<" :- "<<b<<"."<<std::endl;
	}
	
	/*
	 * a_i <- newp_i_j.
	 * b_j <- newp_i_j.
	 * 
	 */
	Atom h1,h2;
	h1 = *hl[0];
	h2 = *hl[1];
	
	for(i=1; i<=k; i++)
	{
		for(j=1; j<=k; j++)
		{
			h1.addTerm(i);
			h2.addTerm(j);
			os << h1 << " :- "<<newp[i][j]<<"."<<std::endl;
			os << h2 << " :- "<<newp[i][j]<<"."<<std::endl;
			h1.popTerm();
			h2.popTerm();
		}
	}
	
	
	for(i=1; i<=k; i++)
	{
		for(j=2; j<=k; j++)
		{
			h1.addTerm(j);
			os <<newp[j][i] <<" :- "<<newp[j-1][i]<<", "<<h1<<"."<<std::endl;
			h1.popTerm();
		}
	}
	
	for(i=1; i<=k; i++)
	{
		for(j=2; j<=k; j++)
		{
			h2.addTerm(j);
			os <<newp[i][j] <<" :- "<<newp[i][j-1]<<", "<<h2<<"."<<std::endl;
			h2.popTerm();
		}
	}
	
	/*
	LiteralPtr nafb1 (new Literal(hl[0], true));
	LiteralPtr nafb2 (new Literal(hl[1], true));
	HeadList_t h1,h2;
	h1.push_back(hl[1]);
	h2.push_back(hl[0]);
	HeadExpr_t he1 = std::make_pair(h1, TNORM);
	HeadExpr_t he2 = std::make_pair(h2, TNORM);

	BodyList_t b1,b2;
	b1.insert(b1.begin(), bl.begin(), bl.end());
	b1.push_back(nafb1);
	b2.insert(b2.begin(), bl.begin(), bl.end());
	b2.push_back(nafb2);

	//std::cout<<"bl[0] = "<<*bl[0]<<" b1[0] = "<<*b1[0]<<endl;

	RulePtr r1(new Rule(he1, std::make_pair(b1, CO_TNORM), "", 0));
	RulePtr r2(new Rule(he2, std::make_pair(b2, CO_TNORM), "", 0));

	translateBCOTNORM(r1);
	translateBCOTNORM(r2);
	*/

}

void ASPTranslate::translateHCOTNORM(RulePtr r)
{
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(hl.size()!=2 || head.second!=CO_TNORM)
		throw FatalError("translateHCOTNORM: wrong rule type!");
	int i,j;

	std::sort(bl.begin(), bl.end());

	LiteralPtr blitpred1 = bl[bl.size()-1];
	AtomPtr bptr1 = blitpred1->getAtom();

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-1; i++)	// up to before the last one
		infix.push_back(bl[i]);
	

	Tuple args1;
	args1.push_back(Term(Program::genNextPred(), Term::SYMBOL));
	std::set<std::string> vars;
	for(i=0; i<bl.size(); i++)
	{
		AtomPtr aptr = bl[0]->getAtom();
		std::set<std::string> myvars = aptr->getVariables();
		vars.insert(myvars.begin(), myvars.end());
	}
	std::set<std::string>::iterator vit;
	for(vit=vars.begin(); vit!=vars.end(); ++vit)
	{
		args1.push_back(Term(*vit, Term::VARIABLE));
	}
	
	AtomPtr newb (new Atom(args1));
	
	/*
	 * 	newb(X1...Xn, i) <-  aptr1(...,i), infixs.
	 * 
	 */
	Atom h, hprev;
	for(i=1; i<=k; i++)
	{
		if(i>1)
			hprev = h;
		h = *newb;
		Atom b (*bptr1);
		h.addTerm(i);
		b.addTerm(i);
		os << h <<" :- "<<b<<"."<<std::endl;
		if(i>1)
			os<<hprev<<" :- "<<h<<"."<<std::endl;
	}
	
	/* Create new atoms newp_i_j(VAR1,...,VARn)
	 *  0<=i,j<=k
	 */
	
	Atom newp[k+2][k+2];
	std::string newpstr = Program::genNextPred();
	for(i=0; i<=k; i++)
	{
		for(j=0; j<=k; j++)
		{
			Tuple args2;
			std::string predname (newpstr + "_" + boost::lexical_cast<std::string>(i)
					      +"_"+boost::lexical_cast<std::string>(j));
			args2.push_back(Term(predname, Term::STRING));
			for(vit=vars.begin(); vit!=vars.end(); ++vit)
			{
				args2.push_back(Term(*vit, Term::VARIABLE));
			}
			newp[i][j] = Atom(args2);
		}
	}
	
	/* newp_0,i v newp_1,i-1 v .... newp_i_0 <- newb_i 
	 * 1 <= i <= k
	 */
	
	for(i=1; i<=k; i++)
	{
		for(j=0; j<=i; j++)
		{
			if(j>0)
				os<<" | ";
			os<<newp[j][i-j];
		}
		Atom b (*newb);
		b.addTerm(i);
		os<<" :- "<<b<<"."<<std::endl;
	}
	
	/*
	 * a_i <- newp_i_j.
	 * b_j <- newp_i_j.
	 * 
	 */
	Atom h1,h2;
	h1 = *hl[0];
	h2 = *hl[1];
	
	for(i=0; i<=k; i++)
	{
		for(j=0; j<=k; j++)
		{
			
			if(i>0)
			{
				h1.addTerm(i);
				os << h1 << " :- "<<newp[i][j]<<"."<<std::endl;
				h1.popTerm();
			}
			if(j>0)
			{
				h2.addTerm(j);
				os << h2 << " :- "<<newp[i][j]<<"."<<std::endl;
				h2.popTerm();
			}
		}
	}
	
	
	for(i=0; i<=k; i++)
	{
		for(j=1; j<=k; j++)
		{
			h1.addTerm(j);
			os <<newp[j][i] <<" :- "<<newp[j-1][i]<<", "<<h1<<"."<<std::endl;
			h1.popTerm();
		}
	}
	
	for(i=0; i<=k; i++)
	{
		for(j=1; j<=k; j++)
		{
			h2.addTerm(j);
			os <<newp[i][j] <<" :- "<<newp[i][j-1]<<", "<<h2<<"."<<std::endl;
			h2.popTerm();
		}
	}

	/*
	LiteralPtr nafb1 (new Literal(hl[0], true));
	LiteralPtr nafb2 (new Literal(hl[1], true));

	HeadList_t h1,h2;
	h1.push_back(hl[1]);
	h2.push_back(hl[0]);
	HeadExpr_t he1 = std::make_pair(h1, TNORM);
	HeadExpr_t he2 = std::make_pair(h2, TNORM);

	BodyList_t b1,b2;
	b1.insert(b1.begin(), bl.begin(), bl.end());
	b1.push_back(nafb1);
	b2.insert(b2.begin(), bl.begin(), bl.end());
	b2.push_back(nafb2);

	//std::cout<<"bl[0] = "<<*bl[0]<<" b1[0] = "<<*b1[0]<<endl;

	RulePtr r1(new Rule(he1, std::make_pair(b1, TNORM), "", 0));
	RulePtr r2(new Rule(he2, std::make_pair(b2, TNORM), "", 0));

	translateBTNORM(r1);
	translateBTNORM(r2);
	*/
}

void ASPTranslate::translateHMAX(RulePtr r)
{
	/* Translate
	 * max(a,b) <- c [body may contain infix atoms]
	 *
	 * into
	 *
	 * a_i v b_i <- c_i 1<=i<=k
	 *
	 */

	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(hl.size()!=2 || head.second!=MAX)
		throw FatalError("translateHMAX: wrong rule type!");
	int i;

	// sort the body literals, the last literal must be a real predicate.
	std::sort(bl.begin(), bl.end());

	LiteralPtr blitpred1 = bl[bl.size()-1];

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-1; i++)	// up to before the last one
		infix.push_back(bl[i]);

	std::string newstr = Program::genNextPred();

	// p_k,i v p_k-1,i+1 v ... p_i,k <- c_i 1<=i<=k
	for(i=1; i<=k; i++)
	{
		Atom a1 = *hl[0];
		Atom a2 = *hl[1];
		a1.addTerm(i);
		a2.addTerm(i);
		os << a1 <<" | "<< a2 <<" :- ";

		int l;
		for(l=0; l<infix.size(); l++)
			os<<*infix[l]<<", ";
		Atom bpred1 = *(blitpred1->getAtom());
		bpred1.addTerm(i);
		os << bpred1 << "."<<std::endl;
	}


}

void ASPTranslate::translateHMIN(RulePtr r)
{
	/* Translate
	 * min(a,b) <- c [body may contain infix atoms]
	 *
	 * into
	 *
	 * a_i <- c_i 1<=i<=k
	 * b_i <- c_i
	 *
	 */

	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	if(hl.size()!=2 || head.second!=MIN)
		throw FatalError("translateHMIN: wrong rule type!");
	int i;

	// sort the body literals, the last literal must be a real predicate.
	std::sort(bl.begin(), bl.end());

	LiteralPtr blitpred1 = bl[bl.size()-1];

	// store the infixes
	BodyList_t infix;
	for(i=0; i<bl.size()-1; i++)	// up to before the last one
		infix.push_back(bl[i]);

	std::string newstr = Program::genNextPred();

	// p_k,i v p_k-1,i+1 v ... p_i,k <- c_i 1<=i<=k
	for(i=1; i<=k; i++)
	{
		Atom a1 = *hl[0];
		Atom a2 = *hl[1];
		a1.addTerm(i);
		a2.addTerm(i);
		os << a1 <<" :- ";

		int l;
		for(l=0; l<infix.size(); l++)
			os<<*infix[l]<<", ";
		Atom bpred1 = *(blitpred1->getAtom());
		bpred1.addTerm(i);
		os << bpred1 << "."<<std::endl;

		os << a2 <<" :- ";
		for(l=0; l<infix.size(); l++)
			os<<*infix[l]<<", ";
		os << bpred1 << "."<<std::endl;
	}

}

ASPTranslate::RuleType_t ASPTranslate::detType(RulePtr r)
{
	HeadExpr_t head = r->getHead();
	BodyExpr_t body = r->getBody();

	HeadList_t hl = head.first;
	BodyList_t bl = body.first;
	FuzzyOp_t oph = head.second;
	FuzzyOp_t opb = body.second;


	int i,cbpred=0,chpred = 0; // number of real pred in body/head
	bool chead = false, cbody = false; // constant exists?
	/* since body can contain infix predicate and constants, we need to count the real predicates
	 * and also see whether constants exist
	 */
	for(i=0; i<bl.size(); i++)
	{
		AtomPtr aptr = bl[i]->getAtom();
		if(typeid(*aptr) == typeid(ConstantAtom))
			cbody = true;
		if(typeid(*aptr) != typeid(InfixAtom) &&
				typeid(*aptr) != typeid(ConstantAtom)) // count real predicates
			cbpred++;
	}

	for(i=0; i<hl.size(); i++)
	{
		AtomPtr aptr = hl[i];
		if(typeid(*aptr) == typeid(ConstantAtom))
			chead = true;
		if(typeid(*aptr) != typeid(InfixAtom) &&		// Code defensively
				typeid(*aptr) != typeid(ConstantAtom)) // count real predicates
			chpred++;
	}

	// FACT
	if(chpred == 1 && cbody)
		return FACT;
	//CONSTR
	if(cbpred == 1 && chead)
		return CONSTR;
	//a <- b
	if(chpred==1 && cbpred==1)
	{
		/* Two possibilities:
		 * 1) a <- b
		 * 2) a <- not b
		 *
		 * Find whether body contain NAF or not
		 * 	 */
		for(i=0; i<bl.size(); i++)
			if(bl[i]->isNAF())
				return BNAF;
		return ONEHB;
	}


	// a <- b op c
	if(chpred==1 && cbpred==2)
	{
		switch(opb)
		{
		case TNORM:
			return BTNORM;
		case CO_TNORM:
			return BCOTNORM;
		case MAX:
			return BMAX;
		case MIN:
			return BMIN;
		default:					// code defensively
			return INV;
		}
	}


	if(chpred==2 && cbpred==1)
	{
		switch(oph)
		{
		case TNORM:
			return HTNORM;
		case CO_TNORM:
			return HCOTNORM;
		case MAX:
			return HMAX;
		case MIN:
			return HMIN;
		default:
			return INV;
		}
	}
	return INV;
}


void ASPTranslate::translateRule(RulePtr r)
{
	RuleType_t type = detType(r);
	switch(type)
	{
	case ONEHB:
		translateONEHB(r);
		break;
	case FACT:
		translateFACT(r);
		break;
	case CONSTR:
		translateCONSTR(r);
		break;
	case BTNORM:
		translateBTNORM(r);
		break;
	case BCOTNORM:
		translateBCOTNORM(r);
		break;
	case BMAX:
		translateBMAX(r);
		break;
	case BMIN:
		translateBMIN(r);
		break;
	case HTNORM:
		translateHTNORM(r);
		break;
	case HCOTNORM:
		translateHCOTNORM(r);
		break;
	case HMAX:
		translateHMAX(r);
		break;
	case HMIN:
		translateHMIN(r);
		break;
	case BNAF:
		translateBNAF(r);
		break;
	default:
		// Code defensively against unknown error
		std::ostringstream oserror;
		oserror<<"ASP translate: unknown rule type: "<<std::endl
				<<*r<<std::endl;
		throw FatalError(oserror.str());
	}
}

