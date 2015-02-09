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
 * @file   Component.cpp
 * @author Roman Schindlauer, Mushthofa
 * 
 * @brief  Class representing program components
 * 
 * 
 */

#include "Component.h"

unsigned Component::labelCounter = 0;

Component::Component()
	: evaluated(false), compLabel(labelCounter++)
{
}

Component::~Component()
{
}


void Component::addAtomNode(const AtomNodePtr atomnode)
{
	atomnodes.push_back(atomnode);
}

const std::vector<AtomNodePtr>& Component::getNodes() const
{
	return atomnodes;
}


Program Component::getBottom() const
{
	Program program;
	std::vector<AtomNodePtr>::const_iterator node = atomnodes.begin();

	while (node != atomnodes.end())
	{
		const std::vector<RulePtr>& rules = (*node)->getRules();

		//
        	// add all rules from this node to the component
		//
		for (std::vector<RulePtr>::const_iterator ri = rules.begin();
				   ri != rules.end();
				   ++ri)
		{
			program.addRule(*ri);
		}

		++node;
	}

	return program;
}


bool Component::isInComponent(const AtomPtr at) const
{
	bool belongsToComp = false;

	std::vector<AtomNodePtr>::const_iterator nodeit = atomnodes.begin();

	while (nodeit != atomnodes.end())
	{
		if ((*nodeit++)->getAtom().get() == at.get())
		{
			belongsToComp = true;

			break;
		}
	}
	return belongsToComp;
}

ProgramComponent::ProgramComponent(const std::vector<AtomNodePtr>& nodes)
	: Component()
{
	std::vector<AtomNodePtr>::const_iterator node = nodes.begin();
	while (node != nodes.end())
		addAtomNode(*node++);

	//
	// find incoming nodes: nodes that depend on a node that does not belong to
	// the component
	//
    
	std::vector<AtomNodePtr>::const_iterator ni = atomnodes.begin();

	while (ni != atomnodes.end())
	{
		//
        	// go through all nodes that this node depends on
		//
		std::set<Dependency> deps = (*ni)->getPreceding();

		std::set<Dependency>::const_iterator di = deps.begin();

		while (di != deps.end())
		{
			const AtomNodePtr other = (*di).getAtomNode();

			//
			// if this other node is not in our component, then the current node
			// is an 'incoming' node
			//
			if (find(atomnodes.begin(), atomnodes.end(), other) == atomnodes.end())
			{
				incomingNodes.push_back(other);
                	//std::cerr << "incoming node: " << *other << std::endl;
			}
			++di;
		}
		++ni;
	}


}

ProgramComponent::~ProgramComponent()
{}

void ProgramComponent::evaluate(std::vector<AtomSet>& input)
{
	// TODO: add the actual evaluation method here
	evaluated = true;	
}

void ProgramComponent::dump(std::ostream& out) const
{
	out << "ProgramComponent-object --------------------------------" << std::endl;
	out << "Nodes:";

	for (std::vector<AtomNodePtr>::const_iterator ni = atomnodes.begin();
		    ni != atomnodes.end();
		    ++ni)
	{
		out << " " << (*ni)->getId();
	}

	out << std::endl;

	out << "Bottom:" << std::endl;

	Program bottom = getBottom();

	std::cout<<bottom<<std::endl;



}

// end
