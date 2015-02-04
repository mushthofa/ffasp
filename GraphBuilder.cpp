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
 * @file   GraphBuilder.h
 * @author Roman Schindlauer, Mushthofa
 * 
 * @brief Class to provide methods for generating the dependency graph
 * 
 * 
 */


#include "GraphBuilder.h"
#include "Registry.h"


void GraphBuilder::run(const Program& program, NodeGraph& nodegraph)
{


	//
	// empty the NodeGraph
	//
	nodegraph.reset();
	
	//
	// go through all rules of the given program
	//
	for (Program::iterator r = program.begin();
		    r != program.end();
		    ++r)
	{
		//
		// all nodes of the current rule's head
		//
		std::vector<AtomNodePtr> currentHeadNodes;

		//
		// go through entire head disjunction
		//
		const HeadExpr_t& head = (*r)->getHead();
		HeadList_t headlist = head.first;

		for (HeadList_t::const_iterator hi = headlist.begin();
				   hi != headlist.end();
				   ++hi)
		{
			//
			// add a head atom node. This function will take care of also adding
			// the appropriate unifying dependency for all existing nodes.
			//
			AtomNodePtr hn = nodegraph.addUniqueHeadNode(*hi);

			//
			// go through all head atoms that were alreay created for this rule
			//


			for (std::vector<AtomNodePtr>::iterator currhead = currentHeadNodes.begin();
						  currhead != currentHeadNodes.end();
						  ++currhead)
			{
				//
				// and add disjunctive dependency
				//
				Dependency::addDep(*r, hn, *currhead, Dependency::DISJUNCTIVE);
				Dependency::addDep(*r, *currhead, hn, Dependency::DISJUNCTIVE);
			}

			//
			// add this atom to current head
			//
			currentHeadNodes.push_back(hn);
		}

		//
		// constraint: create virtual head node to keep the rule
		//
		if (headlist.size() == 0)
		{
			AtomPtr va = Registry::Instance()->storeAtom(new DummyAtom());
			
			AtomNodePtr vn = nodegraph.addUniqueHeadNode(va);

			currentHeadNodes.push_back(vn);
		}


		//std::vector<AtomNodePtr> currentOrdinaryBodyNodes;
		std::vector<AtomNodePtr> currentBodyNodes;

		//
		// go through rule body
		//

		const BodyExpr_t& body = (*r)->getBody();
		BodyList_t bodylist = body.first;

		for (BodyList_t::const_iterator li = bodylist.begin();
				   li != bodylist.end();
				   ++li)
		{
			//
			// add a body atom node. This function will take care of also adding the appropriate
			// unifying dependency for all existing nodes.
			//
			AtomNodePtr bn = nodegraph.addUniqueBodyNode((*li)->getAtom());

			
			//if ((typeid(*((*li)->getAtom())) == typeid(Atom)) &&
			if (!(*li)->isNAF())
				currentBodyNodes.push_back(bn);

			//
			// add dependency from this body atom to each head atom
			//
			for (std::vector<AtomNodePtr>::iterator currhead = currentHeadNodes.begin();
						  currhead != currentHeadNodes.end();
						  ++currhead)
			{
				if ((*li)->isNAF())
					Dependency::addDep(*r, bn, *currhead, Dependency::NEG_PRECEDING);
				else
					Dependency::addDep(*r, bn, *currhead, Dependency::PRECEDING);
				
				/* We set up a dummy dependency between the body literals and the empty head
				 literals to force a constraint to be included in the components where its
				body literals are resolved 
				Eg: 
					a v b :- c.
					:- not a.
				
					by setting up a dummy dependecy from a to _ (empty head), we force 
					the constraint :- not a to be in an scc along with a v b :- c.
				*/
				
				if(headlist.size() == 0)
				{
					if ((*li)->isNAF())
						Dependency::addDep(*r, *currhead, bn, Dependency::NEG_PRECEDING);
					else
						Dependency::addDep(*r, *currhead, bn, Dependency::PRECEDING);
				
				}
			}
		} // body finished
	}
}

void GraphBuilder::dumpGraph(const NodeGraph& nodegraph, std::ostream& out) const
{
	out << "Dependency graph - Program Nodes:" << std::endl;

	for (std::vector<AtomNodePtr>::const_iterator node = nodegraph.getNodes().begin();
		    node != nodegraph.getNodes().end();
		    ++node)
	{
		out << **node << std::endl;
	}

	out << std::endl;
}
