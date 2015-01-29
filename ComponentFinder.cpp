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


#include "ComponentFinder.h"

void ComponentFinder::dumpAssignment(const ComponentList& cl, std::ostream& out) const
{
	for (unsigned ci = 0; ci < cl.size(); ++ci)
	{
		out << ci << ": ";

		for (Vertices::const_iterator vi = cl[ci].begin();
				   vi != cl[ci].end();
				   ++vi)
		{
			if (vi != cl[ci].begin())
				out << ", ";

			out << *vi;
		}

		out << std::endl;
	}
}

// end

