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

#include "ExprNode.h"

LitNode::LitNode(const LiteralPtr& l)
:lit(l)
{
	type= ExprNode::LIT;
}


const LiteralPtr LitNode::getLit() const
{
	return lit;
}

std::string LitNode::getOp() const
{
	return std::string("");
}

OpNode::OpNode(const std::string& s)
:op(s)
{
	type = ExprNode::OP;
}


const LiteralPtr OpNode::getLit() const
{
	LiteralPtr r (new Literal());
	return r;
}

std::string OpNode::getOp() const
{
	return op;
}

std::ostream& operator<<(std::ostream& os, const ExprNode& node)
{
	if(node.getType()==ExprNode::LIT)
		os<<*(node.getLit());
	else
		os<<node.getOp();
	return os;
}


//End
