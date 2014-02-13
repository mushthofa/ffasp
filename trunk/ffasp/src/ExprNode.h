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

/**
 * @file   ExprNode.h
 * @author Mushthofa
 *
 * @brief  A class to encapsulate one expression node in the rule
 *
 *
 */

#include <string>
#include "Literal.h"

#ifndef EXPRNODE_H_
#define EXPRNODE_H_



class ExprNode
{
	public:
		typedef enum {OP, LIT} Node_t;
		Node_t getType() const
		{
			return type;
		}

		virtual std::string getOp() const
		{
			return std::string("");
		}

		virtual const LiteralPtr  getLit() const
		{
			LiteralPtr r (new Literal());
			return r;
		}
	protected:
			Node_t type;
};

class LitNode : public ExprNode
{
	public:
		LitNode(){}
		LitNode(const LiteralPtr& );
		const LiteralPtr getLit() const;
		std::string getOp() const;
	private:
		LiteralPtr lit;

};

class OpNode : public ExprNode
{
	public:
		OpNode(const std::string& );
		const LiteralPtr getLit() const;
		std::string getOp() const;
	private:
		std::string op;

};


std::ostream& operator<<(std::ostream& os, const ExprNode& n);


#endif /* EXPRNODE_H_ */
//End


