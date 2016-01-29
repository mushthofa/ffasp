/*
 * MIPRegistry.h
 *
 *  Created on: Feb 1, 2015
 *      Author: mushthofa
 */



#ifndef MIPREGISTRY_H_
#define MIPREGISTRY_H_

#include "Program.h"
#include <boost/lexical_cast.hpp>

// One (binary) expression
typedef struct
{
	AtomPtr a1, a2;
	FuzzyOp_t op;
} Expr_t ;

// Type of bound for the MIP variables: both, upper, lower, or fixed
typedef enum {LU, LB, UB, FIX} BoundType_t;

// A column variable
typedef struct
{
	std::string name;
	// Bounds
	Rational ub, lb;
	// coefficient in the objective function
	int objcoeff;
	// whether the var is binary/not (all vars are in [0,1] bound)
	bool isBin;
	BoundType_t boundtype;
} ColVar_t;

// A row variable

typedef struct
{
	std::string name;
	// Bounds
	Rational ub, lb;
	// Column coefficients of the row var
	std::vector<int> coef;
	BoundType_t boundtype;
} RowVar_t;


inline bool operator<(Expr_t a, Expr_t b)
{
	if (a.op < b.op)
		return true;
	else if(a.op == b.op)
		return a.a1 < b.a1;
	else if(a.op==b.op && a.a1 == b.a1)
		return a.a2 < b.a2;
	else
		return false;
}


class MIPRegistry
{
public:
	MIPRegistry(const Program& p, const FAnswerSet& as)
	:atomcounter(0), expcounter(0), colcounter(0), rowcounter(0), varnamecounter(0)
	{
		buildMap(p);
		assignColsIdx();
		buildRowExpr();
		buildRowRules(p, as);
		updateColBounds(as);
	}

	void buildMap(const Program& p)
	{
		/* Build a simple map of all atoms and expression in the program */
		Program::iterator r;
		for(r=p.begin(); r!=p.end(); ++r)
		{
			// Construt map of all the atoms

			HeadExpr_t head = (*r)->getHead();
			HeadList_t hl = head.first;
			HeadList_t::iterator hit;
			for(hit = hl.begin(); hit!=hl.end(); ++hit)
				insertAtom(*hit);

			BodyExpr_t body = (*r)->getBody();
			BodyList_t bl = body.first;
			BodyList_t::iterator bit;
			for(bit=bl.begin(); bit!=bl.end(); ++bit)
			{
				AtomPtr b = (*bit)->getAtom();
				insertAtom(b);
			}

			// Construct map of all the (binary) expression

			if(hl.size() > 1)
			{
				Expr_t e;
				e.a1 = hl[0];
				e.a2 = hl[1];
				e.op = head.second;
				insertExpr(e);
			}

			if(bl.size() > 1)
			{
				Expr_t e;
				e.a1 = bl[0]->getAtom();
				e.a2 = bl[1]->getAtom();
				e.op = body.second;
				insertExpr(e);
			}

		} // End for Program iterator
	}


	void assignColsIdx()
	{
		/* Assign column indexes for column variables, by mapping
		 * from their respective map values (atom/expr) to
		 * increasing counter of columns indexes
		 *
		 * Also, create the appropriate column variables and store in the vector
		 */

		// Allocate vectors
		colsAtom.resize(atomcounter);
		colsNegAtom.resize(atomcounter);
		colsVal.resize(expcounter);
		colsBin.resize(expcounter);

		// For atoms and negated atoms variables, we go through the atom map
		std::map<AtomPtr, int>::iterator atomit;
		for(atomit=atommap.begin(); atomit!=atommap.end(); ++atomit)
		{
			colsAtom[atomit->second] =  colcounter++;
			colsNegAtom[atomit->second] = colcounter++;

			// Store into col vars vector
			ColVar_t vatom;
			vatom.name = getNextName();
			vatom.lb = Rational(0,1);
			vatom.ub = Rational(1,1);
			vatom.objcoeff = 1;
			vatom.isBin = false;
			vatom.boundtype = LU;
			colVars.push_back(vatom);

			ColVar_t vnatom;
			vnatom.name = getNextName();
			vnatom.lb = Rational(0,1);
			vnatom.ub = Rational(1,1);
			vnatom.objcoeff = 0;
			vnatom.isBin = false;
			vnatom.boundtype = LU;
			colVars.push_back(vnatom);
		}

		// For Vals, Bin Aux (z), we go through all expressions in exprmap
		std::map<Expr_t, int>::iterator exprit;
		for(exprit=expmap.begin(); exprit!=expmap.end(); ++exprit)
		{
			// All 4 types of expressions have vals
			colsVal[exprit->second] = colcounter++;
			// Store the column vars into the vector
			ColVar_t vexpr;
			vexpr.name = getNextName();
			vexpr.lb = Rational(0,1);
			vexpr.ub = Rational(1,1);
			vexpr.boundtype = LU;
			vexpr.objcoeff = 0;
			vexpr.isBin = false;
			colVars.push_back(vexpr);

			// Only + and x have binary auxiliary vars
			if(exprit->second == TNORM || exprit->second == CO_TNORM)
			{
				colsBin[exprit->second] = colcounter++;
				ColVar_t zexpr;
				zexpr.name = getNextName();
				zexpr.lb = Rational(0,1);
				zexpr.ub = Rational(1,1);
				zexpr.boundtype = LU;
				zexpr.objcoeff = 0;
				zexpr.isBin = true;		// This is the only binary variable
				colVars.push_back(zexpr);
			}

		}

		// colcounter now = number of column variables;
	}


	void buildRowExpr()
	{
		// Building the row variables imposed by the atoms and expressions

		/* 1. For every atom a, create rowvar x = v_a + v_nota
		 * and set its value to 1, i.e., v_a + v_nota = 1
		 */

		// At this point, we know that # column vars = colcounter
		// So every row vars is intialised with colcounter number of coefficients

		std::map<AtomPtr,  int>::iterator atomit;
		for (atomit=atommap.begin(); atomit!= atommap.end(); ++atomit)
		{
			RowVar_t rv;
			rv.name = getNextName();
			// Set the value to be exactly one
			rv.lb = Rational(1,1);
			rv.ub = Rational(1,1);
			rv.boundtype = FIX;
			// Allocate coefficients and initialize with 0s
			rv.coef.assign(colcounter, 0);
			std::vector<pair<int, int> > coef;
			int idxatom = atomit->second;
			int idxvatom = colsAtom[idxatom];
			int idxvnatom = colsNegAtom[idxatom];
			// Set 1s on the the two columns variables
			rv.coef[idxvatom] = 1;
			rv.coef[idxvnatom] = 1;
			// Store the row variables;
			rowVars.push_back(rv);
		}

		/* Now we scan exprmap to perform MIP translation to every expression
		 * a+b, a x b, a v b or a^b
		 * Create all necessary row variables
		 * Notice that for a x b, the corresponding column vars (colVars) is the negated version
		 * of what v_{axb} should be valued, i.e., when translating rules containing it, we must
		 * treat the variable in colVars[axb] as 1-v_{axb}.
		 */

		std::map<Expr_t, int>::iterator expit;
		for(expit=expmap.begin(); expit!=expmap.end(); ++expit)
		{
			Expr_t e = expit->first;
			int idxme = expit->second;

			// Get the column variable indices for the operands (v_a and v_b)
			AtomPtr a1 = e.a1;
			AtomPtr a2 = e.a2;

			int idxva = colsAtom[atommap[a1]];
			int idxvb = colsAtom[atommap[a2]];

			// Get the index of the column variable corresponding to the expr (v_e)

			int idxve = colsVal[idxme];
			RowVar_t r1, r2, r3, r4;
			int idxze = colsBin[expmap[e]], idxvna, idxvnb;
			switch(e.op)
			{
			case CO_TNORM:
				/*
				 *  2. Translate every a+b into
				 *   r1 = v_a + v_b + z_{a+b} - v_{a+b}		r1>=0
				 *   r2 = v_a + v_b - z_{a+b} -v_{a+b} 		r2<=0
				 *   r3 = v_a + v_b - z_{a+b}				 0<=r3<=1
				 *   r4 = v_{a+b} - z{a+b}				 	r4 >= 0
				 */

				// Get indices of the z_variables;


				r1.name = getNextName();

				// Initialize coefficients
				r1.coef.assign(colcounter,0);
				// r1 = v_a + v_b + z_{a+b} - v_{a+b}
				// Note: coefficients for atoms and neg atoms must always be incremented
				// to allow the same atom becoming both operands, so the coefficient = 2

				r1.coef[idxva]++;
				r1.coef[idxvb]++;
				r1.coef[idxze] = 1;
				r1.coef[idxve] = -1;

				// Set bounds r1 >= 0
				r1.boundtype = LB;
				r1.lb = Rational(0,1);
				r1.ub = Rational(1,1);
				// Store;
				rowVars.push_back(r1);

				r2.name = getNextName();
				// Initialize coefficients
				r2.coef.assign(colcounter, 0);
				// r2 = v_a + v_b - z_{a+b} - v_{a+b}
				r2.coef[idxva]++;
				r2.coef[idxvb]++;
				r2.coef[idxze] = -1;
				r2.coef[idxve] = -1;

				// Set bounds r2 <= 0
				r2.boundtype = UB;
				r2.lb = Rational(-1,1);
				r2.ub = Rational(0, 1);
				// Store
				rowVars.push_back(r2);

				r3.name = getNextName();

				// r3 = v_a + v_b - z_{a+b}
				r3.coef.assign(colcounter, 0);
				r3.coef[idxva] = 1;
				r3.coef[idxvb] = 1;

				r3.boundtype = LU;
				r3.lb = Rational(0,1);
				r3.ub = Rational(1,1);
				rowVars.push_back(r3);

				r4.name = getNextName();
				//r4 = v_{a+b} - z_{a+b}
				r4.coef.assign(colcounter, 0);
				r4.coef[idxve] = 1;
				r4.coef[idxze] = -1;
				// Bound r4>=0
				r4.boundtype = LB;
				r4.lb = Rational(0,1);
				r4.ub = Rational(1,1);
				// Store

				rowVars.push_back(r4);
				// Done
				break;
			case TNORM:
				/*
				 *  Let v'_a and v'_b be the MIP column variables corresponding to not a and not b
				 *  We translate a x b into v'_{axb} defined by MIP constraints as follows
				 *
				 *  r1 = v'_a + v'_b + z_{axb} - v'_{axb}		r1>= 0
				 *  r2 = v'_a + v'_b - z_{axb} - v'_{axb}		r2<= 0
				 *  r3 = v'_a + v'_b - z_{axb}				0 <=r3<= 1
				 *	r4 = v'_{axb} - z_{axb}						r4>= 0
				 */

				// Get the indices for the column variables of the negated atoms not a and not b
				idxvna = colsNegAtom[atommap[a1]];
				idxvnb = colsNegAtom[atommap[a2]];


				r1.name = getNextName();
				r1.coef.assign(colcounter, 0);
				// r1 = v'_a + v'_b + z_{axb} - v'_{axb}
				r1.coef[idxvna]++;
				r1.coef[idxvnb]++;
				r1.coef[idxze] = 1;
				r1.coef[idxve] = -1;
				// Set bounds r1 >= 0
				r1.boundtype = LB;
				r1.lb = Rational(0,1);
				r1.ub = Rational(1,1);
				// Store;
				rowVars.push_back(r1);

				r2.name = getNextName();
				// Initialize coefficients
				r2.coef.assign(colcounter, 0);
				// r2 = v'_a + v'_b - z_{axb} - v_{axb}
				r2.coef[idxvna]++;
				r2.coef[idxvnb]++;
				r2.coef[idxze] = -1;
				r2.coef[idxve] = -1;

				// Set bounds r2 <= 0
				r2.boundtype = UB;
				r2.lb = Rational(-1,1);
				r2.ub = Rational(0,1);
				// Store
				rowVars.push_back(r2);

				r3.name = getNextName();

				// r3 = v'_a + v'_b - z_{axb}
				r3.coef.assign(colcounter, 0);
				r3.coef[idxvna] = 1;
				r3.coef[idxvnb] =

				r3.boundtype = LU;
				r3.lb = Rational(0,1);
				r3.ub = Rational(1,1);
				rowVars.push_back(r3);

				r4.name = getNextName();
				//r4 = v'_{axb} - z_{axb}
				r4.coef.assign(colcounter, 0);
				r4.coef[idxve] = 1;
				r4.coef[idxze] = -1;
				// Bound r4>=0
				r4.boundtype = LB;
				r4.lb = Rational(0,1);
				r4.ub = Rational(1,1);
				// Store

				rowVars.push_back(r4);
				// Done
				break;

			case MAX:
				/*
				 * Translate a v b into the set of MIP constraints
				 *
				 * r1  = v_{avb} - v_a		r1 >= 0
				 * r2  = v_{avb} - v_a		r2 >= 0
				 *
				 */

				// r1  = v_{avb} - v_a		r1 >= 0
				r1.name = getNextName();
				r1.coef.assign(colcounter, 0);
				r1.coef[idxve] = 1;
				r1.coef[idxva] = -1;
				r1.boundtype = LB;
				r1.lb = Rational(0,1);
				r1.ub = Rational(1,1);
				rowVars.push_back(r1);

				// r2  = v_{avb} - v_a		r2 >= 0
				r2.name = getNextName();
				r2.coef.assign(colcounter, 0);
				r2.coef[idxve] = 1;
				r2.coef[idxvb] = -1;
				r2.boundtype = LB;
				r2.lb = Rational(0,1);
				r2.lb = Rational(1,1);
				rowVars.push_back(r2);
				// Done
				break;
			case MIN:

				/*
				 * Translate a ^ b into the set of MIP constraints
				 *
				 * r1  = - v_{a^b} + v_a		r1 >= 0
				 * r2  = - v_{a^b} + v_a		r2 >= 0
				 *
				 */

				//  r1  = - v_{a^b} + v_a		r1 >= 0
				r1.name = getNextName();
				r1.coef.assign(colcounter, 0);
				r1.coef[idxve] = -1;
				r1.coef[idxva] = 1;
				r1.boundtype = LB;
				r1.lb = Rational(0,1);
				r1.ub = Rational(1,1);
				rowVars.push_back(r1);

				// r2  = - v_{a^b} + v_a		r2 >= 0
				r2.name = getNextName();
				r2.coef.assign(colcounter, 0);
				r2.coef[idxve] = -1;
				r2.coef[idxvb] = 1;
				r2.boundtype = LB;
				r2.lb = Rational(0,1);
				r2.lb = Rational(1,1);
				rowVars.push_back(r2);
				// Done
				break;

				break;
			default:
				throw FatalError("In buildRowExpr(): unknown operator type!");
			} // End switch(

		}// For expr in expmap
	}



	void buildRowRules(const Program& p, const FAnswerSet& as)
	{
		/*
		 *  Build row variables from each rule in the program
		 *  1. If rule is
		 *   a <- #c
		 *   or
		 *   #c <- a
		 *
		 *   then we don't create new row variables, but instead only update the bounds for corresponding
		 *   column variables (v_a)
		 *
		 *   2. If rule is of the form
		 *   a <- b
		 *   create new row variable
		 *   r1 = v_a - v_b and set r1>=0
		 *
		 *  3. If rule is of the form
		 *   a <- not b
		 *   then, since we want to check minimality against the reduct p^as,
		 *   we only update the bound for a, i.e., if lower bound of v_a < 1-as[b], set it to 1-as[b]
		 *
		 *
		 *  4. If rule is of the form
		 *   a <- b op c
		 *   then create new row variable
		 *   r1 = v_a - v_e, where e=b op c, and set r1 >= 0
		 *   UNLESS e = b x c, in which what we have is v'_e, and hence we must create
		 *   r1 = v_a + v'_e  and set r1 >= 1
		 *
		 *   5. If rule is of the form
		 *   a op b <- c
		 *   then create new row variable
		 *   r1 = v_e - v_c, where e=a op b, and set r1 >= 0
		 *   UNLESS e = a x b, in which what we have is v'_e, and hence we must create
		 *   r1 = v_c + v'_e and set r1 >= 1
		 *
		 *   6. Catch exception when rules is not of the above forms (due to problems in rewriting)
		 *
		 *
		 */

		Program::iterator it;
		for(it=p.begin(); it!=p.end(); ++it)
		{
			HeadExpr_t head = (*it)->getHead();
			BodyExpr_t body = (*it)->getBody();
			HeadList_t hl = head.first;
			BodyList_t bl = body.first;

			// Check for a <- #c
			if  (hl.size() == 1 && bl.size() == 1 &&
				 typeid(*hl[0]) != typeid(ConstantAtom) &&
				 typeid(*(bl[0]->getAtom())) == typeid(ConstantAtom)
				)
			{
				// Get index of v_a
				int idxva = colsAtom[atommap[hl[0]]];
				// If current lower bound of v_a < c, then change it to c;
				AtomPtr atomc = bl[0]->getAtom();
				Rational c = atomc->getRat();
				if(colVars[idxva].lb < c && colVars[idxva].ub >= c)
					colVars[idxva].lb = c;
			}
			// Check for #c <- a
			else if(hl.size() == 1 && bl.size() == 1 &&
					 typeid(*hl[0]) == typeid(ConstantAtom) &&
					 typeid(*(bl[0]->getAtom())) != typeid(ConstantAtom))
			{
				AtomPtr atoma = bl[0]->getAtom();
				int idxva = colsAtom[atommap[atoma]];
				// If current upper bound for v_a is > c, then change it to c;
				AtomPtr atomc = hl[0];
				Rational c = atomc->getRat();
				if(colVars[idxva].ub > c && colVars[idxva].lb <= c)
					colVars[idxva].ub = c;
			}
			// Check for a <- b and a <- not b
			else if(hl.size() == 1 && bl.size() == 1 &&
					 typeid(*hl[0]) != typeid(ConstantAtom) &&
					 typeid(*(bl[0]->getAtom())) != typeid(ConstantAtom))
			{
				AtomPtr a = hl[0];
				AtomPtr b = bl[0]->getAtom();

				// Get index of a
				int idxva = colsAtom[atommap[a]];
				// If NAF, only update the bounds for column variable v_a to the value of 1-as[b]
				if(bl[0]->isNAF())
				{
					Rational asb = as[b];
					if(colVars[idxva].lb < asb && colVars[idxva].ub >= asb)
						colVars[idxva].lb = asb;
				}
				else
				{
					// Create r = v_a - v_b
					int idxvb = colsAtom[atommap[b]];

					RowVar_t r;
					r.name = getNextName();
					r.coef.assign(colcounter, 0);
					// To avoid trouble in cases like a <- a, use increment
					r.coef[idxva] ++;
					r.coef[idxvb] --;
					// set r >= 0
					r.boundtype = LB;
					r.lb = Rational(0,1);
					r.ub = Rational(1,1);
					//Store
					rowVars.push_back(r);
				}
			}
			// Check for a <- b op c
			else if(hl.size() == 1 && bl.size() == 2)
			{
				// Get the atom a and expr e = b op c
				AtomPtr a = hl[0];
				Expr_t e;
				e.a1 = bl[0]->getAtom();
				e.a2 = bl[1]->getAtom();
				e.op = body.second;
				// Get indices v_a and v_e
				int idxva = colsAtom[atommap[a]];
				int idxve = colsVal[expmap[e]];

				// Create row variable
				RowVar_t r;
				r.name = getNextName();
				r.coef.assign(colcounter, 0);

				if(e.op == TNORM) // if op = x
				{
					// Create row variable r = v_a + v_e
					r.coef[idxva]++;
					r.coef[idxve]++;
					// set r>=1
					r.boundtype = LB;
					r.lb = Rational(1,1);
					// UB Not used ?
					r.ub = Rational(1,1);
				}
				else
				{
					// Create row variable r = v_a - v_e
					r.coef[idxva]++;
					r.coef[idxve] = -1;
					// set r>=0
					r.boundtype = LB;
					r.lb = Rational(0,1);
					r.ub = Rational(1,1);
				}
				// Store
				rowVars.push_back(r);
			}
			// check for a op b <- c
			else if(hl.size() == 2 && bl.size() == 1)
			{
				// Get the atom c and expr e = a op b
				AtomPtr c = bl[0]->getAtom();
				Expr_t e;
				e.a1 = hl[0];
				e.a2 = hl[1];
				e.op = head.second;
				// Get indices v_a and v_e
				int idxva = colsAtom[atommap[c]];
				int idxve = colsVal[expmap[e]];


				RowVar_t r;
				r.name = getNextName();
				r.coef.assign(colcounter, 0);

				if(e.op == TNORM)
				{
					// Create row variable r = v_e + v_a
					r.coef[idxva]++;
					r.coef[idxve] = 1;

					// set r>=1
					r.boundtype = LB;
					r.lb = Rational(1,1);
					r.ub = Rational(1,1);
				}
				else
				{
					// Create row variable r = v_e - v_a
					r.coef[idxva]--;
					r.coef[idxve] = 1;

					// set r>=0
					r.boundtype = LB;
					r.lb = Rational(0,1);
					r.ub = Rational(1,1);
				}

				// Store
				rowVars.push_back(r);
			}
			else
			{
				std::ostringstream oss;
				oss << "In buildRowRules(): unrecognized rule: "<<std::endl;
				oss << *(*it) << std::endl;
				throw FatalError(oss.str());
			}

		}
	}

	void updateColBounds(const FAnswerSet& as)
	{
		/* Go through all the atoms in the answer set and update bounds for corresponding col variables
		 *
		 */
		Inter_t interp = as.getInter();
		Inter_t::iterator it;
		for(it = interp.begin(); it!=interp.end(); ++it)
		{
			AtomPtr a = it->first;
			Rational v = it->second;
			int idxva = colsAtom[atommap[a]];
			//if(colVars[idxva].name == "v0")
				//std::cout<<"update column bounds "<<colVars[idxva].ub<<" with "<<v<<endl;
			if(colVars[idxva].ub > v && colVars[idxva].lb <= v)
				colVars[idxva].ub = v;
		}

	}

	/* Auxilary functions for inserting into the maps */
	void insertAtom(AtomPtr a)
	{
		// Skip constant atoms;
		if(typeid(*a) == typeid(ConstantAtom))
			return;
		std::map<AtomPtr, int>::iterator it = atommap.lower_bound(a);
		if(it!=atommap.end() && !(atommap.key_comp()(a, it->first)))
			return;
		atommap.insert(it, std::map<AtomPtr, int>::value_type(a, atomcounter++));
	}


	void insertExpr(Expr_t a)
	{
		std::map<Expr_t, int>::iterator it = expmap.lower_bound(a);
		if(it!=expmap.end() && !(expmap.key_comp()(a, it->first)))
			return;
		expmap.insert(it, std::map<Expr_t, int>::value_type(a, expcounter++));

	}


	std::string getNextName()
	{
		return std::string("v")+boost::lexical_cast<std::string>(varnamecounter++);
	}


	// Counters for maps
	int atomcounter;
	int expcounter;

	int colcounter;
	int rowcounter;

	// Map of all atoms and expressions
	std::map<AtomPtr, int> atommap;
	std::map<Expr_t, int> expmap;

	// Map of indices for the MIP column variables
	// e.g., colsAtom[i] contains the column variable index for atom in atommap[i]
	// while colsVal[i] contains the column variable index for the val expression in expmap[i]

	std::vector<int> colsAtom;	// atom variables
	std::vector<int> colsNegAtom;	// negated atom variables
	std::vector<int> colsVal;	// values of expression variables
	std::vector<int> colsBin;	// auxilary (z) binary variables (for + and x)

	// Vector of all MIP column and row variables;

	std::vector<ColVar_t> colVars;
	std::vector<RowVar_t> rowVars;

	int varnamecounter;
};

//int MIPRegistry::varnamecounter = 0;


#endif /* MIPREGISTRY_H_ */
