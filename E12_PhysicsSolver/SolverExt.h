/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2023/11
----------------------------------------------*/
#ifndef __SOLVERA_H_
#define __SOLVERA_H_

#include "RTSG\Physics\Solver.h"
#include "RTSG\TypeDefs.h"

class SolverExt : public RTSG::Solver
{
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: object instance
	*/
	SolverExt(void);

	/*
	USAGE: Applies friction to the movement
	ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
	OUTPUT: ---
	*/
	void ApplyFriction(float a_fFriction = 0.1f) override;
	/*
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> Force to apply
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force) override;
	/*
	USAGE: Updates the Solver
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void) override;
	/*
	USAGE: Resolve the collision between two solvers
	ARGUMENTS: Solver* a_pOther -> other solver to resolve collision with
	OUTPUT: ---
	*/
	void ResolveCollision(Solver* a_pOther) override;
};//class


#endif //__SOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/