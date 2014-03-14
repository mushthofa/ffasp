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
 * @file DLVResultParser.cpp
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief DLV's result parser implemented using Boost Spirit parser framework
 *
 *
 */


#include "DLVResultParser.h"
#include <boost/algorithm/string/trim.hpp>


DLVResultParser::DLVResultParser()
{
}

void DLVResultParser::parseLine(std::string& line)
{
        boost::trim(line);
        answers.clear();
        if(line.size()>0)
        {
                DLVresult_grammar dg;
                tree_parse_info<> parse_tree = ast_parse(line.c_str(), dg, space_p);
                if(parse_tree.full)
                {
                        tree_it tree_begin = parse_tree.trees.begin();
                        boost::spirit::classic::parser_id node_id = tree_begin->value.id();
                        if(node_id == DLVresult_grammar::answerID
                                                || node_id == DLVresult_grammar::atomID
                                                || node_id == DLVresult_grammar::predicateID)
                        {
                                AtomPtr answer (new Atom(parseAtom(tree_begin)));
                                answers.insert(answer);
                        }
                        else if(tree_begin->children.size()>0)
                        {
                                tree_it atoms_it;
                                for(atoms_it=tree_begin->children.begin();
                                                                atoms_it!=tree_begin->children.end();
                                                                ++atoms_it)
                                {
                                        AtomPtr answer (new Atom(parseAtom(atoms_it)));
                                        answers.insert(answer);
                                }
                        }

                        /*
                        std::map<parser_id, std::string> rule_names;
                        rule_names[DLVresult_grammar::constantID] = "constant";
                        rule_names[DLVresult_grammar::stringconstID] = "stringconst";
                        rule_names[DLVresult_grammar::integerID] = "integer";
                        rule_names[DLVresult_grammar::termID] = "term";
                        rule_names[DLVresult_grammar::predicateID] = "predicate";
                        rule_names[DLVresult_grammar::atomID] = "atom";
                        rule_names[DLVresult_grammar::answerID] = "answer";
                        rule_names[DLVresult_grammar::answersetID] = "answerset";
                        tree_to_xml(std::cout, parse_tree.trees, line.c_str(), rule_names);
                        */
                }
                else
                {
                        // Error in parsing DLV's output...

                        throw FatalError("Failed parsing results from DLV: " + line);
                }
        }
}

Term DLVResultParser::parseTerm(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();
        std::string termstr (node->value.begin(), node->value.end());
        boost::trim(termstr);
        if(node_id==DLVresult_grammar::symbolID)
        {
                return Term(termstr, Term::SYMBOL);
        }
        if(node_id==DLVresult_grammar::stringconstID)
        {
                return Term(termstr, Term::STRING);
        }
        if(node_id==DLVresult_grammar::integerID)
        {
                return Term(termstr, Term::INTEGER);
        }
        throw FatalError("Error parsing result from DLV: parseTerm() unknown node_id!");
        /* Not reachable */
}

Atom DLVResultParser::parseAtom(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();
        bool strongneg = false;
        tree_it args_node, args_it;
        if(node_id==DLVresult_grammar::answerID)
        {
                strongneg = true;
                args_node = node->children.begin();
        }
        else
                args_node = node;
        std::string predname (args_node->value.begin(), args_node->value.end());
        boost::trim(predname);

        /* TODO: ugly hack for encoding classic negation */
        /*
        if(predname.substr(0, 6) == "m_NEG_")
        {
                predname = predname.substr(6);
                strongneg = true;
        }
		*/


        Tuple args;

        /* Predicate name must be a symbol */
        args.push_back(Term(predname, Term::SYMBOL));

        /* Go through all argument nodes */

        for(args_it = args_node->children.begin();
                   args_it!=args_node->children.end();
                   ++args_it)
        {
                args.push_back(parseTerm(args_it));
        }

        return Atom(args, strongneg);
}
