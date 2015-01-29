/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa   								*
 *   unintendedchoice@gmail.com  									*
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
 * @file   AtomFactory.cpp
 * @author Roman Schindlauer
 * @date   Sat Feb  4 19:09:02 CET 2006
 * 
 * @brief  Singleton class for storing atoms.
 * 
 * 
 */


#include "AtomFactory.h"


//
// initialize static variable:
//
AtomFactory* AtomFactory::_instance = 0;


AtomFactory* AtomFactory::Instance()
{
	if (_instance == 0)
	{
		_instance = new AtomFactory;
	}

	return _instance;
}


struct NullDeleter
{
	void operator() (Atom*) {} // don't delete managed Atom object
};



AtomPtr AtomFactory::insert(Atom* ap)
{
	AtomPtr a(ap, NullDeleter());

	AtomSet::atomset_t::const_iterator it = atoms.find(a);

	if (it == atoms.end())
	{
		AtomPtr x(ap);
		atoms.insert(x);
		return x;
	}

	delete ap;

	return *it;

}


void AtomFactory::reset()
{
	atoms.clear();
}


AtomFactory::~AtomFactory()
{
}
// end
