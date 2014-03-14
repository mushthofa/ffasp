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
/*

 * AtomSet.cpp
 *
 *  Created on: Feb 2014
 *      Author: mush
 */

/**
 * @file   AtomSet.cpp
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  AtomSet class
 *
 *
 */

#include "AtomSet.h"
#include <algorithm>


AtomSet::const_iterator
                AtomSet::begin() const
{
        return const_iterator(atoms.begin());
}


AtomSet::const_iterator
                AtomSet::end() const
{
        return const_iterator(atoms.end());
}


void AtomSet::clear()
{
        atoms.clear();
}


bool AtomSet::empty() const
{
        return atoms.empty();
}


size_t AtomSet::size() const
{
        return atoms.size();
}



void AtomSet::insert(AtomPtr& ap)
{
        atoms.insert(ap);
}



void AtomSet::insert(const AtomSet& add)
{
        atoms.insert(add.atoms.begin(), add.atoms.end());
}

void AtomSet::insert(const AtomSet::const_iterator& it)
{
        atoms.insert(it.getPtr());
}


AtomSet AtomSet::difference(AtomSet& as) const
{
        AtomSet res;
        for (atomset_t::const_iterator a = atoms.begin();
                    a != atoms.end();
                    a++)
        {
                if (as.atoms.find(*a) == as.atoms.end())
                        res.atoms.insert(*a);
        }
        return res;
}

void AtomSet::intersectWith(const AtomSet& as)
{
        atomset_t result;
        std::insert_iterator<atomset_t> insert_it (result, result.begin());
        std::set_intersection(as.atoms.begin(), as.atoms.end(),
                                          atoms.begin(),atoms.end(), insert_it);
        atoms = result;
}

struct atomMatches : public std::binary_function<AtomPtr, Atom, bool>
{
        bool operator()(const AtomPtr g, const Atom& a) const
        {
                return (*g == a);
        }
};

bool AtomSet::isConsistent() const
{
        atomset_t::iterator cur = atoms.begin();
        atomset_t::const_iterator last = atoms.end();

        while (cur != last)
        {
                Atom a(**cur);
                a.negate();

                if (std::find_if(++cur, last, bind2nd(atomMatches(), a)) != last)
                        return false;
        }
        return true;
}

int AtomSet::operator< (const AtomSet& atomset2) const
{
        if (this->size() < atomset2.size())
                return true;

        if (this->size() > atomset2.size())
                return false;

        std::pair<AtomSet::const_iterator, AtomSet::const_iterator> result;
        result = std::mismatch(this->begin(), this->end(), atomset2.begin());

        if (result.first == this->end())
                return false;
        return *(result.first) < *(result.second);
}

/*
struct predicateMatches : public std::binary_function<AtomPtr, std::string, bool>
{
        bool operator()(const AtomPtr g, const std::string& pred) const
        {
                return (g->getPredicate() == Term(pred, Term::SYMBOL));
        }
};
*/

/*
void AtomSet::remove(const std::string& pred)
{
        atomset_t::iterator cur = atoms.begin();

        atomset_t::const_iterator last = atoms.end();

        while ((cur = std::find_if(cur, last, bind2nd(predicateMatches(), pred))) != last)
        {
                atomset_t::iterator tmp = cur++;

                atoms.erase(tmp);
        }
}


void AtomSet::remove(const std::vector<std::string>& preds)
{
        for (std::vector<std::string>::const_iterator predit = preds.begin();
                    predit != preds.end();
                    ++predit)
        {
                remove(*predit);
        }
}

void AtomSet::keep(const std::vector<std::string>& preds)
{
        atomset_t::iterator cur = atoms.begin();
        atomset_t::const_iterator last = atoms.end();

        while (cur != last)
        {

                if ((std::find_if(preds.begin(), preds.end(),
                        bind1st(predicateMatches(), *cur))) == preds.end())
                {
                        atomset_t::iterator tmp = cur++;

                        atoms.erase(tmp);
                }
                else
                {
                        cur++;
                }
        }
}

*/
std::vector<AtomPtr> AtomSet::asVector() const
{
        std::vector<AtomPtr> result;
        atomset_t::iterator it;
        for(it = atoms.begin(); it!=atoms.end(); ++it)
                result.push_back(*it);
        return result;
}

/*

std::set<struct PredicateSign> AtomSet::getPredicates() const
{
        std::set<struct PredicateSign> preds;
        atomset_t::const_iterator a_it;
        for (a_it = atoms.begin(); a_it!=atoms.end(); ++a_it)
        {
                struct PredicateSign pred;
                pred.name = (*a_it)->getPredicateName();
                pred.arity = (*a_it)->getArity();
                preds.insert(pred);
        }
        return preds;
}
*/

std::ostream& operator<<(std::ostream& os, const AtomSet& as)
{
        unsigned i = 1;
        os<<"{";
        for(AtomSet::const_iterator as_it = as.begin(); as_it!=as.end(); ++as_it)
        {
                os<<*as_it;
                if(i++<as.size())
                        os<<", ";

        }
        os<<"}";
        return os;
}



