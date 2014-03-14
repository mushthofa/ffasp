/***************************************************************************
 *   Copyright (C) 2009 by Mushthofa, Thomas Krennwallner					*
 *   Mushthofa.Mushthofa@UGent.												*
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
 * @file   ProcessBuff.h
 * @author Thomas Krennwallner
 *
 *
 * @brief  Process buffer for external program input/output pipeline
 *
 *
 */


#ifndef _PROCESSBUF_H
#define _PROCESSBUF_H

#include <iostream>
#include <streambuf>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

class ProcessBuf : public std::streambuf
{
        public:
                ProcessBuf();

                ProcessBuf(const ProcessBuf&);

                virtual
                                ~ProcessBuf();

                virtual void
                                endoffile();

                virtual void
                                open(const std::vector<std::string>&);

                virtual int
                                close();
                virtual bool isOpen() const
                {
                        return opened;
                }

        private:
                pid_t process;

                int status;

                int outpipes[2];
                int inpipes[2];

                unsigned bufsize;

                std::streambuf::char_type* obuf;
                std::streambuf::char_type* ibuf;

                void initBuffers();

        protected:
                virtual std::streambuf::int_type
                                overflow(std::streambuf::int_type c);

                virtual std::streambuf::int_type
                                underflow();

                virtual std::streambuf::int_type
                                sync();
                bool opened;
};

#endif // _PROCESSBUF_H
//End

