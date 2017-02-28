/* Copyright 2016, Gurobi Optimization, Inc. */

/* This example formulates and solves the following simple QP model:

     minimize    x + y + x^2 + x*y + y^2 + y*z + z^2
     subject to  x + 2 y + 3 z >= 4
                 x +   y       >= 1

   The example illustrates the use of dense matrices to store A and Q
   (and dense vectors for the other relevant data).  We don't recommend
   that you use dense matrices, but this example may be helpful if you
   already have your data in this format.
*/

#include "gurobi_c++.h"
#include <Gurobi.h>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>
using namespace std;

struct EigenParams
{
	EigenParams()
	{
		nrvar = 3;
		nreq = 0;
		nrineq = 2;

		Q.resize(nrvar, nrvar);
		Aeq.resize(nreq, nrvar);
		Aineq.resize(nrineq, nrvar);

		C.resize(nrvar);
		Beq.resize(nreq);
		Bineq.resize(nrineq);
		XL.resize(nrvar);
		XU.resize(nrvar);
		X.resize(nrvar);

		Aineq << -1, -2, -3, -1, -1, 0;
		Bineq << -4, -1;

		XL << 0, 0, 0;
		XU << GRB_INFINITY, GRB_INFINITY, GRB_INFINITY;

    // Linear part of the objective function
		C << 1, 1, 0;
    // Quadratic part of the objective function
    Q << 1, 1, 0, 0, 1, 1, 0, 0, 1;
	}

	int nrvar, nreq, nrineq;
	Eigen::MatrixXd Q, Aeq, Aineq;
	Eigen::VectorXd C, Beq, Bineq, XL, XU, X;
};


static bool
dense_optimize(GRBEnv* env,
               int     rows,
               int     cols,
               double* c,     /* linear portion of objective function */
               double* Q,     /* quadratic portion of objective function */
               double* A,     /* constraint matrix */
               char*   sense, /* constraint senses */
               double* rhs,   /* RHS vector */
               double* lb,    /* variable lower bounds */
               double* ub,    /* variable upper bounds */
               char*   vtype, /* variable types (continuous, binary, etc.) */
               double* solution,
               double* objvalP)
{
  std::cout << "Variable type: " << vtype << std::endl;
  GRBModel model = GRBModel(*env);
  int i, j;
  bool success = false;

  /* Add variables to the model */
  GRBVar* vars = model.addVars(lb, ub, NULL, vtype, NULL, cols);

  /* Populate A matrix */

  for (i = 0; i < rows; i++) {
    GRBLinExpr lhs = 0;
    for (j = 0; j < cols; j++)
      if (A[i*cols+j] != 0)
        lhs += A[i*cols+j]*vars[j];
    model.addConstr(lhs, sense[i], rhs[i]);
  }

  GRBQuadExpr obj = 0;

  for (j = 0; j < cols; j++)
    obj += c[j]*vars[j];
  for (i = 0; i < cols; i++)
    for (j = 0; j < cols; j++)
      if (Q[i*cols+j] != 0) {
        obj += Q[i*cols+j]*vars[i]*vars[j];
      }

  model.setObjective(obj);

  model.optimize();

  model.write("dense.lp");

  if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
    *objvalP = model.get(GRB_DoubleAttr_ObjVal);
    for (i = 0; i < cols; i++)
      solution[i] = vars[i].get(GRB_DoubleAttr_X);
    success = true;
  }

  delete[] vars;

  return success;
}

//////////////////////////// MAIN PROGRAM //////////////////////////////////////
int main(int   argc, char *argv[])
{
  GRBEnv* env = 0;
  try {
    env = new GRBEnv();
    double c[] = {1, 1, 0};
    double  Q[3][3] = {{1, 1, 0}, {0, 1, 1}, {0, 0, 1}};
    double  A[2][3] = {{1, 2, 3}, {1, 1, 0}};
    char    sense[] = {'>', '>'};
    double  rhs[]   = {4, 1};
    double  lb[]    = {0, 0, 0};
    bool    success;
    double  objval, sol[3];

    char type[3];
    for (int i=0;i<3;i++) {
      type[i] = GRB_CONTINUOUS;
    }

    std::cout << "############## SOLVED WITH PURE GUROBI ################" << std::endl;
    success = dense_optimize(env, 2, 3, c, &Q[0][0], &A[0][0], sense, rhs,
                             lb, NULL, &type[0], sol, &objval);

    std::cout << "############## SOLVED WITH EIGEN-GUROBI ################" << std::endl;
    EigenParams _eigenParams;
    Eigen::GurobiDense qp(_eigenParams.nrvar, _eigenParams.nreq, _eigenParams.nrineq);
    std::cout << "Solve" << std::endl;
    qp.solve(_eigenParams.Q, _eigenParams.C,
      _eigenParams.Aeq, _eigenParams.Beq,
      _eigenParams.Aineq, _eigenParams.Bineq,
      _eigenParams.XL, _eigenParams.XU);
    std::cout << " -- Result using Eigen: \n" << qp.result().transpose() << std::endl;
    std::cout << " -- Result using pure GUROBI: \n" << "x: " << sol[0] << " y: " << sol[1] << " z: " << sol[2] << endl;

  } catch(GRBException e) {
    cout << "Error code = " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch(...) {
    cout << "Exception during optimization" << endl;
  }

  delete env;
  return 0;
}
