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


#ifndef _TERM_H
#define _TERM_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "Error.h"

/* To represent variable bindings/substitutions */

typedef std::map<std::string, std::string> Substitutions_t;
std::ostream& operator<<(std::ostream&, const Substitutions_t&);


class Term
{

        public:
                typedef enum {INTEGER, SYMBOL, STRING, VARIABLE, ANON } TermType_t;
                static std::set<std::string>    namesTable;
                Term();
                Term(const Term&);
                Term(const std::string&, TermType_t);
                Term(int, TermType_t);
                TermType_t getType() const;

                bool isInt() const;
                bool isSymbol() const;
                bool isString() const;
                bool isVariable() const;
                bool isAnon() const;
                bool isConstant() const
                {
                        return (isInt() || isSymbol() || isString());
                }

                const std::string& getName() const;
                unsigned getInt() const;

                const std::string& getVariable() const;

                bool unifiesWith(const Term&) const;

                Term bindVariables(const Substitutions_t&);

                Term& operator=(const Term&);
                int compare(const Term&) const;
                bool operator==(const Term&) const;
                bool operator<(const Term&) const;
                bool operator>(const Term&) const;
                bool operator<=(const Term&) const;
                bool operator>=(const Term&) const;
                bool operator!=(const Term&) const;
        private:
                TermType_t type;
                std::set<std::string>::const_iterator constantString;
                unsigned constantInt;
                std::string varString;

};

std::ostream& operator<<(std::ostream&, const Term&);

typedef std::vector<Term> Tuple;

std::ostream& operator<<(std::ostream&, const Tuple&);



#endif
// End
