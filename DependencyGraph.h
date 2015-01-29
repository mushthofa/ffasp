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
 * 	@brief The actual definition of the dependency graph
 * 			Also construct components and components dependency graph
 *	@author Roman Schindlauer, Mushthofa
 */

 
#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H


#include <vector>

#include "Rule.h"
#include "AtomNode.h"
#include "Component.h"
#include "GraphBuilder.h"
#include "ComponentFinder.h"

class DependencyGraph
{
	public:

   	 	/// Dtor.
		~DependencyGraph();

    		/**
		 * @brief Constructor that builds the dependency graph.
		 *
		 */
		DependencyGraph(const NodeGraph&, ComponentFinder*);
		
    		/**
		 * @brief Creates strongly connected components from AtomNodes.
		 */
		void getStrongComponents(const std::vector<AtomNodePtr>&,
							std::vector<std::vector<AtomNodePtr> >&);
    		/**
		 * @brief Returns all Components.
		 */
		
		std::vector<Component*> getComponents() const;
    
	private:

		bool hasNegEdge(const std::vector<AtomNodePtr>&);
		
		/** 
		 * 	@brief Perform labeling on the components 
		 */
    
		void labelComponents();
		
    		/**
		 * @brief All nodes.
		 */
		NodeGraph nodegraph;
    

    		/**
		 * @brief All components (strongly connected components).
		 */
		std::vector<Component*> components;
		
		/**
		 * @brief ComponentFinder for the dependency graph
		 */
	
		ComponentFinder* componentFinder;
		
};

 
#endif 
// end
