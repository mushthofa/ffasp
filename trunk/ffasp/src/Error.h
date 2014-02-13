/***************************************************************************
 *   Copyright (C) 2005 by Roman Schindlauer 2009 Mushthofa                             *
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

/* Taken from dlvhex's Error.h */

/**
 * @file   Error.h
 * @author Roman Schindlauer, Mushthofa
 *
 *
 * @brief  Exception classes.
 *
 *
 */


#ifndef _ERROR_H
#define _ERROR_H

#include <string>
#include <iostream>
#include <stdexcept>


class GeneralError : public std::runtime_error
{
        public:
                GeneralError(const std::string msg);

                virtual std::string getErrorMsg() const
                {
                        return this->what();
                }
};

class SyntaxError: public GeneralError
{
        public:
                SyntaxError(const std::string msg,
                                  const unsigned line=0,
         const std::string file="");
                virtual ~SyntaxError() throw() {}
                virtual std::string getErrorMsg() const;
                void setLine(unsigned);
                void setFile(const std::string&);
        private:
                unsigned line;
                std::string file;
};

class FatalError: public GeneralError
{
        public:
                FatalError(const std::string msg);
};


#endif
//
