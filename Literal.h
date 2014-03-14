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
 * @file   Literal.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  Literal class.
 *
 *
 */

#ifndef _LITERAL_H
#define _LITERAL_H

#include "Atom.h"

#include <set>
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/shared_ptr.hpp>

class Literal
{
        public:
                Literal();
                ~Literal();

                Literal(const Literal&);

                Literal(const AtomPtr&, bool naf=false);
                Literal& operator=(const Literal&);

                const AtomPtr getAtom() const;

                bool isNAF() const;

                //bool isInfix() const;

                bool isGround() const;

                void negate();

                //Literal getPrimed() const;

                //Literal bindVariables(const Substitutions_t& sub);


                bool operator==(const Literal&) const;

                bool operator!=(const Literal&) const;

                bool operator<(const Literal&) const;

                std::set<std::string> getVariables() const;
                friend std::ostream& operator<<(std::ostream&, const Literal&);
                //void accept(BaseVisitor& e) const;


        private:

                const AtomPtr atom;
                bool isWeaklyNegated;

};

typedef boost::shared_ptr<Literal> LiteralPtr;

bool operator<(const LiteralPtr& , const LiteralPtr&);

std::ostream& operator<<(std::ostream&, const Literal&);



#endif
// End
