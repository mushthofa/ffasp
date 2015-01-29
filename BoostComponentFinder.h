/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa   								*
 *   unintendedchoice@gmail.com   									*
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
 * @brief Component Finder using the Boost Graph Library.
 *
 */


#ifndef _BOOST_COMPONENT_FINDER_H
#define _BOOST_COMPONENT_FINDER_H


#include <vector>
#include <iostream>

#include "ComponentFinder.h"



class BoostComponentFinder : public ComponentFinder
{
	public:

    		/// Ctor.
		BoostComponentFinder()
		{ }

    	
    	/**
		 * @brief Finds Strongly Connected Components from a list of AtomNodes.
		 */
		virtual void findStrongComponents(const std::vector<AtomNodePtr>&,
								    std::vector<std::vector<AtomNodePtr> >&);
    
	private:

    /**
	 * @brief Converts the AtomNode dependency structure into Edges.
	 *
	 * The Boost Graph Library works with integers as vertex-identifier and
	 * pairs of integers as edges. This function converts the dependency
	 * information of the given AtomNodes and convets it into the Edges type.
		 */
		void makeEdges(const std::vector<AtomNodePtr>&, Edges&) const;

    	/**
		 * @brief Filters a set of AtomNodes based on given Vertices.
		 *
		 * The Boost functions return sets of vertices as result. This function
		 * selects those AtomNodes from a given set that correspond to these
		 * Vertices. The correspondence between AtomNodes and Vertices is based on
		 * the unique ID each AtomNode has.
		 */
		void selectNodes(const Vertices&, 
					  const std::vector<AtomNodePtr>&,
	  std::vector<AtomNodePtr>&) const;
};



#endif 
// end
