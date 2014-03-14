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
	:program(p), k(kk)
	{
		doTranslate(); // translate rules
		addConsRule(); // add rules p_0 <- , p_i <- p_{i+1}
	}

	std::string getProgram() const
	{
		return os.str();
	}


protected:

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
	int k;
};



#endif /* ASPTRANSLATE_H_ */
