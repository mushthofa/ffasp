
/***************************************************************************
 *   Copyright (C) 2014 by Mushthofa                                             *
 *   Mushthofa.Mushthofa@Ugent.be                                                                         *
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
 * @file   Number.h
 * @author Mushthofa
 *
 *
 * @brief  Number related algorithm
 *
 *
 *//*
 * Number.h
 *
 *  Created on: Feb 21, 2014
 *      Author: mush
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <vector>
#include <iostream>
#include "Globals.h"



inline int gcd(int a, int b)
{
	if(b==0)
		return a;
	else return gcd(b, a%b);
}

inline int lcm(int a, int b)
{
	return a*(b/gcd(a,b));
}

inline int gcd(std::set<int> a)
{
	if(a.size()==0) return 1;
	int r=*(a.begin());
	std::set<int>::iterator it;
	for(it=a.begin(); it!=a.end(); it++)
		r=gcd(r,*it);
	return r;
}

inline int lcm(std::set<int> a)
{
	if(a.size()==0) return 1;
	int r=*(a.begin());
	std::set<int>::iterator it;
	for(it=a.begin(); it!=a.end(); it++)
		r=lcm(r,*it);
	return r;
}

inline double myabs(double a)
{
	return ((a)>=0? (a): (-a));
}

inline std::pair<int, int> float2rat(double startx, int maxden)
{

	/*
	if(startx<=0) return std::make_pair(0,1);
	if(startx>=1) return std::make_pair(1,1);

	long m[2][2];
	double x;
	long ai;

	x = startx;
	m[0][0] = m[1][1] = 1;
	m[0][1] = m[1][0] = 0;

	while (m[1][0] *  ( ai = (long)x ) + m[1][1] <= maxden)
	{
		long t;
		t = m[0][0] * ai + m[0][1];
		m[0][1] = m[0][0];
		m[0][0] = t;
		t = m[1][0] * ai + m[1][1];
		m[1][1] = m[1][0];
		m[1][0] = t;
		if(x==(double)ai) break;     // AF: division by zero
			x = 1/(x - (double) ai);
		if(x>(double)0x7FFFFFFF)
			break;  // AF: representation failure
	}

	int a1,b1,a2,b2;
	double e1,e2;

	a1=m[0][0];
	b1=m[1][0];
	e1=startx - ((double) m[0][0] / (double) m[1][0]);

	ai = (maxden - m[1][1]) / m[1][0];
	m[0][0] = m[0][0] * ai + m[0][1];
	m[1][0] = m[1][0] * ai + m[1][1];

	a2=m[0][0];
	b2=m[1][0];
	e2=startx - ((double) m[0][0] / (double) m[1][0]);

	double error1 = myabs(e1), error2 = abs(e2);


	if(error1<error2)
		return std::make_pair(a1,b1);
	else
		return std::make_pair(a2,b2);

	*/
	/*
	int den = 1, a;
	bool f=false;
	while(den<=maxden)
	{
		a = (int)(den*startx);
		float r = den*startx;
		if(r==a)
		{
			f=true;
			break;
		}
		den *= 10;
	}
	if(!f) den /= 10;
	return std::make_pair(a,den);
	*/

	int nom = (int) (startx*maxden+0.5);
	int d = gcd(nom, maxden);
	return std::make_pair(nom/d,maxden/d);
}

class Rational
{
public:
	Rational(int aa, int bb)
	{
		if(aa>bb)
		{
			a=b=1;
		}
		else
		{
			int d=gcd(aa,bb);
			a = aa/d;
			b = bb/d;
		}

	}

	Rational(double c)
	{
		std::pair<int,int> rat =
				float2rat(c, (int)Globals::Instance()->intOption("maxDenom"));

		a = rat.first;
		b = rat.second;
	}

	Rational()
	:a(1), b(1)
	{}

	int getNom() const
	{
		return a;
	}

	int getDenom() const
	{
		return b;
	}

	double getFloat() const
	{
		return (float)a/(float)b;
	}

	bool operator==(const Rational& r) const
	{
		return a*r.b == b*r.a;
	}
	bool operator!=(const Rational& r) const
	{
		return !(*this==r);
	}

	bool operator<(const Rational& r) const
	{
		return a*r.b < b*r.a;
	}

	bool operator<=(const Rational& r) const
	{
		return (*this<r) || (*this==r);
	}

	bool operator>(const Rational& r) const
	{
		return !(*this<=r) ;
	}

	bool operator>=(const Rational& r) const
	{
		return !(*this<r);
	}


protected:
	int a,b;
};

std::ostream& operator<<(std::ostream& os, const Rational& r);



#endif /* NUMBER_H_ */
