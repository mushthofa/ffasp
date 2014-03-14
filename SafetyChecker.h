/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa                                                            *
 *   unintendedchoice@gmail.com                                                                         *
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
 * @file SafetyChecker.h
 * @author Mushthofa
 * @date Tue 24 03 2009
 *
 * @brief Safety checker class
 *
 *
 */


#ifndef _SAFETYCHECKER_H
#define _SAFETYCHECKER_H

#include "Program.h"

class SafetyChecker
{
        public:
                SafetyChecker(const Atom&);
                SafetyChecker(const Rule&);
                bool checkSafe() const;
        protected:
                enum {FACT, RULE} type;
                Atom atom;
                Rule rule;
};

#endif
//End

