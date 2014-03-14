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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <boost/algorithm/string/trim.hpp>
#include "Globals.h"

#define MAXDENOM 100
#define MAXK 200
#define MAXT 600
#define REP 0

Globals* Globals::_instance = 0;

Globals::Globals()
{
        //put default options here

        //
        strOpt["solver"] = "clingo";


        intOpt["maxDenom"] = MAXDENOM;
        intOpt["maxk"] = MAXK;
        intOpt["maxt"] = MAXT;
        intOpt["rp"] = REP;
        boolOpt["check"] = false;
        boolOpt["help"] = false;

        //strOpt["DLVArgs"] = "-silent --";
}

Globals* Globals::Instance()
{
        if(_instance == 0)
                _instance = new Globals;

        return _instance;
}

void Globals::processArgs(GetPot cl)
{
        /* Get the options from the command line */
        //bool showHelp = cl.search("--help") || cl.options_contain("h");

        std::string solver =  cl("--solver", "clingo");

        const bool verbose_f = cl.options_contain("vV");

        std::string filter = cl("--filter", "");

        int maxDenom = cl("--maxd",MAXDENOM);

        int maxk = cl("--maxk", MAXK);

        int maxtime = cl("--maxt", MAXT);

        int trans_k = cl("--trans", 0);

        const bool checkOnly = cl.options_contain("-c") || cl.search("--check");
        const bool help = cl.options_contain("-h") || cl.search("--help");

        int rep = cl("--rnd", REP);
        if(rep>0)
        	maxDenom = rep;

        /* Save the options in the internal records */

        strOpt["solver"] = solver;
        intOpt["maxDenom"] = maxDenom;

        if(verbose_f)
                intOpt["verboseLevel"] = 1;

        intOpt["trans"] = trans_k;
        intOpt["maxk"] = maxk;
        intOpt["maxt"] = maxtime;
        boolOpt["check"] = checkOnly;
        intOpt["rp"] = rep;
        boolOpt["help"] = help;

        /* Determine the input file */

        std::string f (cl.next_nominus());
        boost::trim(f);
        if(f.size()>0)
        {
                filename = f;
                boolOpt["fromSTDIN"] = false;
        }
        else
        {
                filename = "<STDIN>";
                boolOpt["fromSTDIN"] = true;
        }

}

bool Globals::boolOption(const std::string& o)
{
        return boolOpt[o];
}

unsigned long Globals::intOption(const std::string& o)
{
        return intOpt[o];
}

std::string Globals::strOption(const std::string& o)
{
        return strOpt[o];
}

void Globals::setOption(const std::string& key, bool val)
{
        boolOpt[key] = val;
}

void Globals::setOption(const std::string& key, unsigned val)
{
        intOpt[key] = val;
}

void Globals::setOption(const std::string& key, const std::string& val)
{
        strOpt[key] = val;
}

const std::string& Globals::getFileName()
{
        return filename;
}

void Globals::setFileName(const std::string& f)
{
        filename = f;
}
// End
