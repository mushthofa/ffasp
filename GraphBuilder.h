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
 * @file   GraphBuilder.h
 * @author Roman Schindlauer, Mushthofa
 * 
 * @brief Class to provide methods for generating the dependency graph
 * 
 * 
 */


#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "Component.h"
#include "Program.h"


class GraphBuilder
{
	public:

    	/**
	 * @brief Takes a set of rules and builds the according node graph.
	 *
	 * This nodegraph will contain the entire dependency graph of the program,
	 * including any artificial nodes that had to be created for auxiliary
	 * rules, e.g., for external atoms with variable input parameters.
	 */
		void run(const Program&, NodeGraph&);
	
	/**
		 * @brief Debug dump.
	 */
		void dumpGraph(const NodeGraph&, std::ostream&) const;

	private:

//    void
//    addDep(AtomNode*, AtomNode*, Dependency::Type);

};

#endif

//end

