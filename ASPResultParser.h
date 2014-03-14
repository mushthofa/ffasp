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
/**
 * @file ASPResultParser.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Base class for ASP solvers' result parsers
 *
 *
 */

#ifndef _ASPRESULTPARSER_H
#define _ASPRESULTPARSER_H

#include "AtomSet.h"


class ASPResultParser
{
public:
	virtual void parseLine(std::string& line) = 0;
	AtomSet getAnswerSet() const
	{
		return answers;
	}

	virtual ~ASPResultParser()
	{}
protected:
	AtomSet answers;
};

#endif
//End

