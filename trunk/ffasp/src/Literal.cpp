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
 * @file   Literal.cpp
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  Literal class.
 *
 *
 */


#include "Literal.h"


Literal::Literal()
{ }

Literal::~Literal()
{ }

Literal::Literal(const Literal& l2)
        :atom(l2.getAtom()), isWeaklyNegated(l2.isNAF())
{

}

Literal& Literal::operator=(const Literal& lit2)
{
        this->isWeaklyNegated = lit2.isWeaklyNegated;
        const_cast<AtomPtr&>(this->atom) = lit2.atom;
        return *this;
}

Literal::Literal(const AtomPtr& at, bool naf)
        : atom(at),
                  isWeaklyNegated(naf)
{
}


const AtomPtr Literal::getAtom() const
{
        return atom;
}


bool Literal::isNAF() const
{
        return isWeaklyNegated;
}


bool Literal::isGround() const
{
        return atom->isGround();
}

void Literal::negate()
{
        isWeaklyNegated = !isWeaklyNegated;
}


std::set<std::string> Literal::getVariables() const
{
        return atom->getVariables();
}


bool Literal::operator== (const Literal& lit2) const
{
        if (!(*atom == *(lit2.getAtom())))
                return 0;

        if (isWeaklyNegated != lit2.isNAF())
                return 0;

        return 1;
}

bool Literal::operator!= (const Literal& lit2) const
{
        return !(*this == lit2);
}


bool Literal::operator< (const Literal& lit2) const
{
        if (!this->isNAF() && lit2.isNAF())
                return true;
        if (this->isNAF() && !lit2.isNAF())
                return false;
        return (*(this->getAtom()) < *(lit2.getAtom()));
}

bool operator<(const LiteralPtr& l1, const LiteralPtr& l2)
{
        return *l1<*l2;
}

std::ostream& operator<<(std::ostream& os, const Literal& lit)
{
        if(lit.isNAF())
                os<<"not ";
        os<<(*lit.getAtom());
        return os;
}


//End
