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
 * @file DLVResult_grammar.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Grammar spesification for DLV's output expressed in Boost Spirit syntax
 *
 *
 */

#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/tree/ast.hpp>

#ifndef _DLVRESULT_GRAMMAR_H
#define _DLVRESULT_GRAMMAR_H

using namespace BOOST_SPIRIT_CLASSIC_NS;

struct DLVresult_grammar : public grammar<DLVresult_grammar>
{

        static const int constantID = 1;
        static const int anonID = 2;
        static const int variableID = 3;
        static const int termID = 4;
        static const int predicateID = 5;
        static const int infix_predID = 6;
        static const int atomID = 7;
        static const int answerID = 8;
        static const int answersetID = 9;
        static const int symbolID = 17;
        static const int stringconstID = 18;
        static const int integerID = 19;


        template <typename ScannerT>
                        struct definition
        {
                definition(DLVresult_grammar const& )
                {
                        //Starting the definition of the grammar

                        symbol = leaf_node_d[lower_p >> *(alnum_p|ch_p('_'))];
                        // symbol --> [a-z].([A-Z]|[a-z]|[0-9]|_)*
                        stringconst = leaf_node_d[ch_p('"')>>*(alnum_p|ch_p('_')|space_p)>>ch_p('"')];
                        // stringconst --> ".([a-z]|[A-Z]|[0-9]|_)"
                        integer = leaf_node_d[+digit_p];
                        // integer --> [0-9]*
                        constant = symbol|stringconst|integer;
                        // constant --> [0-9]+ | [a-z].{[a-z A-Z]|[0-9]|'_'}*
                        term = constant ;
                        // term --> constant | variable | anon
                        predicate = leaf_node_d[lower_p >> *(alnum_p|ch_p('_'))];
                        // predicate --> [a-z].{[a-zA-Z]|[0-9]|'_'}*
                        atom = root_node_d[predicate] >>
                                        inner_node_d
                                        [
                                        ch_p('(') >> infix_node_d
                                        [
                                        term  >> *(ch_p(',') >> term)
                                        ] >> ch_p(')')
                                        ]
                                        | predicate;
                        // atom --> predicate | predicate . '('. term.(term.',')* ')'
                        answer = atom | root_node_d[ch_p('-')]>>atom;
                        answerset = inner_node_d
                                        [
                                        ch_p('{')>>!
                                        (
                                         infix_node_d
                                        [
                                        answer>>*(ch_p(',')>>answer)
                                        ]
                                        )
                                        >>ch_p('}')
                                        ];

                }
                rule<ScannerT, parser_context<>, parser_tag<constantID> > constant;
                rule<ScannerT, parser_context<>, parser_tag<symbolID> > symbol;
                rule<ScannerT, parser_context<>, parser_tag<stringconstID> > stringconst;
                rule<ScannerT, parser_context<>, parser_tag<integerID> > integer;
                rule<ScannerT, parser_context<>, parser_tag<termID> > term;
                rule<ScannerT, parser_context<>, parser_tag<predicateID> > predicate;
                rule<ScannerT, parser_context<>, parser_tag<atomID> > atom;
                rule<ScannerT, parser_context<>, parser_tag<answerID> > answer;
                rule<ScannerT, parser_context<>, parser_tag<answersetID> > answerset;
                rule<ScannerT, parser_context<>, parser_tag<answersetID> > const&
                                start() const { return answerset; }
        };

};

#endif
//End
