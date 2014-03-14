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
 * @file DLVResultParser.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief DLV's result parser implemented using Boost Spirit parser framework
 *
 *
 */

#ifndef _DLVRESULT_PARSER_H
#define _DLVRESULT_PARSER_H



#include "ASPResultParser.h"
#include "DLVResult_grammar.h"
#include "AtomSet.h"

using namespace boost::spirit::classic;

typedef char const* char_t;
typedef tree_match<char_t> parse_tree_match_t;
typedef parse_tree_match_t::tree_iterator tree_it;


class DLVResultParser : public ASPResultParser
{
        public:
                DLVResultParser();
                virtual void parseLine(std::string& line);

        private:
                Term parseTerm(const tree_it&);
                Atom parseAtom(const tree_it&);

};

#endif

//End
