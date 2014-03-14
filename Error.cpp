/***************************************************************************
 *   Copyright (C) 2005 Roman Schindlauer 2009 by Mushthofa                *
 *   unintendedchoice@gmail.											*
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

 /* Taken from dlvhex's Error.cpp */

/**
 * @file   Error.cpp
 * @author Roman Schindlauer, Mushthofa
 *
 *
 * @brief  Exception classes.
 *
 *
 */


#include <sstream>
#include "Error.h"


GeneralError::GeneralError(const std::string msg)
        : std::runtime_error(msg)
{
}

SyntaxError::SyntaxError(const std::string msg,
                                        const unsigned l,
        const std::string f)
        : GeneralError(msg),line(l), file(f)
{
}


std::string SyntaxError::getErrorMsg() const
{
        std::ostringstream err;

        err << "Syntax Error";

        if (!file.empty())
                err << " in " << file;

        if (line != 0)
                err << ", line " << line;

        err << ": " << this->what();

        return err.str();
}


void SyntaxError::setLine(unsigned l)
{
        this->line = l;
}


void SyntaxError::setFile(const std::string& f)
{
        this->file = f;
}



FatalError::FatalError(const std::string msg)
        : GeneralError("Fatal error: " + msg)
{

}

//End
