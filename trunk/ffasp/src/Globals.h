/***************************************************************************
 *   Copyright (C) 2009 by *
 *   Mushthofa.Mushthofa@UGent.*
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
 * @file   Globals.h
 * @author Roman Schindlauer, Mushthofa
 *
 * @brief  Global parameter class
 *
 */


#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <map>
#include <string>
#include "GetPot.h"

using namespace std;

class Globals
{
        protected:
                Globals();

        public:
                void processArgs(GetPot );

                static Globals* Instance();

                const std::string& getFileName() ;
                bool boolOption(const std::string&) ;
                unsigned long intOption(const std::string&) ;
                std::string strOption(const std::string&) ;

                void setOption(const std::string&, bool);
                void setOption(const std::string&, unsigned);
                void setOption(const std::string&, const std::string&);
                void setFileName(const std::string&);

        private:
                static Globals* _instance;

                std::string filename;

                std::map<std::string, bool> boolOpt;
                std::map<std::string, unsigned long> intOpt;
                std::map<std::string, std::string> strOpt;

};

#endif

// End
