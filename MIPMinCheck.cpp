/*
 * MIPMinCheck.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: mushthofa
 */

#include "MIPMinCheck.h"

void MIPMinCheck::writeMPS()
{
	// Set up minimizing problem
	glp_prob *lp;
	lp = glp_create_prob();
	glp_set_prob_name(lp, "chekmin");
	glp_set_obj_dir(lp, GLP_MIN);

	// Size of the matrix
	int nCols = mipreg.colVars.size();
	int nRows = mipreg.rowVars.size();

	// Adding columns
	glp_add_cols(lp, nCols);
	int i,j,counter;
	for(i=0; i<nCols; i++)
	{
		ColVar_t colvar = mipreg.colVars[i];
		glp_set_col_name(lp, i+1, colvar.name.c_str());
		// Set bounds
		switch (colvar.boundtype)
		{
		case LB:
			glp_set_col_bnds(lp, i+1, GLP_LO, colvar.lb.getFloat(), colvar.ub.getFloat());
			break;
		case UB:
			glp_set_col_bnds(lp, i+1, GLP_UP, colvar.lb.getFloat(), colvar.ub.getFloat());
			break;
		case FIX:
			glp_set_col_bnds(lp, i+1, GLP_FX, colvar.lb.getFloat(), colvar.ub.getFloat());
			break;
		default:	// LU
			glp_set_col_bnds(lp, i+1, GLP_DB, colvar.lb.getFloat(), colvar.ub.getFloat());
			break;
		}
		// Set objective coeff
		glp_set_obj_coef(lp, i+1, colvar.objcoeff);
		// Set binary variable
		if(colvar.isBin)
			glp_set_col_kind(lp, i+1, GLP_BV);
	}

	// Adding rows
	glp_add_rows(lp, nRows);
	for(i=0; i<nRows; i++)
	{
		RowVar_t rowvar = mipreg.rowVars[i];
		glp_set_row_name(lp, i+1, rowvar.name.c_str());
		// Set bounds
		switch (rowvar.boundtype)
		{
		case LB:
			glp_set_row_bnds(lp, i+1, GLP_LO, rowvar.lb.getFloat(), rowvar.ub.getFloat());
			break;
		case UB:
			glp_set_row_bnds(lp, i+1, GLP_UP, rowvar.lb.getFloat(), rowvar.ub.getFloat());
			break;
		case FIX:
			glp_set_row_bnds(lp, i+1, GLP_FX, rowvar.lb.getFloat(), rowvar.ub.getFloat());
			break;
		default:	// LU
			glp_set_row_bnds(lp, i+1, GLP_DB, rowvar.lb.getFloat(), rowvar.ub.getFloat());
			break;
		}
	}

	// Setup matrix

	int* ia = new int[1+nCols*nRows];
	int* ja = new int[1+nCols*nRows];
	double* ar = new double[1+nCols*nRows];

	counter = 1;
	for(i=1; i<=nRows; i++)
	{
		for(j=1; j<=nCols; j++)
		{
			ia[counter] = i;
			ja[counter] = j;
			// Get matrix values from rowvars coefficient
			// Minus 1 since GLP is 1-based, and we are 0-based
			RowVar_t rowvar = mipreg.rowVars[i-1];
			ar[counter] = rowvar.coef[j-1];
			counter++;
		}
	}

	glp_load_matrix(lp, nCols*nRows, ia, ja, ar);
	glp_term_out(GLP_OFF);
	glp_write_mps(lp, GLP_MPS_FILE, NULL, "out1.mps");

	glp_delete_prob(lp);
	delete [] ia;
	delete [] ja;
	delete [] ar;

}

bool MIPMinCheck::callMIP()
{
	OsiClpSolverInterface solver1;
	solver1.setLogLevel(0);
	// Read in example model in MPS file format
	// and assert that it is a clean model
	int numMpsReadErrors = solver1.readMps("out1.mps","");
	if(numMpsReadErrors>0)
		throw FatalError("Error reading MPS file");

	// Pass the solver with the problem to be solved to CbcModel
	CbcModel model(solver1);

	model.setLogLevel(0);
	// Do complete search
	model.branchAndBound();

	double z = model.getObjValue();

	return (target-z) < EPS;
	//std::cout<<"Target = "<<target<<" Obj = "<<z<<std::endl;
}


