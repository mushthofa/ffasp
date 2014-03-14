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

 * @file SpiritProgramParser.cpp
 * @author Mushthofa
 * @date 02-2014
 *
 * @brief Implementation class for program parser using Boost Spirit
 *
 *
 */


#include "SpiritProgramParser.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>


SpiritProgramParser::SpiritProgramParser()
        :ProgramParser()
{
        unsigned line_id = 1;
        curVarID = 0;
        std::string line_str;

        // read line from standard input until a newline

        logic_grammar lg;
        while(std::getline(std::cin, line_str, '\n'))
        {
                boost::trim(line_str);
                line_str = ignore_comments(line_str);
                boost::trim(line_str);
                if(line_str.size()==0)
                        continue;

                tree_parse_info<> parse_tree = ast_parse(line_str.c_str(), lg, space_p);

                if(parse_tree.full)
                {
					bool safe = true;
					tree_it tree_begin = parse_tree.trees.begin();
					boost::spirit::classic::parser_id node_id = tree_begin->value.id();

					if(node_id == logic_grammar::literalID || node_id == logic_grammar::predicateID)
					{
						AtomPtr fact (new Atom (parseAtom(tree_begin)));
						SafetyChecker* sc = new SafetyChecker(*fact);
						if(!sc->checkSafe())
								safe = false;
						else
						{
							AtomPtr ca (new ConstantAtom(1,1));
							LiteralPtr l(new Literal(ca, false));
							HeadList_t h;
							h.push_back(fact);
							BodyList_t b;
							b.push_back(l);

							RulePtr rule (new Rule(std::make_pair(h,TNORM),
											std::make_pair(b, TNORM),
											filename, line_id));
							rules.addRule(rule, true);
						}
						delete sc;

					}

					else if(node_id == logic_grammar::ifopID)
					{

						int numc = tree_begin->children.size();
						if(numc==2)
						{
							tree_it child_it = tree_begin->children.begin();
							HeadExpr_t head;
							head = parseHead(child_it);
							++ child_it;

							BodyExpr_t body;
							body = parseBody(child_it);

							RulePtr prule(new Rule(head, body,
												filename, line_id));
							SafetyChecker* sc = new SafetyChecker(*prule);
							if(!sc->checkSafe())
							{
									safe = false;
							}
							delete sc;
							rules.addRule(prule, true);
						}
						else if(numc==1)
						{
							tree_it child_it = tree_begin->children.begin();
							HeadList_t head;
							AtomPtr ca (new ConstantAtom(0));
							head.push_back(ca);

							BodyExpr_t body;
							body = parseBody(child_it);

							RulePtr prule(new Rule(std::make_pair(head, TNORM), body,
												filename, line_id));
							SafetyChecker* sc = new SafetyChecker(*prule);
							if(!sc->checkSafe())
							{
									safe = false;
							}
							delete sc;
							rules.addRule(prule, true);
						}
						else
						{
							throw SyntaxError("<Rule with 3 children>: ", line_id, filename);
						}
					}

					else if(node_id == logic_grammar::tnormID || node_id == logic_grammar::cotnormID ||
							node_id == logic_grammar::maxID || node_id == logic_grammar::minID)
					{
						AtomPtr ca (new ConstantAtom(1,1));
						LiteralPtr l(new Literal(ca, false));
						BodyList_t b;
						b.push_back(l);
						HeadExpr_t head = parseHead(tree_begin);

						RulePtr rule (new Rule(head, std::make_pair(b, TNORM), filename, line_id));
						rules.addRule(rule, true);
					}
					else
					{
							throw SyntaxError("Unknown node_id: ", line_id, filename);
					}


					if(!safe)
							throw SyntaxError("Rule/fact is not safe", line_id, filename);
					/*
					std::map<parser_id, std::string> rule_names;
					rule_names[logic_grammar::constantID] = "constant";
					rule_names[logic_grammar::anonID] = "anonymous";
					rule_names[logic_grammar::variableID] = "variable";
					rule_names[logic_grammar::termID] = "term";
					rule_names[logic_grammar::infix_predID] = "infix predicate";
					rule_names[logic_grammar::predicateID] = "predicate";
					rule_names[logic_grammar::atomID] = "atom";
					rule_names[logic_grammar::literalID] = "literal";
					rule_names[logic_grammar::body_literalID] = "body literals";
					rule_names[logic_grammar::headID] = "head";
					rule_names[logic_grammar::bodyID] = "body";
					rule_names[logic_grammar::constraintID] = "constraint";
					rule_names[logic_grammar::factID] = "fact";
					rule_names[logic_grammar::ruleID] = "rule";
					rule_names[logic_grammar::disjunctID] = "disjunction";
					rule_names[logic_grammar::symbolID] = "symbol";
					rule_names[logic_grammar::stringconstID] = "stringconst";
					rule_names[logic_grammar::integerID] = "integer";
					rule_names[logic_grammar::lineID] = "line";
					tree_to_xml(std::cout, parse_tree.trees, line_str.c_str(), rule_names);
					*/
			}
			else
			{
					std::ostringstream oserr;
					oserr<<"\n>Here ==> "<<parse_tree.stop<<std::endl;
					throw SyntaxError(oserr.str(), line_id, filename);
			}
            line_id++;
	}
}

Term SpiritProgramParser::parseTerm(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();
        std::string termstr (node->value.begin(), node->value.end());
        boost::trim(termstr);
        if(node_id==logic_grammar::symbolID)
        {
                return Term(termstr, Term::SYMBOL);
        }
        if(node_id==logic_grammar::stringconstID)
        {
                return Term(termstr, Term::STRING);
        }
        if(node_id==logic_grammar::integerID)
        {
                return Term(termstr, Term::INTEGER);
        }
        if(node_id==logic_grammar::variableID)
        {
                /* Standardize apart */
                std::ostringstream varName;
                std::map<std::string, unsigned>::iterator it = varID.find(termstr);
                if(it == varID.end())
                {
                        //std::cout<<"creating a new variable ";
                        varID[termstr] = curVarID++;
                }

                varName << "VAR_" << varID[termstr] <<"";

                return Term(varName.str(), Term::VARIABLE);
        }

        if(node_id==logic_grammar::anonID)
        {
        	std::cout<<"anon"<<endl;
            return Term();
        }
        throw SyntaxError("parseTerm(): no return value;");
        return Term();

}

Atom SpiritProgramParser::parseAtom(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();
        bool strongneg = false;
        tree_it args_node, args_it;
        if(node_id==logic_grammar::literalID)
        {
                strongneg = true;
                args_node = node->children.begin();
        }
        else
                args_node = node;
        std::string predname (args_node->value.begin(), args_node->value.end());
        boost::trim(predname);
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

InfixAtom SpiritProgramParser::parseInfixAtom(const tree_it& node)
{
        //boost::spirit::classic::parser_id node_id = node->value.id();
        std::string opname (node->value.begin(), node->value.end());
        boost::trim(opname);

        tree_it child_it = node->children.begin();
        Term t1 = parseTerm(child_it);
        ++ child_it;
        Term t2 = parseTerm(child_it);
        return InfixAtom(opname, t1, t2);
}

ConstantAtom SpiritProgramParser::parseConstantAtom(const tree_it& node)
{
		//tree_it child_it = node->children.begin();
        boost::spirit::classic::parser_id node_id = node->value.id();

        if(node_id == logic_grammar::fractionID)
        {


        	tree_it child_it = node->children.begin();
        	++ child_it;
        	std::string stri (child_it->value.begin(), child_it->value.end());

        	int a = boost::lexical_cast<int> (stri);
        	++ child_it;
        	++ child_it;
        	stri = std::string(child_it->value.begin(), child_it->value.end());

        	int b = boost::lexical_cast<int> (stri);


        	return ConstantAtom(a,b);
        }
        else
        {
        	tree_it child_it = node->children.begin();
        	++child_it;
        	std::string strreal (child_it->value.begin(), child_it->value.end());

        	double r = boost::lexical_cast<double> (strreal);
        	return ConstantAtom(r);
        }

        throw SyntaxError("parseConstantAtom(): no return value;");
        return ConstantAtom(1);
        /*
        std::string opname (node->value.begin(), node->value.end());
        boost::trim(opname);

        tree_it child_it = node->children.begin();
        Term t1 = parseTerm(child_it);
        ++ child_it;
        Term t2 = parseTerm(child_it);
        return InfixAtom(opname, t1, t2);
        */
}

HeadExpr_t SpiritProgramParser::parseHead(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();
        if(node_id == logic_grammar::predicateID
                  || node_id == logic_grammar::literalID)
        {
                HeadList_t head;
                AtomPtr head_atom (new Atom (parseAtom(node)));
                head.push_back(head_atom);
                return std::make_pair(head, TNORM);
        }
        else if(node_id == logic_grammar::fractionID || node_id == logic_grammar::rationalID)
		{
				HeadList_t head;
				AtomPtr atom (new ConstantAtom(parseConstantAtom(node)));
				head.push_back(atom);
				return std::make_pair(head, TNORM) ;
		}
        else if(node_id == logic_grammar::tnormID)
        {
        	tree_it child_it;
			HeadList_t head;
			for(child_it = node->children.begin(); child_it!=node->children.end(); ++child_it)
			{
				HeadExpr_t temphead = parseHead(child_it);
				HeadList_t temphl = temphead.first;
				FuzzyOp_t op = temphead.second;
				if(temphl.size()>=2 && op!=TNORM)
					throw SyntaxError("Only one type of operator is allowed in the head of the same rule!");
				head.insert(head.begin(), temphead.first.begin(), temphead.first.end());
			}
            return std::make_pair(head, TNORM);

        }
		else if(node_id == logic_grammar::maxID)
		{
			tree_it child_it;
			HeadList_t head;
			for(child_it = node->children.begin(); child_it!=node->children.end(); ++child_it)
			{
				HeadExpr_t temphead = parseHead(child_it);
				HeadList_t temphl = temphead.first;
				FuzzyOp_t op = temphead.second;
				if(temphl.size()>=2 && op!=MAX)
					throw SyntaxError("Only one type of operator is allowed in the head of the same rule!");
				head.insert(head.begin(), temphead.first.begin(), temphead.first.end());
			}
			return std::make_pair(head, MAX);

		}
		else if(node_id == logic_grammar::minID)
		{
				tree_it child_it;
				HeadList_t head;
				for(child_it = node->children.begin(); child_it!=node->children.end(); ++child_it)
				{
					HeadExpr_t temphead = parseHead(child_it);
					HeadList_t temphl = temphead.first;
					FuzzyOp_t op = temphead.second;
					if(temphl.size()>=2 && op!=MIN)
						throw SyntaxError("Only one type of operator is allowed in the head of the same rule!");
					head.insert(head.begin(), temphead.first.begin(), temphead.first.end());
				}
				return std::make_pair(head, MIN);

		}
		else if(node_id == logic_grammar::cotnormID)
		{
			tree_it child_it;
			HeadList_t head;
			for(child_it = node->children.begin(); child_it!=node->children.end(); ++child_it)
			{
				HeadExpr_t temphead = parseHead(child_it);
				HeadList_t temphl = temphead.first;
				FuzzyOp_t op = temphead.second;
				if(temphl.size()>=2 && op!=CO_TNORM)
					throw SyntaxError("Only one type of operator is allowed in the head of the same rule!");
				head.insert(head.begin(), temphead.first.begin(), temphead.first.end());
			}
			return std::make_pair(head, CO_TNORM);

		}
        throw SyntaxError("parseHead(): no return value;");
        HeadList_t h;
        return std::make_pair(h, MIN);
}

BodyExpr_t SpiritProgramParser::parseBody(const tree_it& node)
{
        boost::spirit::classic::parser_id node_id = node->value.id();

        if(node_id == logic_grammar::predicateID
               || node_id == logic_grammar::literalID)
        {
                BodyList_t body;
                AtomPtr atom (new Atom(parseAtom(node)));
                LiteralPtr literal (new Literal(atom));
                body.push_back(literal);
                return std::make_pair(body, TNORM);
        }
        else if(node_id == logic_grammar::infix_predID)
        {
        		BodyList_t body;
        		AtomPtr atom(new InfixAtom(parseInfixAtom(node)));
        		LiteralPtr literal (new Literal(atom));
				body.push_back(literal);
				return std::make_pair(body, TNORM) ;
        }
        else if(node_id == logic_grammar::fractionID || node_id == logic_grammar::rationalID)
        {
                BodyList_t body;
                AtomPtr atom (new ConstantAtom(parseConstantAtom(node)));
                LiteralPtr literal (new Literal(atom));
                body.push_back(literal);
                return std::make_pair(body, TNORM) ;
        }
        else if(node_id == logic_grammar::literalID)
		{
			   BodyList_t body;
			   AtomPtr atom (new Atom(parseAtom(node)));
			   LiteralPtr literal (new Literal(atom, false));
			   body.push_back(literal);
			   return std::make_pair(body, TNORM);
		}
        else if(node_id == logic_grammar::body_literalID)
        {
                BodyList_t body;
                tree_it child_it = node->children.begin();
                AtomPtr atom (new Atom(parseAtom(child_it)));
                LiteralPtr literal (new Literal(atom, true));
                body.push_back(literal);
                return std::make_pair(body, TNORM);
        }
        else if(node_id == logic_grammar::tnormID)
        {

                BodyList_t body;
                tree_it child_it;

                for(child_it=node->children.begin();
                	child_it!=node->children.end(); ++child_it)
                {

                        BodyExpr_t tempbody = parseBody(child_it);
                        BodyList_t tempbl = tempbody.first;
                        FuzzyOp_t op = tempbody.second;
                        if(tempbl.size()>=2 && op!=TNORM)
                        	throw SyntaxError("Only one type of operator is allowed in the body of the same rule");
                        body.insert(body.begin(), tempbody.first.begin(), tempbody.first.end());

                }

                return std::make_pair(body, TNORM);
        }

        else if(node_id == logic_grammar::cotnormID)
		{

				BodyList_t body;
				tree_it child_it;

				for(child_it=node->children.begin();
					child_it!=node->children.end(); ++child_it)
				{

						BodyExpr_t tempbody = parseBody(child_it);
						BodyList_t bc = tempbody.first;
						FuzzyOp_t op = tempbody.second;
						if(bc.size()>=2 && op!=CO_TNORM)
							throw SyntaxError("Only one type of operator is allowed in the body of the same rule");
						int idx=0;
						for(idx=0; idx<bc.size(); ++idx)
						{
							AtomPtr at = bc[idx]->getAtom();
							if(typeid(*at)==typeid(InfixAtom))
								throw SyntaxError("parseBody(): infix predicates can only be used with t-norm!");
						}

						body.insert(body.begin(), tempbody.first.begin(), tempbody.first.end());

				}

				return std::make_pair(body, CO_TNORM);
		}
        else if(node_id == logic_grammar::maxID)
		{

				BodyList_t body;
				tree_it child_it;

				for(child_it=node->children.begin();
					child_it!=node->children.end(); ++child_it)
				{

						BodyExpr_t tempbody = parseBody(child_it);
						BodyList_t bc = tempbody.first;
						FuzzyOp_t op = tempbody.second;
						if(bc.size()>=2 && op!=MAX)
							throw SyntaxError("Only one type of operator is allowed in the body of the same rule");
						int idx=0;
						for(idx=0; idx<bc.size(); ++idx)
						{
							AtomPtr at = bc[idx]->getAtom();
							if(typeid(*at)==typeid(InfixAtom))
								throw SyntaxError("parseBody(): infix predicates can only be used with t-norm!");
						}

						body.insert(body.begin(), tempbody.first.begin(), tempbody.first.end());

				}

				return std::make_pair(body, MAX);
		}
        else if(node_id == logic_grammar::minID)
		{

				BodyList_t body;
				tree_it child_it;

				for(child_it=node->children.begin();
					child_it!=node->children.end(); ++child_it)
				{

						BodyExpr_t tempbody = parseBody(child_it);
						BodyList_t bc = tempbody.first;
						FuzzyOp_t op = tempbody.second;
						if(bc.size()>=2 && op!=MIN)
							throw SyntaxError("Only one type of operator is allowed in the body of the same rule");
						int idx=0;
						for(idx=0; idx<bc.size(); ++idx)
						{
							AtomPtr at = bc[idx]->getAtom();
							if(typeid(*at)==typeid(InfixAtom))
								throw SyntaxError("parseBody(): infix predicates can only be used with t-norm!");
						}

						body.insert(body.begin(), tempbody.first.begin(), tempbody.first.end());

				}

				return std::make_pair(body, MIN);
		}

        BodyList_t b;
        throw SyntaxError("parseBody(): no return value");
        return std::make_pair(b,TNORM);
}

/*
AtomSet SpiritProgramParser::getEDB()
{
        return ProgramParser::getEDB();
}
*/
Program SpiritProgramParser::getRules()
{
        return ProgramParser::getRules();
}


std::string ignore_comments(const std::string& input)
{
        std::string::size_type index1, index2, length;
        std::string temp;
        index1 = input.find('%', 0);
        if(index1==std::string::npos)
                return input;
        else
        {
                index2 = input.find('\n',index1);
                if(index2==std::string::npos)
                        return input.substr(0, index1);
                else
                {
                        length = index2 - index1;
                        temp = input;
                        temp.erase(index1, length);
                        return ignore_comments(temp);
                }
        }
}

// End

