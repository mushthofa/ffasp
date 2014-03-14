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


 * @file Program.cpp
 * @author Mushthofa
 *
 * @brief Program class.
 *
 */

#include "Program.h"
#include <sstream>

unsigned long int Program::nextId = 1;



std::string Program::genNextPred()
{
	std::ostringstream ss;
	ss << NEW_PRED <<nextId++;
	return ss.str();
}

Program::Program()
{
}

RulePtr Program::operator[](unsigned int idx) const
{
        rulemap_t::const_iterator it = rule_map.find(idx);
        if(it==rule_map.end())
        {
                std::ostringstream oserr;
                oserr<<"Rule index "<<idx<<" is not found."<<std::endl;
                throw GeneralError(oserr.str());
        }
        else
                return it->second;
}

void Program::addRule(RulePtr r, bool withPredicate)
{
        rule_map.insert(std::pair<unsigned, RulePtr>(rules.size(), r));
        rules.insert(r);
        /* Update the predicate set */

        if(!withPredicate)
                return;
        HeadExpr_t currentHead = r->getHead();
        BodyExpr_t currentBody = r->getBody();

        HeadList_t::iterator h_it;
        for(h_it = currentHead.first.begin(); h_it!=currentHead.first.end(); ++h_it)
        {
                AtomPtr currAtom = *h_it;
                if(typeid(*currAtom) != typeid(ConstantAtom)
                		&& typeid(*currAtom) != typeid(InfixAtom))
                {
                        std::string name = currAtom->getPredicateName();
                        int arity = currAtom->getArity();
                        if(predsign.find(name)!=predsign.end() &&
                        		predsign[name]!=arity)
                        {
                        	std::ostringstream os;
                        	os <<"Predicate " << name <<" previously seen with arity "<<
                        			predsign[name] << ", now with arity" << arity;
							throw SyntaxError(os.str());
                        }
                        else
                        	predsign[name] = arity;
                }
        }

        BodyList_t::iterator b_it;
        for(b_it = currentBody.first.begin(); b_it!=currentBody.first.end(); ++b_it)
        {
                LiteralPtr currLiteral = *b_it;
                AtomPtr currAtom = currLiteral->getAtom();
                if(typeid(*currAtom) != typeid(ConstantAtom)
                		&& typeid(*currAtom) != typeid(InfixAtom))
                {
                	std::string name = currAtom->getPredicateName();
					int arity = currAtom->getArity();
					if(predsign.find(name)!=predsign.end() &&
							predsign[name]!=arity)
					{
						std::ostringstream os;
						os <<"Predicate " << name <<" previously seen with arity "<<
								predsign[name] << ", now with arity " << arity;
						throw SyntaxError(os.str());
					}
					else
						predsign[name] = arity;
                }
        }
}

void Program::deleteRule(iterator i)
{
        rules.erase(i.it);
        rule_map.clear();
        ruleset_t::iterator it;
        int idx=0;
        for(it=rules.begin(); it!=rules.end(); ++it)
        	rule_map.insert(std::pair<unsigned, RulePtr>(idx++, *it));

}


void Program::clear()
{
        rule_map.clear();
        rules.clear();
}

bool Program::isHorn() const
{
        /* Program is normal positive, no negative body literals appear on a body of a rule
        and no disjunction appear in the head */

        Program::iterator it;
        for(it=this->begin(); it!=this->end(); ++it)
        {
                RulePtr currentRule = (*it);
                HeadExpr_t currentHead = currentRule->getHead();
                if(currentHead.first.size() > 1)
                        return false;
                BodyExpr_t currentBody = currentRule->getNegativeBody();
                if(currentBody.first.size() > 0)
                        return false;
        }
        return true;
}


MapSign_t Program::getPredicates() const
{
	return predsign;
}

std::ostream& operator<< (std::ostream& os, const Program& p)
{
        for (Program::const_iterator it=p.begin(); it!=p.end(); ++it)
        {
                os<<(*(*it));//<<std::endl;
        }
        return os;
}

/*bool operator< (struct PredicateSign a, struct PredicateSign b)
{
        if(a.arity < b.arity)
                return true;
        if(a.arity > b.arity)
                return false;
        if(a.name < b.name)
                return true;
        if(a.name > b.name)
                return false;
        return false;
}
*/
//End
