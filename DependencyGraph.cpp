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
 * 	@brief The actual definition of the dependency graph
 * 			Also construct components and components dependency graph
 *	@author Roman Schindlauer, Mushthofa
 */



#include <sstream>
#include <vector>
#include <list>
#include "DependencyGraph.h"


#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/depth_first_search.hpp>


DependencyGraph::DependencyGraph(const NodeGraph& ng, ComponentFinder* cf)
	: nodegraph(ng), componentFinder(cf)
{


	const std::vector<AtomNodePtr> allnodes = nodegraph.getNodes();


	std::vector<std::vector<AtomNodePtr> > strongComponents;

	//
    // keep track of the nodes that belong to a SCC
	//
	std::vector<AtomNodePtr> visited;

	//
    // find all strong components
	//
	getStrongComponents(allnodes, strongComponents);

	//
    // go through strong components
	//
	for (std::vector<std::vector<AtomNodePtr> >::const_iterator scc = strongComponents.begin();
		    scc != strongComponents.end();
		    ++scc)
	{
		
		Component* comp = new ProgramComponent(*scc);
		
		/*
		std::cout<<"SCC = ";
		std::vector<AtomNodePtr>::const_iterator itsc;
		for(itsc=scc->begin(); itsc!=scc->end(); ++itsc)
		{
		std::cout<<*(*itsc)<<" ";
	}
		std::cout<<std::endl;
		*/
		
		
		/* delete empty components */
		/*
		if(comp->getBottom().empty())
		delete comp;
		else*/
		components.push_back(comp);
		
		//
          // mark these scc nodes as visited
          // TODO: this is not so nice here
		//
		for (std::vector<AtomNodePtr>::const_iterator ni = (*scc).begin();
				   ni != (*scc).end();
				   ++ni)
		{
			visited.push_back(*ni);
		}
		
	}
	
	/* Set up dependencies between components */
	
	std::vector<Component*>::iterator ci;
	for(ci=components.begin(); ci!=components.end(); ++ci)
	{
		
		
		std::vector<AtomNodePtr> currentNodes = (*ci)->getNodes();
		/*
		std::cout<<"current component's nodes = ";
		for(std::vector<AtomNodePtr>::iterator ai=currentNodes.begin(); 
		ai!=currentNodes.end(); ++ai)
		{
		std::cout<< *((*ai)->getAtom()) <<", ";
	}
		std::cout<<std::endl;
		
		*/
		
		std::list<AtomNodePtr> previousNodes = (*ci)->getIncomingNodes();
		std::list<AtomNodePtr>::const_iterator pi;
		
		for(pi=previousNodes.begin(); pi!=previousNodes.end(); ++pi)
		{
			std::vector<Component*>::iterator ci2;
			for(ci2=components.begin(); ci2!=components.end(); ++ci2)
			{
				if(ci!=ci2) /* Don't add the current component itself */
				{
					AtomPtr checkAtom = (*pi)->getAtom();
					if((*ci2)->isInComponent(checkAtom))
					{
						/* We want to store the dependency on both sides */
						/* to make it easier to compute labeling and so on.. */
						
						(*ci)->addPreviousComponent(*ci2);
						(*ci2)->addNextComponent(*ci);
						
					}
				}
			}
		}
	}
	
	/* Make the  DAG labeling for each component */
	labelComponents();

}

//void DependencyGraph::

DependencyGraph::~DependencyGraph()
{
	for (std::vector<Component*>::const_iterator ci = components.begin();
		    ci != components.end();
		    ++ci)
	{
		delete *ci;
	}
}

void DependencyGraph::labelComponents()
{
	/* Still empty for now, but later might be used for components simplification and merging */
	
}

bool DependencyGraph::hasNegEdge(const std::vector<AtomNodePtr>& nodes)
{
	for (std::vector<AtomNodePtr>::const_iterator ni = nodes.begin();
		    ni != nodes.end();
		    ++ni)
	{
		//
        	// since an SCC is always cyclic, we only have to consider preceding,
        	// not preceding AND succeeding!
		//
		for (std::set<Dependency>::const_iterator di = (*ni)->getPreceding().begin();
				   di != (*ni)->getPreceding().end();
				   ++di)
		{
			if (((*di).getType() == Dependency::NEG_PRECEDING))
		//|| ((*di).getType() == Dependency::DISJUNCTIVE))
				//
                	// a scc has a negated edge only if the "target" of the edge is also in the cycle!
				//
				if (find(nodes.begin(), nodes.end(), (*di).getAtomNode()) != nodes.end())
					return true;
		}
	}

	return false;
}


void DependencyGraph::getStrongComponents(const std::vector<AtomNodePtr>& nodes,
								  std::vector<std::vector<AtomNodePtr> >& sccs)
{
	componentFinder->findStrongComponents(nodes, sccs);
}

std::vector<Component*> DependencyGraph::getComponents() const
{
	/* If we have only one component, return immediately */
	if(components.size() <= 1)
		return components;
	
	/* Otherwise, return the components in a topological sort */
	std::vector<Component*> sortedComponents;

	using namespace boost;
	{
		typedef adjacency_list <vecS, vecS, directedS> Graph;
		typedef graph_traits<Graph>::vertex_descriptor Vertex;

		Graph G(0);
		
		//typedef std::pair<Component*, Component*> Edge;
		
		std::vector<Component*>::const_iterator cit;
		for(cit = components.begin(); cit != components.end(); ++cit)
		{
			std::set<Component*> previousComp = (*cit)->getPreviousComponents();
			std::set<Component*>::const_iterator pi;

			for(pi=previousComp.begin(); pi!=previousComp.end(); ++pi)
			{
				add_edge((*pi)->getLabel(), (*cit)->getLabel(), G);
			}
		}
		
		typedef std::list<Vertex> Ordering;
		Ordering sortedComp;
		
		/* Do topological sort */
		topological_sort(G, std::front_inserter(sortedComp));
		
		/* Put the result in sortedComponents*/
		
		Ordering::const_iterator oit;
		for(oit = sortedComp.begin(); oit!=sortedComp.end(); ++oit)
		{
			/* Look for the component with the correct label */
			std::vector<Component*>::const_iterator cit;
			for(cit = components.begin(); cit != components.end(); ++cit)
			{
				if((*cit)->getLabel() == *oit)
				{
					sortedComponents.push_back(*cit);
				}
			}
		}
	}
	
	return sortedComponents;
	
}
// End
