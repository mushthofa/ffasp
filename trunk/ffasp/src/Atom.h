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
 * @file   Atom.h
 * @author Roman Schindlauer, Mushthofa
 *
 *
 * @brief  Atom class definition
 *
 *
 */


#ifndef _ATOM_H
#define _ATOM_H

#include <string>
#include <iostream>
#include <set>
#include <boost/shared_ptr.hpp>
#include "Term.h"


class Atom;

typedef boost::shared_ptr<Atom> AtomPtr;

class Atom
{
        public:
                Atom();

                ~Atom();

                Atom(const Atom&);

                Atom(const std::string&, const Tuple&, bool=false);

                Atom(const Tuple&, bool=false);

                virtual const   Term& getPredicate() const;

                virtual Tuple getArguments() const
                {
                        assert(!arguments.empty());
                        Tuple ret(arguments.begin(), arguments.end());
                        ret.erase(ret.begin());
                        return ret;
                }

                std::string getPredicateName() const;

                virtual void setArguments(const Tuple&);

                const Term& getArgument(unsigned ) const;



                std::set<std::string> getVariables() const;

                Atom bindVariables(const Substitutions_t& sub);

                virtual unsigned getArity() const;

                virtual bool unifiesWith(const AtomPtr&) const;

                virtual bool operator==(const Atom&) const;

                virtual bool operator!=(const Atom&) const;

                virtual bool operator>(const Atom&) const;

                virtual bool operator<(const Atom&) const;

                virtual bool operator>=(const Atom&) const;

                virtual bool operator<=(const Atom&) const;

                virtual bool equals(const AtomPtr& a) const
                {
                        return *this == *a;
                }

                bool isGround() const;

                bool isStronglyNegated() const;

                void negate()
                {
                        isStrongNegated = !isStrongNegated;
                }

                Atom getPrimed() const;

               // virtual void accept(BaseVisitor& ) const;

                /* Table for storing all constant arguments */
                static std::set<Term> constantsTable;

        protected:
                Tuple arguments;
                bool isStrongNegated;


};

bool operator<(const AtomPtr&, const AtomPtr& );
/*
class InfixAtom: public Atom
{
        public:
                InfixAtom (const std::string&, Term&, Term& );
                //const Term& getArgument
                void accept(BaseVisitor& e) const;
};

class boolAtom : public Atom
{
        public:
                boolAtom() : Atom(Tuple(1, Term()))
                { }

                virtual const Term& getPredicate() const
                {
                        return arguments.front();
                }

                virtual bool unifiesWith(const AtomPtr&) const
                {
                        return false;
                }

                virtual bool operator== (const Atom&) const
                {
                        return false;
                }

                bool operator< (const Atom&) const
                {
                        return true;
                }
};
*/

std::ostream& operator<<(std::ostream&, const Atom&);

struct PredicateSign
{
        std::string name;
        unsigned arity;
        /*
        void accept(BaseVisitor& v) const
        {
                v.visitPredicateSign(this);
        }
        */

        bool operator< (struct PredicateSign ps) const
        {
                if(this->arity < ps.arity)
                        return true;
                if(this->arity > ps.arity)
                        return false;
                if(this->name.compare(ps.name) < 0)
                        return true;
                return false;
        }
};

#endif
// End
