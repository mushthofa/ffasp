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
 * @file   Atom.cpp
 * @author Roman Schindlauer, Mushthofa
 *
 *
 * @brief  Atom class definition
 *
 *
 */

#include "Atom.h"

/* Initialize static data member */

std::set<Term> Atom::constantsTable;

Atom::Atom()
{
}

Atom::~Atom()
{
}

Atom::Atom(const Atom& atom2)
        :arguments(atom2.arguments),
                         isStrongNegated(atom2.isStrongNegated)
{

}

Atom::Atom(const std::string& predname, const Tuple& args, bool neg)
        :isStrongNegated(neg)
{
        arguments.push_back(Term(predname, Term::SYMBOL));
        Tuple::const_iterator args_it;
        for(args_it=args.begin(); args_it!=args.end(); ++args_it)
        {
                arguments.push_back(*args_it);

                /* Store constants in the table */
                if(args_it->isConstant())
                        constantsTable.insert(*args_it);
        }
}

Atom::Atom(const Tuple& args, bool neg)
        :isStrongNegated(neg)
{
        assert(args.size()>0);
        Tuple::const_iterator args_it;
        bool is_arg = false;
        for(args_it=args.begin(); args_it!=args.end(); ++args_it)
        {
                if(!is_arg) /* First time is always true, then always false */
                {
                        is_arg = true;
                }
                else
                {
                        /* Store constants in the table */
                        if(args_it->isConstant())
                                constantsTable.insert(*args_it);
                }
                arguments.push_back(*args_it);
        }
}

void Atom::setArguments(const Tuple& args)
{
        arguments.resize(1);
        arguments.insert(arguments.end(),
                                  args.begin(), args.end());
}

const Term& Atom::getArgument(unsigned idx) const
{
        return arguments[idx];
}

std::string Atom::getPredicateName() const
{
        Term predTerm = getArgument(0);
        return predTerm.getName();
}


unsigned Atom::getArity() const
{
        return arguments.size()-1;
}

const Term& Atom::getPredicate() const
{
        return getArgument(0);
}

bool Atom::isStronglyNegated() const
{
        return isStrongNegated;
}

bool Atom::unifiesWith(const AtomPtr& atom2) const
{
        if(typeid(*atom2)!=typeid(Atom))
                return false;
        if(getArity()!=atom2->getArity())
                return false;
        for(unsigned i=0; i<=getArity(); i++)
        {
                if(!getArgument(i).unifiesWith(atom2->getArgument(i)))
                        return false;
        }
        return true;
}

Atom Atom::bindVariables(const Substitutions_t& sub)
{
        Tuple args;
        for(Tuple::iterator it=arguments.begin(); it!=arguments.end(); ++it)
        {
                args.push_back(Term(it->bindVariables(sub)));
        }
        return Atom(args, isStrongNegated);
}

Atom Atom::getPrimed() const
{
        std::string predname = getPredicateName();
        predname += "_m_PRIME";
        return Atom(predname, getArguments(), isStrongNegated);
}

/*
void Atom::accept(BaseVisitor& v) const
{
        v.visitAtom(this);
}
*/

bool Atom::operator==(const Atom& atom2) const
{
        if(typeid(atom2)!=typeid(*this))
                return false;
        if(getArity()!=atom2.getArity())
                return false;
        if(isStrongNegated!=atom2.isStronglyNegated())
                return false;
        return equal(this->arguments.begin(), this->arguments.end(),
                           atom2.arguments.begin());
}

bool Atom::operator!=(const Atom& atom2) const
{
        return !(*this==atom2);
}

bool Atom::operator<(const Atom& atom2) const
{
        /* If both is infix atom, we do lexicographical compare */
       // if(typeid(*this) == typeid(InfixAtom) && typeid(atom2) == typeid(InfixAtom))
                return lexicographical_compare(++arguments.begin(), arguments.end(),
                                                                   ++atom2.arguments.begin(), atom2.arguments.end());
        /* InfixAtom is bigger */
        /*if(typeid(*this) == typeid(InfixAtom) && typeid(atom2) == typeid(Atom))
                return false;
        if(typeid(*this) == typeid(Atom) && typeid(atom2) == typeid(InfixAtom))
                return true;
        */

        int n = getPredicate().compare(atom2.getPredicate());
        if(n<0)
                return true;
        if(n>0)
                return false;

        if (!isStrongNegated && atom2.isStrongNegated)
                return true;
        else if (isStrongNegated && !atom2.isStrongNegated)
                return false;

        if (getArity() < atom2.getArity())
        {
                return true;
        }
        if (getArity() == atom2.getArity())
        {
                return std::lexicographical_compare(++arguments.begin(), arguments.end(),
                                                                   ++atom2.arguments.begin(), atom2.arguments.end());
        }
        // getArity() > atom2.getArity()
        return false;
}

bool Atom::operator>(const Atom& atom2) const
{
        return (!(*this==atom2) && !(*this<atom2));
}

bool Atom::operator<=(const Atom& atom2) const
{
        return !(*this>atom2);
}

bool Atom::operator>=(const Atom& atom2) const
{
        return !(*this<atom2);
}

bool Atom::isGround() const
{
        for(Tuple::const_iterator it=arguments.begin(); it!=arguments.end(); ++it)
        {
                if(it->isVariable())
                        return false;
        }
        return true;
}
std::set<std::string> Atom::getVariables() const
{
        std::set<std::string> vars;
        for(Tuple::const_iterator args_it = arguments.begin();
                   args_it!=arguments.end();
                   ++args_it)
        {
                if(args_it->isVariable())
                        vars.insert(args_it->getVariable());
        }
        return vars;
}

std::ostream& operator<<(std::ostream& os, const Atom& atom)
{
        if(false)//typeid(atom)==typeid(InfixAtom)) /* Bad use of typeid */
        {
                os<<atom.getArgument(1);
                os<<atom.getArgument(0);
                os<<atom.getArgument(2);
        }
        else
        {
                unsigned i=1;
                //cout<<"in ostream operator<<"<<endl;
                if(atom.isStronglyNegated())
                        os<<"-";
                os<<atom.getPredicate();
                Tuple args = atom.getArguments();
                if(args.size()>0)
                {
                        os<<"(";
                        for(Tuple::const_iterator it=args.begin(); it!=args.end(); ++it)
                        {
                                //cout<<"type "<<it->getType()<<endl;
                                os<<*it;
                                if(i++<atom.getArguments().size())
                                        os<<", ";
                        }
                        os<<")";
                }
        }
        return os;
}

bool operator<(const AtomPtr& a, const AtomPtr& b)
{
        return *a<*b;
}

/*
InfixAtom::InfixAtom( const std::string& op, Term& t1, Term& t2)
{
        arguments.push_back(Term(op, Term::SYMBOL));
        arguments.push_back(t1);
        arguments.push_back(t2);
        if(t1.isConstant())
                constantsTable.insert(t1);
        if(t2.isConstant())
                constantsTable.insert(t2);
}

void InfixAtom::accept(BaseVisitor& v) const
{
        v.visitInfixAtom(this);
}

std::ostream& operator<<(std::ostream& os, const InfixAtom& atom)
{
        os<<atom.getArgument(1);
        os<<atom.getArgument(0);
        os<<atom.getArgument(2);
        return os;
}
*/
//End
