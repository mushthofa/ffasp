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

* Rewrite.h
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

#ifndef REWRITE_H_
#define REWRITE_H_

#include "Program.h"

class Rewrite
{
public:


	Rewrite(const Program& p)
	:rules(p), done(false)
	{ }

	Program getStandard ()
	{
		if(!done)
			doRewrite();
		return rules;
	}

	void doRewrite();



protected:
	Program rules;
	bool done;

	/* Each of these method check for a spesific condition of rules
	 * Perform the appropriate rewriting by:
	 * 1) adding the new/replacing rules
	 *  and keeping also the predicate signature in the program
	 *  because they need to be converted also to graded truth value in the translation
	 * 2) return true when they rewrite the rule
	 *   the rule will be removed in the calling method (doRewrite())
	 * 3) if no rewriting necessary, return false;
	 */
	bool checkRuleConstant(Program::iterator);
	bool checkRuleBodyOp(Program::iterator);
	bool checkRule2BodyNeg(Program::iterator);
	bool checkRuleHeadOp(Program::iterator);
	bool checkHeadCompBodyNeg(Program::iterator);
	bool checkHeadBodyComp(Program::iterator);

};



#endif /* REWRITE_H_ */
