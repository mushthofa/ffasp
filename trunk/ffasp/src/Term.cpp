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
 * @file   Term.h
 * @author Roman Schindlauer, Mushthofa
 *
 *
 * @brief  Term class definition
 *
 *
 */

#include <cstdlib>
#include "Term.h"
#include "Error.h"

using namespace std;

Term::Term()
        :type(Term::ANON), constantString(namesTable.end()), varString("")
{
}

Term::Term(const Term& term2)
        :type(term2.type)
{
        if(this != &term2)
        {
                if (!term2.isVariable())
                {
                        if( term2.isString() || term2.isSymbol() )
                                constantString = term2.constantString;
                        else
                                constantInt = term2.constantInt;
                }
                else
                        varString = term2.varString;
        }
}

Term::Term(const string& str, TermType_t tt)
        :type(tt)
{

        if(tt==Term::STRING || tt==Term::SYMBOL)
        {
                pair<set<string>::iterator, bool> ret;
                ret = namesTable.insert(str);
                constantString = ret.first;
        }
        else if(tt == Term::VARIABLE)
        {
                varString = str;
        }
        else if(tt==Term::INTEGER)
        {
                constantInt = (unsigned)strtoul(str.c_str(), 0, 10);
                /*constantInt =  */ // convert string representation of the integer to unsigned
        }
}


Term::TermType_t Term::getType() const
{
        return type;
}

bool Term::isInt() const
{
        return type==Term::INTEGER;
}

bool Term::isString() const
{
        return type==Term::STRING;
}

bool Term::isSymbol() const
{
        return type==Term::SYMBOL;
}

bool Term::isVariable() const
{
        return type==Term::VARIABLE;
}

bool Term::isAnon() const
{
        return type==Term::ANON;
}

const string& Term::getName() const
{
        if(type==Term::STRING || type==Term::SYMBOL)
                return *constantString;
        else
                throw GeneralError("getName() is called for non string/symbol term");
}

unsigned Term::getInt() const
{
        if(type==Term::INTEGER)
                return constantInt;
        else
                throw GeneralError("getInt() is called for non integer term");
}

const string& Term::getVariable() const
{
        if(type==Term::VARIABLE)
                return varString;
        else
                throw GeneralError("getVariable() is called for non variable term");
}

bool Term::unifiesWith(const Term& term2) const
{
        if(isVariable()||term2.isVariable())
                return true;
        if(isAnon()||term2.isAnon())
                return true;
        if(type!=term2.type)
                return false;
        if(*this==term2)
                return true;
        return false;
}

Term Term::bindVariables(const Substitutions_t& sub)
{
        if(type == Term::VARIABLE)
        {
                if(sub.find(varString)!=sub.end())
                {
                        // TODO: Does not cover the case for STRING and INTEGER
                        return Term((sub.find(varString))->second, Term::SYMBOL);
                }
                else
                        return *this;
        }
        else
                return *this;
}

Term& Term::operator=(const Term& term2)
{
        type = term2.type;
        constantString = term2.constantString;
        varString = term2.varString;
        constantInt = term2.constantInt;
}

int Term::compare(const Term& term2) const
{
        if(type!=term2.type)
                return (int)type - (int)term2.getType();
        switch(type)
        {
                case INTEGER:
                        return constantInt - term2.getInt();
                case SYMBOL:
                case STRING:
                        return constantString->compare(term2.getName());
                case VARIABLE:
                        return varString.compare(term2.varString);
                case ANON:
                        return 0;
                default:
                        throw GeneralError("Term::compare is called with unknown term type");
                        return 0;
        }
}

bool Term::operator==(const Term& term2) const
{
        return compare(term2)==0;
}

bool Term::operator!=(const Term& term2) const
{
        return compare(term2)!=0;
}

bool Term::operator>(const Term& term2) const
{
        return compare(term2)>0;
}

bool Term::operator<(const Term& term2) const
{
        return compare(term2)<0;
}

bool Term::operator>=(const Term& term2) const
{
        return compare(term2)>=0;
}

bool Term::operator<=(const Term& term2) const
{
        return compare(term2)<=0;
}

ostream& operator<<(ostream& os, const Term& term)
{
        switch(term.getType())
        {
                case Term::INTEGER :
                        os<<term.getInt();
                        break;
                case Term::SYMBOL:
                case Term::STRING:
                        os<<term.getName();
                        break;
                case Term::VARIABLE:
                        os<<term.getVariable();
                        break;
                case Term::ANON:
                        os<<"_";
                        break;
                default:
                        os<<"Error"<<endl;
                        //assert(0);
                        break;
        }
        return os;
}

ostream& operator<< (ostream& out, const Tuple& tuple)
{
        for (unsigned i = 0; i < tuple.size(); i++)
        {
                out << tuple[i];
                if (i < tuple.size() - 1)
                        out << ",";
        }
        return out;
}


std::ostream& operator<<(std::ostream& os, const Substitutions_t& sub)
{
        for(Substitutions_t::const_iterator it = sub.begin(); it!=sub.end(); ++it)
        {
                os<<it->first<<"/"<<it->second<<" ";
        }
        return os;
}

/* Initialize static member */
set<string> Term::namesTable;


