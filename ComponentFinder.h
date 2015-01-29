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


#ifndef _COMPONENTFINDER_H
#define _COMPONENTFINDER_H


#include <map>
#include <vector>
#include <iostream>

#include "AtomNode.h"


/**
 * @brief ComponentFinder.h
 *
 * Finds the components in a dependency graph
 *
 */
class ComponentFinder
{
	public:

		/**
	 * Single Vertex Type.
		 */
		typedef unsigned Vertex;

    		/**
		 * List of Vertices.
		 */
		typedef std::vector<Vertex> Vertices;

    		/**
		 * An Edge is a pair of Vertices.
		 */
		typedef std::pair<Vertex, Vertex> Edge;

    		/**
		 * List of Edges.
		 */
		typedef std::vector<Edge> Edges;

    		/**
		 * A ComponentIdx uniquely identifies a Component.
		 */

    		/**
		 * A ComponentAssignment associates a Vertex with a Component.
		 */


	     /**
		 * A ComponentList is a set of Vertices that belong to a single
		 * Component.
		 */
		typedef std::vector<Vertices> ComponentList;

		virtual ~ComponentFinder() {}

	protected:

    		/// Ctor.
		ComponentFinder()
		{ }

	public:

    	
   		/**
		 * @brief Method for finding Strongly Connected Components.
		 */
		virtual void findStrongComponents(const std::vector<AtomNodePtr>&,
								    std::vector<std::vector<AtomNodePtr> >&)
		{ }

    		/**
		 * @brief For verbose and debugging.
		 */
		void dumpAssignment(const ComponentList&, std::ostream&) const;
};


/**
 * @brief Simple Component finder for testing purposes.
 *
 * This Component Finder puts every Vertex in a single WCC and finds no SCC.
 *
 */

class SimpleComponentFinder : public ComponentFinder
{
	public:

    		/// Ctor.
		SimpleComponentFinder()
		{ }
};

#endif
