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

 * @file SpiritProgramParser.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Implementation class for program parser using Boost Spirit
 *
 *
 */


#ifndef _SPIRITPROGRAMPARSER_H
#define _SPIRITPROGRAMPARSER_H


#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/tree/ast.hpp>

#include "logic_grammar.h"
#include "ProgramParser.h"
#include "SafetyChecker.h"


using namespace boost::spirit::classic;

typedef char const* char_t;
typedef tree_match<char_t> parse_tree_match_t;
typedef parse_tree_match_t::tree_iterator tree_it;


class SpiritProgramParser: public ProgramParser
{
        public:
                SpiritProgramParser();
                ~SpiritProgramParser(){}
                Program getRules();
                //AtomSet getEDB();

        protected:
                Term parseTerm(tree_it const&);
                Atom parseAtom(tree_it const&);
                ConstantAtom parseConstantAtom(const tree_it&);
                InfixAtom parseInfixAtom(tree_it const&);
                Literal parseLiteral(tree_it const&);
                BodyExpr_t parseBody(tree_it const&);
                HeadExpr_t parseHead(tree_it const&);
                //HardConstraint parseHardConstraint(tree_it const&);
                Rule parseRule(tree_it const&);
                std::map<std::string, unsigned> varID;
                unsigned curVarID;

};

/* Ignoring comments on the string read from the input */

std::string ignore_comments(const std::string&);

#endif
//End
