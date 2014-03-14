/***************************************************************************
 *   Copyright (C) 2009 by *
 *   Mushthofa.Mushthofa@UGent.*
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
 * @file logic_grammar.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Grammar spesification for logic program in Boost::Spirit format
 *
 *
 */


#ifndef _LOGIC_GRAMMAR_H
#define _LOGIC_GRAMMAR_H

using namespace BOOST_SPIRIT_CLASSIC_NS;

struct logic_grammar : public grammar<logic_grammar>
{

        static const int constantID = 1;
        static const int anonID= 2;
        static const int variableID = 3;
        static const int termID = 4;
        static const int predicateID = 5;
        static const int infix_predID = 6;
        static const int atomID = 7;
        static const int literalID = 8;
        static const int body_literalID = 9;
        static const int headID = 10;
        static const int bodyID = 11;
        static const int constraintID = 12;
        static const int factID = 13;
        static const int ruleID = 14;
        static const int lineID = 15;
        static const int disjunctID = 16;
        static const int symbolID = 17;
        static const int stringconstID = 18;
        static const int integerID = 19;
        static const int fuzzyconstantID = 20;
        static const int fractionID = 21;
        static const int tnormID = 22;
        static const int cotnormID = 23;
        static const int maxID = 24;
        static const int minID = 25;
        static const int bodytnormID = 26;
        static const int bodycotnormID = 27;
        static const int bodymaxID = 28;
        static const int bodyminID = 29;
        static const int headtnormID = 30;
        static const int headcotnormID = 31;
        static const int headmaxID = 32;
        static const int headminID = 33;
        static const int fuzzyopID = 34;
        static const int rationalID = 35;
        static const int ifopID = 36;



        template <typename ScannerT>
                        struct definition
        {
                definition(logic_grammar const& )
                {
                        //Starting the definition of the grammar

                        symbol = leaf_node_d[lower_p >> *(alnum_p|ch_p('_'))];
                        // symbol --> [a-z].([A-Z]|[a-z]|[0-9]|_)*
                        stringconst = leaf_node_d[ch_p('"')>>*(alnum_p|ch_p('_')|space_p)>>ch_p('"')];
                        // string const --> ".([a-z]|[A-Z]|[0-9]|_)"
                        integer = leaf_node_d[+digit_p];
                        // integer --> [0-9]*
                        constant = symbol|stringconst|integer;
                        // constant --> [0-9]+ | [a-z].{[a-z A-Z]|[0-9]|'_'}*
                        anon = leaf_node_d[ch_p('_')];
                        // anon --> '_'
                        variable =  leaf_node_d[upper_p >> *(alnum_p|ch_p('_'))];
                        // variable --> [A-Z].{[a-zA-Z]|[0-9]|'_'}*
                        term = constant | variable | anon;
                        // term --> constant | variable | anon
                        predicate = leaf_node_d[lower_p >> *(alnum_p|ch_p('_'))];
                        // predicate --> [a-z].{[a-zA-Z]|[0-9]|'_'}*
                        infix_pred = str_p(">=") | str_p("<=")|
                                        ch_p('<') | ch_p('>') |
                                        ch_p('=') | str_p("!=");

                        // infix_pred = '<'|'>'|'>='|'<='|'='|'!='
                        atom = root_node_d[predicate] >>
                                        inner_node_d
                                        [
                                        ch_p('(') >> infix_node_d
                                        [
                                                term  >> *(ch_p(',') >> term)
                                        ] >> ch_p(')')
                                        ]
                                        | term>>root_node_d[infix_pred]>>term
                                        | predicate;

                        // atom --> predicate | predicate . '('. term.(term.',')* ')'
                        fraction = ch_p('#')>>leaf_node_d[int_p]>>ch_p('/')>>leaf_node_d[int_p];
                        rational = ch_p('#')>>leaf_node_d[(ch_p('0')|ch_p('1'))>>!(ch_p('.')>>+digit_p)];
                        fuzzyconstant = fraction | rational;
                        /* Actually not a good term for this ... literal should be used for body */
                        literal = (root_node_d[ch_p('-')]>>atom) |
                                        atom | root_node_d[fuzzyconstant] ;
                        // literal --> - atom | atom


                        body_literal = (root_node_d[str_p("not")]>>literal) |
                                        literal;
                        // body_literal --> not literal | literal

                        tnorm = ch_p(',') | ch_p('*');
                        cotnorm = ch_p('+') | ch_p('|');
                        maxOp = ch_p('&');
                        minOp = ch_p('^');

                        fuzzyOp = tnorm | cotnorm | maxOp | minOp;
                        ifOp = str_p(":-");


                        //body = bodycotnorm | bodytnorm | bodymax | bodymin;
                        body = body_literal >> *(root_node_d[fuzzyOp]>>body_literal);
                        head = literal >> *(root_node_d[fuzzyOp]>>literal);



                        constraint = root_node_d[ifOp] >> body;
                        // constraint = ':-'.body
                        fact = literal;
                        // fact --> literal
                        prule = (head >> root_node_d[ifOp]>> body);
                        line = (discard_last_node_d[prule>>ch_p('.')])
                        		| (discard_last_node_d[fact>>ch_p('.')])
                        		| (discard_last_node_d[head>>ch_p('.')])
                        		| (discard_last_node_d[constraint>>ch_p('.')]);
                        // line --> fact | constraint | rule | head
                }
                rule<ScannerT, parser_context<>, parser_tag<constantID> > constant;
                rule<ScannerT, parser_context<>, parser_tag<anonID> > anon;
                rule<ScannerT, parser_context<>, parser_tag<variableID> > variable;
                rule<ScannerT, parser_context<>, parser_tag<termID> > term;
                rule<ScannerT, parser_context<>, parser_tag<infix_predID> > infix_pred;
                rule<ScannerT, parser_context<>, parser_tag<predicateID> > predicate;
                rule<ScannerT, parser_context<>, parser_tag<atomID> > atom;
                rule<ScannerT, parser_context<>, parser_tag<fuzzyconstantID> > fuzzyconstant;
                rule<ScannerT, parser_context<>, parser_tag<fractionID> > fraction;
                rule<ScannerT, parser_context<>, parser_tag<rationalID> > rational;
                rule<ScannerT, parser_context<>, parser_tag<literalID> > literal;
                rule<ScannerT, parser_context<>, parser_tag<body_literalID> > body_literal;
                rule<ScannerT, parser_context<>, parser_tag<tnormID> > tnorm;
                rule<ScannerT, parser_context<>, parser_tag<cotnormID> > cotnorm;
                rule<ScannerT, parser_context<>, parser_tag<maxID> > maxOp;
                rule<ScannerT, parser_context<>, parser_tag<minID> > minOp;
                rule<ScannerT, parser_context<>, parser_tag<fuzzyopID> > fuzzyOp;
                rule<ScannerT, parser_context<>, parser_tag<ifopID> > ifOp;
                rule<ScannerT, parser_context<>, parser_tag<bodytnormID> > bodytnorm;
                rule<ScannerT, parser_context<>, parser_tag<bodycotnormID> > bodycotnorm;
                rule<ScannerT, parser_context<>, parser_tag<bodymaxID> > bodymax;
                rule<ScannerT, parser_context<>, parser_tag<bodyminID> > bodymin;
                rule<ScannerT, parser_context<>, parser_tag<headtnormID> > headtnorm ;
                rule<ScannerT, parser_context<>, parser_tag<headcotnormID> > headcotnorm;
                rule<ScannerT, parser_context<>, parser_tag<headmaxID> > headmax;
                rule<ScannerT, parser_context<>, parser_tag<headminID> > headmin;
                rule<ScannerT, parser_context<>, parser_tag<headID> > head;
                rule<ScannerT, parser_context<>, parser_tag<bodyID> > body;
                rule<ScannerT, parser_context<>, parser_tag<constraintID> > constraint;
                rule<ScannerT, parser_context<>, parser_tag<factID> > fact;
                rule<ScannerT, parser_context<>, parser_tag<ruleID> > prule;
                rule<ScannerT, parser_context<>, parser_tag<disjunctID> > disjunct;
                rule<ScannerT, parser_context<>, parser_tag<symbolID> > symbol;
                rule<ScannerT, parser_context<>, parser_tag<stringconstID> > stringconst;
                rule<ScannerT, parser_context<>, parser_tag<integerID> > integer;
                rule<ScannerT, parser_context<>, parser_tag<lineID> > line;
                rule<ScannerT, parser_context<>, parser_tag<lineID> > const&
                                start() const { return line; }
        };

};

#endif
//End
