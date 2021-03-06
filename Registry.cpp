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
 * 	@brief The Registry class is a sort of mediator that inserts objects into factory classes.
 * 	@author Roman Schindlauer, Mushthofa		
 */



#include "Registry.h"


Registry* Registry::_instance = 0;


Registry* Registry::Instance()
{
	if (_instance == 0)
	{
		_instance = new Registry;
	}

	return _instance;
}


AtomPtr Registry::storeAtom(Atom* a)
{
	return AtomFactory::Instance()->insert(a);
}

