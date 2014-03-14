/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                       *
 *   Mushthofa.Mushthofa@												   *
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
 * @file Program.h
 * @author Mushthofa, Roman Schindlauer,
 *
 * @brief Program class.
 *
 */

#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <set>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
#include "Rule.h"

typedef boost::shared_ptr<Rule> RulePtr;
typedef std::map<std::string, int> MapSign_t;

#define NEW_PRED "p_NEW_"

class Program
{
        public:

                typedef std::set<RulePtr, boost::indirect_fun<std::less<Rule> > > ruleset_t;
                typedef std::map<unsigned, RulePtr> rulemap_t;

                class const_iterator;

                class iterator
                {
                        friend class const_iterator;
                        friend class Program;

                        ruleset_t::iterator it;
                        public:
                                iterator() {}

                                iterator(const  ruleset_t::iterator &it1)
                                : it(it1)
                                { }

                                RulePtr operator *() const
                                {
                                        return (*it);
                                }

                                iterator operator ++() //prefix
                                {
                                        it++;
                                        return (*this);
                                }

                                iterator operator ++(int) //postfix
								{
									   iterator temp(it);
									   it++;
									   return temp;
								}

                                bool operator== (const iterator& i2) const
                                {
                                        return it == i2.it;
                                }

                                bool operator != (const iterator& i2) const
                                {
                                        return (it != i2.it);
                                }
                };

                class const_iterator
                {
                        ruleset_t::const_iterator it;

                        public:

                                const_iterator()
                                { }

                                const_iterator(const iterator &it1)
                                : it(it1.it)
                                { }

                                const RulePtr operator *() const
                                {
                                        return (*it);
                                }

                                void operator ++()
                                {
                                        it++;
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

                iterator begin() const
                {
                        return iterator(rules.begin());
                }

                iterator end() const
                {
                        return iterator(rules.end());
                }

                RulePtr operator[](unsigned int idx) const;

                Program();

                void addRule(RulePtr, bool withPredicate = false);
                void deleteRule(iterator);
                void deleteRule(unsigned int idx);

                MapSign_t getPredicates() const;

                /* Diagnosis utilities for a program */

                /* Is this program empty? */
                bool empty() const
                {
                        return rules.empty();
                }

                /* How many (non-ground) rules do we have? */
                unsigned size() const
                {
                        return rules.size();
                }

                /*  Is it a Horn program? */
                bool isHorn() const;


                /* Clears all the rules */
                void clear();



                /* Union */
                Program operator+(const Program& p1)
                {
                        Program result;
                        Program::const_iterator p_it;
                        for(p_it = p1.begin(); p_it != p1.end(); ++p_it)
                        {
                                result.addRule(*p_it, false);
                        }

                        for(p_it = this->begin(); p_it != this->end(); ++p_it)
                        {
                                result.addRule(*p_it, false);
                        }

                        return result;
                }

                /* Get the definite part of the program */
                /*
                Program getDefinite() const
                {
                        Program result;
                        Program::const_iterator p_it;
                        for(p_it = this->begin(); p_it!=this->end(); ++p_it )
                        {
                                if((*p_it)->isDefinite())
                                        result.addRule(*p_it, false);
                        }
                        return result;
                }
				*/

                static std::string genNextPred();

        private:
                static unsigned long int nextId ;

                ruleset_t rules;
                rulemap_t rule_map;
                //std::set<struct PredicateSign> preds;
                MapSign_t predsign;
};



std::ostream& operator<<(std::ostream& os, const Program&);

#endif
//End
