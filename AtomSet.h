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

* @file   AtomSet.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  AtomSet class
 *
 *
 */


#ifndef _ATOMSET_H
#define _ATOMSET_H

#include <vector>
#include "Atom.h"

class AtomSet
{
        public:
                struct AtomCompare
                {
                        bool operator()(const AtomPtr& a, const AtomPtr& b)
                        {
                                return *a < *b;
                        }
                };

                /* Class const_iterator to simulate STL const iterator in AtomSet */
                typedef std::set<AtomPtr, AtomCompare> atomset_t;

                class const_iterator :
                public std::iterator<atomset_t::const_iterator::iterator_category,
                					Atom, atomset_t::difference_type>
                {
                        atomset_t::const_iterator it;
                        public:
                                const_iterator()
                                { }
                                const_iterator(const atomset_t::const_iterator &it1)
                                : it(it1)
                                { }
                                AtomPtr getPtr() const
                                {
                                        return *it;
                                }
                                const Atom& operator *() const
                                {
                                        return *(*it);
                                }
                                const Atom* operator ->() const
                                {
                                        return &(operator*());
                                }

                                const_iterator& operator ++()
                                {
                                        it++;

                                        return *this;
                                }

                                const_iterator operator ++(int)
                                {
                                        const_iterator tmp = *this;

                                        ++*this;

                                        return tmp;
                                }
                                const_iterator& operator --()
                                {
                                        it--;

                                        return *this;
                                }

                                const_iterator operator --(int)
                                {
                                        const_iterator tmp = *this;

                                        --*this;

                                        return tmp;
                                }

                                bool operator== (const const_iterator& i2) const
                                {
                                        return it == i2.it;
                                }

                                bool operator != (const const_iterator& i2) const
                                {
                                        return (it != i2.it);
                                }
                };

                /* End of class const_iterator */

                /* Ctor */

                AtomSet()
                { }



                const_iterator begin() const;

                const_iterator end() const;

                void clear();

                bool empty() const;

                size_t size() const;

                void insert(AtomPtr&);

                void insert(const AtomSet&);

                void insert(const AtomSet::const_iterator&);

                AtomSet difference(AtomSet&) const;

                void intersectWith(const AtomSet& );

                //void remove (const std::string&);

                //void remove (const std::vector<std::string>&);

                //void keep(const std::vector<std::string>&);

                bool isConsistent() const;

                bool operator==(const AtomSet&) const;

                bool operator!=(const AtomSet&) const;

                int operator<(const AtomSet&) const;



                /* For some functions, atomset needs to be declared as vector */
                std::vector<AtomPtr> asVector() const;


                //std::set<struct PredicateSign> getPredicates() const;

                /* Union of atomsets */
                AtomSet operator+(const AtomSet& a1)
                {
                        AtomSet result;
                        AtomSet::const_iterator a_it;
                        for(a_it = this->begin(); a_it != this->end(); ++a_it)
                        {
                                AtomPtr a_ptr (new Atom(*a_it));
                                result.insert(a_ptr);
                        }

                        for(a_it = a1.begin(); a_it != a1.end(); ++a_it)
                        {
                                AtomPtr a_ptr (new Atom(*a_it));
                                result.insert(a_ptr);
                        }

                        return result;
                }

        private:
                atomset_t atoms;

};

std::ostream& operator<<(std::ostream&, const AtomSet&);

#endif
