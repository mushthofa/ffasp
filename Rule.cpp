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
 * @file Rule.cpp
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief Rule class.
 *
 */


#include "Rule.h"

Rule::Rule(const HeadExpr_t& h, const BodyExpr_t& b,
                 const std::string& f, unsigned l, bool noVars)
        :head(h), body(b), filename(f), lineid(l)
{
        if(!noVars)

                /* Store the rule's variables */
        {
             	BodyList_t::const_iterator b_it;
                for(b_it = body.first.begin(); b_it!=body.first.end(); ++b_it)
                {
                        std::set<std::string> tmpvars;
                        AtomPtr a = (*b_it)->getAtom();

                        if(!(*b_it)->isNAF() && typeid(*a)!=typeid(InfixAtom))
                        	// Also exclude the infix predicates for safety checks
                        {
                                tmpvars = (*b_it)->getVariables();
                                std::set_union(posVars.begin(), posVars.end(),
                                               tmpvars.begin(), tmpvars.end(),
                                               inserter(posVars, posVars.begin()));
                        }
                }
        }
}

Rule::~Rule()
{
}

const HeadExpr_t& Rule::getHead() const
{
        return head;
}

const BodyExpr_t& Rule::getBody() const
{
        return body;
}

const BodyExpr_t Rule::getPositiveBody() const
{
        BodyList_t result;
        BodyList_t::const_iterator it;
        for(it=body.first.begin(); it!=body.first.end(); ++it)
        {
                if(!(*it)->isNAF())
                        result.push_back(*it);
        }
        return std::make_pair(result, body.second);
}

const BodyExpr_t Rule::getNegativeBody() const
{
        BodyList_t result;
        BodyList_t::const_iterator it;
        for(it=body.first.begin(); it!=body.first.end(); ++it)
        {
                if((*it)->isNAF())
                        result.push_back(*it);
        }
        return std::make_pair(result, body.second);
}


std::string Rule::getFile() const
{
        return filename;
}

unsigned Rule::getLine() const
{
        return lineid;
}

void Rule::setHead(const HeadExpr_t& h)
{
        head = h;
}

void Rule::setBody(const BodyExpr_t& b)
{
        body = b;
}

void Rule::addHead(AtomPtr a)
{
        head.first.push_back(a);
}

void Rule::addBody(LiteralPtr l)
{
        body.first.push_back(l);
}

std::set<std::string> Rule::getVariables() const
{
        std::set<std::string> vars;
        HeadList_t::const_iterator h_it;
        for(h_it = head.first.begin(); h_it!=head.first.end(); ++h_it)
        {
                std::set<std::string> tmpvars;
                tmpvars = (*h_it)->getVariables();
                std::set_union(vars.begin(), vars.end(),
                               tmpvars.begin(), tmpvars.end(),
                               inserter(vars, vars.begin()));
        }

        BodyList_t::const_iterator b_it;
        for(b_it = body.first.begin(); b_it!=body.first.end(); ++b_it)
        {
                std::set<std::string> tmpvars;
                tmpvars = (*b_it)->getVariables();
                std::set_union(vars.begin(), vars.end(),
                			tmpvars.begin(), tmpvars.end(),
                			inserter(vars, vars.begin()));
        }
        return vars;
}

std::set<std::string> Rule::getPosVariables() const
{
        return posVars;
}

std::set<std::string> Rule::getNegVariables() const
{
        std::set<std::string> vars;
        HeadList_t::const_iterator h_it;
        for(h_it = head.first.begin(); h_it!=head.first.end(); ++h_it)
        {
                std::set<std::string> tmpvars;
                tmpvars = (*h_it)->getVariables();
                std::set_union(vars.begin(), vars.end(),
                			tmpvars.begin(), tmpvars.end(),
                			inserter(vars, vars.begin()));
        }

        BodyList_t::const_iterator b_it;
        for(b_it = body.first.begin(); b_it!=body.first.end(); ++b_it)
        {
                std::set<std::string> tmpvars;
                AtomPtr a = (*b_it)->getAtom();
                if((*b_it)->isNAF() || (typeid(*a)==typeid(InfixAtom)))
                	// Also take the infix predicates for safety checks
                {
                        tmpvars = (*b_it)->getVariables();
                        std::set_union(vars.begin(), vars.end(),
                        			tmpvars.begin(), tmpvars.end(),
                        			inserter(vars, vars.begin()));
                }
        }
        return vars;
}

unsigned Rule::numberOfVars() const
{
        return posVars.size();
}


bool Rule::isGround() const
{
        HeadList_t::const_iterator h_it;
        for(h_it = head.first.begin(); h_it!=head.first.end(); ++h_it)
        {
                if(!(*h_it)->isGround())
                        return false;
        }
        BodyList_t::const_iterator b_it;
        for(b_it = body.first.begin(); b_it!=body.first.end(); ++b_it)
        {
                if(!(*b_it)->isGround())
                        return false;
        }
        return true;
}

/*
Rule Rule::bindVariables(const std::vector<std::string>& vals)
{


        Substitutions_t sub;
        std::set<std::string>::iterator var_it;
        std::vector<std::string>::const_iterator val_it;

        if(vals.size() != posVars.size())
        {
                std::ostringstream oserr;
                oserr<<*this<<std::endl;
                oserr<<"with values: "<<std::endl;
                for(val_it = vals.begin(); val_it!=vals.end(); ++val_it)
                        oserr<<*val_it<<", ";
                oserr<<std::endl;
                throw GeneralError("Incomplete values for binding: " + oserr.str());
        }

        for(var_it = posVars.begin(), val_it=vals.begin(); var_it!= posVars.end(); ++var_it, ++val_it)
        {
                sub.insert(std::pair<std::string, std::string>(*var_it, *val_it));
        }


        RuleHead_t bindHead;
        RuleHead_t::const_iterator h_it;
        for(h_it = head.begin(); h_it!=head.end(); ++h_it)
        {
                AtomPtr bindAtom(new Atom((*h_it)->bindVariables(sub)));
                bindHead.insert(bindAtom);
        }

        RuleBody_t bindBody;
        RuleBody_t::const_iterator b_it;
        for(b_it = body.begin(); b_it!=body.end(); ++b_it)
        {
                LiteralPtr bindLiteral(new Literal((*b_it)->bindVariables(sub)));
                bindBody.insert(bindLiteral);
        }
        return Rule(bindHead, bindBody, "", 0, true);
}

*/
/*
void Rule::accept(BaseVisitor& v) const
{
        v.visitRule(this);
}
*/

bool Rule::operator== (const Rule& rule2) const
{
        const HeadExpr_t& head2 = rule2.getHead();

        if (head.first.size() != head2.first.size())
                return false;
        if (head.second != head2.second)
        		return false;

        const BodyExpr_t& body2 = rule2.getBody();
        if (body.first.size() != body2.first.size())
                return false;
        if(body.second != body2.second)
        		return false;
        return std::equal(head.first.begin(), head.first.end(), head2.first.begin()) &&
        		std::equal(body.first.begin(), body.first.end(), body2.first.begin());
}

bool Rule::operator!=(const Rule& rule2) const
{
        return !(*this==rule2);
}

bool operator< (const HeadExpr_t& head1, const HeadExpr_t& head2)
{
		if(head1.first.empty() && head2.first.empty()) return false;
        return std::lexicographical_compare(head1.first.begin(), head1.first.end(),
        									head2.first.begin(), head2.first.end());
}

bool operator< (const BodyExpr_t& b1, const BodyExpr_t& b2)
{
        return std::lexicographical_compare(b1.first.begin(), b1.first.end(),
        									b2.first.begin(), b2.first.end());
}

bool Rule::operator< (const Rule& rule2) const
{
        if (this->head < rule2.head)
        {
                return true;
        }
        if (rule2.head < this->head)
        {
                return false;
        }

        if (this->body < rule2.body)
        {
                return true;

        }
        return false;
}

std::ostream& operator<<(std::ostream& os, const FuzzyOp_t& op)
{
	switch(op)
	{
	case TNORM:
		os<<" * ";
		break;
	case CO_TNORM:
		os<<" + ";
		break;
	case MAX:
		os<<" & ";
		break;
	default:
		os<<" ^ ";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Rule& r)
{
        HeadExpr_t h = r.getHead();
        unsigned i = 0;
        HeadList_t::iterator h_it;
        for(h_it = h.first.begin(); h_it!=h.first.end(); ++h_it)
        {
                os<<*(*h_it);
                if(++i<h.first.size())
                	os<<h.second;
        }

        BodyExpr_t b = r.getBody();
        if(b.first.size()>0)
        {
        		i=0;
                os<<" :- ";
                BodyList_t::iterator bit;
                for(bit=b.first.begin(); bit!=b.first.end(); ++bit)
                {
                	os<<*(*bit);
                	if(++i<b.first.size())
                		 os<<b.second;
                }
        }

        if(h.first.size()>0 || b.first.size()>0)
                os<<"."<<std::endl;
        return os;
}

//End
