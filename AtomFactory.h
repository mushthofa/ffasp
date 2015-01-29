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
 * @file   AtomFactory.h
 * @author Roman Schindlauer
 * @date   Sat Feb  4 19:09:02 CET 2006
 * 
 * @brief  Singleton class for storing atoms.
 * 
 * 
 */

#ifndef _ATOMFACTORY_H
#define _ATOMFACTORY_H

#include <vector>

#include "Atom.h"
#include "AtomSet.h"

/**
 * @brief The Factory stores all (ground) atoms that emerge in the course of
 *  			solving the program.
 */

class AtomFactory
{
	public:

    		/**
	 * @brief Get (unique) instance of the static factory class.
		 */
		static AtomFactory* Instance();

    		/**
		 * @brief Inserts an Atom into the Factory.
		 *
		 * 
		 */
		AtomPtr insert(Atom*);

    		/**
		 * @brief Clears the Factory
		 */
		void reset();

	protected:

		AtomFactory()
		{ }

		~AtomFactory();

	private:

		AtomSet::atomset_t atoms;

		static AtomFactory* _instance;
};

#endif

// end
