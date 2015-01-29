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
 * @file   Component.h
 * @author Roman Schindlauer, Mushthofa
 * 
 * @brief  Class representing program components
 * 
 * 
 */


#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <list>
#include "Program.h"
#include "AtomSet.h"
#include "AtomNode.h"
//#include "PrintVisitor.h"


class Component
{
	public:

   		/// Dtor.
		virtual ~Component();

    		

    		/**
		 * @brief Adds an AtomNode to the component.
		 */
		void addAtomNode(const AtomNodePtr);

    		/**
		 * @brief Returns all AtomNodes of this component.
		 */
		const std::vector<AtomNodePtr>& getNodes() const;
    
    		/**
		 * @brief Returns the rules that belong to this component.
		 */
		Program getBottom() const;
				
    		/**
		 * Serialize component to stream out for verbose and debugging.
		 */
		virtual void dump(std::ostream& out) const = 0;

    		/**
		 * @brief Checks if the spcified Atom occurs in the component.
		 */
		
		bool isInComponent(const AtomPtr) const;
		std::list<AtomNodePtr> getIncomingNodes() const
		{
			return incomingNodes;
		}
		
		std::set<Component*> getPreviousComponents() const
		{
			return previousComponents;
		}
		
		void addPreviousComponent(Component* c)
		{
			previousComponents.insert(c);
		}
		
		std::set<Component*> getNextComponents() const
		{
			return nextComponents;
		}
		
		void addNextComponent(Component* c)
		{
			nextComponents.insert(c);
		}
		
		unsigned getLabel() const
		{
			return compLabel;
		}
		
		
	protected:
		Component();

    		/**
		 * @brief AtomNodes that belong to this component.
		 */
		
		std::vector<AtomNodePtr> atomnodes;
		
		bool evaluated;

		std::vector<AtomSet> result;

		std::list<AtomNodePtr> incomingNodes;
		
		/* Set of components for which this component depends on */
		std::set<Component*> previousComponents;
		
		/* Set of components dependent on this component */
		
		std::set<Component*> nextComponents;
		
		unsigned compLabel;
		static unsigned labelCounter;

};


class ProgramComponent : public Component
{
	public:
    		/// Ctor.
		ProgramComponent(const std::vector<AtomNodePtr>&);
    		/// Dtor.
		~ProgramComponent();
    		/**
		 * @brief Computes the model(s) of the subprogram of this component.
		 */
		
		virtual void evaluate(std::vector<AtomSet>&);


    		/**
		 * @brief Adds a node pointer to the component.
		 */ 
    		/**
		 * Serialize component to stream out for verbose and debugging.
		 */ 
		virtual void dump(std::ostream& out) const;


	protected:
    
};


#endif
//


