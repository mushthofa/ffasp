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
 * @brief Component Finder using the Boost Graph Library.
 *
 */



#include <sstream>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>

#include "BoostComponentFinder.h"
#include "Globals.h"
//#include "PrintVisitor.h" /* Just for debugging purposes */


void BoostComponentFinder::makeEdges(const std::vector<AtomNodePtr>& nodes,
							  Edges& edges) const
{
	for (std::vector<AtomNodePtr>::const_iterator node = nodes.begin();
		    node != nodes.end();
		    ++node)
	{
		ComponentFinder::Vertex v1 = (*node)->getId();

		//
        	// considering all types of dependencies
		//
		for (std::set<Dependency>::const_iterator d = (*node)->getSucceeding().begin();
				   d != (*node)->getSucceeding().end();
				   ++d)
		{
			ComponentFinder::Vertex v2 = (*d).getAtomNode()->getId();
			edges.push_back(ComponentFinder::Edge(v2, v1));
		}

	}
}

void BoostComponentFinder::selectNodes(	const Vertices& vertices,
								const std::vector<AtomNodePtr>& nodes,
	   std::vector<AtomNodePtr>& newnodes) const
{
	newnodes.clear();
    
	for (ComponentFinder::Vertices::const_iterator vi = vertices.begin();
		    vi != vertices.end();
		    ++vi)
	{
		//
		// TODO: this is too expensive - all the vertices-stuff should actually be done
		// in boost, it could handle all these properties internally.
		// there shouldn't be any mapping and searching here!
		//
		std::vector<AtomNodePtr>::const_iterator an;

		for (an = nodes.begin(); an != nodes.end(); ++an)
		{
			if ((*an)->getId() == *vi)
				break;
		}

		if (an != nodes.end())
		{
			newnodes.push_back(*an);
		}
	}
}


void BoostComponentFinder::findStrongComponents(const std::vector<AtomNodePtr>& nodes,
		std::vector<std::vector<AtomNodePtr> >& sccs)
{
	ComponentFinder::Edges edges;

	makeEdges(nodes, edges);

	//
    // create a label table for the graphviz output
	// FFASP: This is just for debugging purposes, not needed
	/*
	std::vector<std::string> nms;
	nms.resize(nodes.size());

	std::ostringstream oss;
	PrintVisitor rpv(oss);

	for (unsigned y = 0; y < nodes.size(); ++y)
	{
		oss.str("");

		nodes[y]->getAtom()->accept(rpv);

		std::string at(oss.str());
		
		nms[y] = at.c_str();
	}
   */

	using namespace boost;
	{
		typedef adjacency_list <vecS, vecS, directedS> Graph;

		Graph G(0);

		for (Edges::const_iterator ei = edges.begin();
				   ei != edges.end();
				   ++ei)
		{
			add_edge((*ei).first, (*ei).second, G);
		}
		
// 		boost::write_graphviz(std::cout, G);

		std::vector<int> component(num_vertices(G));

		int num = strong_components(G, &component[0]);
				
        //std::cout << "Total number of components: " << num << std::endl;
		// 		
// 		std::copy(component.begin(), component.end(), std::ostream_iterator<int>(std::cout, "\n"));

		std::vector<AtomNodePtr> scc;

		for (int cn = 0; cn < num; ++cn)
		{
			Vertices thiscomponent;

			for (std::vector<int>::size_type i = 0; i != component.size(); ++i)
			{
				if (component[i] == cn)
					thiscomponent.push_back(Vertex(i));
			}

			//
            	// only add components with more than one vertex:
			//
// 			if (thiscomponent.size() > 1)
// 			{
                //components.push_back(thiscomponent);

			scc.clear();
                
			selectNodes(thiscomponent, nodes, scc);

			sccs.push_back(scc);
// 			}
		}
	}
}


// end

